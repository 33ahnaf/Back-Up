// =============================================================================
// Tracker.cpp — Full IMU -> position pipeline implementation
// =============================================================================
#include "Tracker.h"
#include "Config.h"
#include <Arduino.h>
#include <Preferences.h>
#include <math.h>

namespace {
// constexpr float DEG_TO_RAD = 3.14159265358979f / 180.0f;   // no need of ts, Arduino.h already provides
constexpr float G_TO_MS2 = 9.80665f;
const char *NVS_NAMESPACE = "smartpen";
} // namespace

// ---------------------------------------------------------------------------
// begin()
// ---------------------------------------------------------------------------
bool Tracker::begin() {
    if (!imu_.begin()) {
        return false;
    }

    madgwick_.begin(Config::MADGWICK_BETA);

    for (int i = 0; i < 3; i++) {
        accelLpf_[i].begin(Config::ACCEL_LPF_CUTOFF_HZ);
        velHpf_[i].begin(Config::VELOCITY_HPF_CUTOFF_HZ);
        accelOutlier_[i].begin(6.0f * G_TO_MS2); // reject implausible >6g jumps
    }

    // If we have a recent calibration saved in flash, use it so the user
    // isn't forced to recalibrate on every single power cycle. They can
    // always force a fresh calibration with the 'c' serial command.
    if (loadCalibrationFromNvs()) {
        calibrated_ = true;
        Serial.println(F("[Tracker] Loaded saved calibration from flash."));
    }

    resetPosition();
    return true;
}

// ---------------------------------------------------------------------------
// calibrate() — blocking startup/on-demand calibration
// ---------------------------------------------------------------------------
void Tracker::calibrate() {
    Serial.println(F("[Tracker] Calibrating... hold the pen still and flat."));

    double gyroSum[3] = {0, 0, 0};
    double accelSum[3] = {0, 0, 0};
    int collected = 0;

    // Blocking on purpose: calibration is a one-time startup event, not
    // part of the real-time loop, so we don't need to worry about
    // non-blocking design here — simplicity wins.
    while (collected < Config::CALIBRATION_SAMPLES) {
        ImuSample s;
        if (imu_.readSample(s)) {
            gyroSum[0] += s.gx;
            gyroSum[1] += s.gy;
            gyroSum[2] += s.gz;
            accelSum[0] += s.ax;
            accelSum[1] += s.ay;
            accelSum[2] += s.az;
            collected++;
        }
        delayMicroseconds(Config::IMU_SAMPLE_PERIOD_US);
    }

    gyroBiasDps_[0] = static_cast<float>(gyroSum[0] / collected);
    gyroBiasDps_[1] = static_cast<float>(gyroSum[1] / collected);
    gyroBiasDps_[2] = static_cast<float>(gyroSum[2] / collected);

    float avgAx = static_cast<float>(accelSum[0] / collected);
    float avgAy = static_cast<float>(accelSum[1] / collected);
    float avgAz = static_cast<float>(accelSum[2] / collected);

    // Sanity check: if the gyro bias came out unreasonably large, the pen
    // probably wasn't held still — warn, but still proceed (better than
    // refusing to boot).
    float gyroBiasMag = sqrtf(gyroBiasDps_[0] * gyroBiasDps_[0] +
                               gyroBiasDps_[1] * gyroBiasDps_[1] +
                               gyroBiasDps_[2] * gyroBiasDps_[2]);
    if (gyroBiasMag > Config::CALIBRATION_GYRO_SANITY_DPS) {
        Serial.println(F("[Tracker] WARNING: gyro bias looks large — was the "
                          "pen held still during calibration?"));
    }

    // -----------------------------------------------------------------
    // Initialize orientation from the measured gravity vector instead of
    // letting Madgwick converge from identity over several real seconds
    // of motion. We deliberately do NOT treat this averaged accel vector
    // as a "bias to subtract" — it mostly IS gravity, and gravity is
    // exactly what the Madgwick filter needs in order to correct gyro
    // drift. Zeroing it out would remove the one reference signal the
    // whole fusion depends on.
    //
    // Rather than hand-deriving roll/pitch and building a quaternion
    // directly (Madgwick's internal quaternion is intentionally not
    // exposed for raw injection, to guarantee it only ever changes via
    // its own normalized update step), we reset to identity and run a
    // short "warm-up" burst of updates with zero gyro input and the
    // measured gravity vector as the accelerometer input. The gradient-
    // descent correction term converges the quaternion onto the correct
    // roll/pitch within a few dozen iterations — this just runs that
    // convergence once, instantly, at startup instead of waiting for it
    // to happen implicitly during the pen's first real strokes.
    // -----------------------------------------------------------------
    madgwick_.reset();
    // Temporarily crank the gain way up so ~200 iterations (1 simulated
    // second) is enough to converge from an arbitrary starting
    // orientation onto the measured gravity direction, regardless of how
    // far off "identity" the pen was actually held. At the normal
    // steady-state beta (0.1) this same convergence could take many real
    // seconds — fine during live tracking (smoothness matters more once
    // already oriented), too slow for a one-time startup snap.
    madgwick_.setBeta(3.0f);
    // The gradient-descent correction has a degenerate fixed point when the
    // measured gravity vector is *exactly* antipodal to the filter's
    // current "down" estimate (e.g. pen calibrated exactly upside-down) —
    // the gradient there is zero, so it never rotates away from identity.
    // A tiny fixed angular-rate "nudge" during warm-up only (not used
    // during real tracking) breaks that symmetry without measurably
    // affecting convergence from any normal starting orientation.
    constexpr float NUDGE_RAD_S = 0.01f;
    for (int i = 0; i < 200; i++) {
        madgwick_.update(NUDGE_RAD_S, NUDGE_RAD_S * 1.3f, 0.0f,
                          avgAx, avgAy, avgAz, 1.0f / Config::IMU_SAMPLE_RATE_HZ);
    }
    madgwick_.setBeta(Config::MADGWICK_BETA);

    for (int i = 0; i < 3; i++) {
        accelLpf_[i].reset(0.0f);
        velHpf_[i].reset();
        accelOutlier_[i].reset();
    }

    resetPosition();
    calibrated_ = true;
    haveLastSample_ = false;

    saveCalibrationToNvs();
    Serial.println(F("[Tracker] Calibration complete."));
}

// ---------------------------------------------------------------------------
// NVS persistence
// ---------------------------------------------------------------------------
void Tracker::saveCalibrationToNvs() {
    Preferences prefs;
    if (!prefs.begin(NVS_NAMESPACE, false)) return;
    prefs.putFloat("gbx", gyroBiasDps_[0]);
    prefs.putFloat("gby", gyroBiasDps_[1]);
    prefs.putFloat("gbz", gyroBiasDps_[2]);
    prefs.putBool("valid", true);
    prefs.end();
}

bool Tracker::loadCalibrationFromNvs() {
    Preferences prefs;
    if (!prefs.begin(NVS_NAMESPACE, true)) return false;
    bool valid = prefs.getBool("valid", false);
    if (valid) {
        gyroBiasDps_[0] = prefs.getFloat("gbx", 0.0f);
        gyroBiasDps_[1] = prefs.getFloat("gby", 0.0f);
        gyroBiasDps_[2] = prefs.getFloat("gbz", 0.0f);
    }
    prefs.end();
    return valid;
}

// ---------------------------------------------------------------------------
// resetPosition()
// ---------------------------------------------------------------------------
void Tracker::resetPosition() {
    for (int i = 0; i < 3; i++) {
        velocity_[i] = 0.0f;
        position_[i] = 0.0f;
    }
    stationaryCount_ = 0;
    isStationary_ = false;
}

// ---------------------------------------------------------------------------
// updateStationaryDetection()
// ---------------------------------------------------------------------------
void Tracker::updateStationaryDetection(float accelDevMagSq, float gyroMagDps) {
    bool lowAccel = accelDevMagSq < Config::STATIONARY_ACCEL_VARIANCE_THRESH;
    bool lowGyro = gyroMagDps < Config::STATIONARY_GYRO_THRESH_DPS;

    if (lowAccel && lowGyro) {
        if (stationaryCount_ < Config::STATIONARY_WINDOW_SAMPLES) {
            stationaryCount_++;
        }
    } else {
        stationaryCount_ = 0;
    }

    isStationary_ = (stationaryCount_ >= Config::STATIONARY_WINDOW_SAMPLES);
}

// ---------------------------------------------------------------------------
// update() — the real-time pipeline, called every loop()
// ---------------------------------------------------------------------------
bool Tracker::update(bool penButtonPressed) {
    if (!imu_.isConnected()) return false;

    // Rate-limit to Config::IMU_SAMPLE_RATE_HZ using elapsed micros rather
    // than delay(), so the rest of the firmware (WiFi/WebSocket stack, etc)
    // never gets blocked.
    uint32_t now = micros();
    if (haveLastSample_ &&
        (now - lastSampleUs_) < Config::IMU_SAMPLE_PERIOD_US) {
        return false;
    }

    ImuSample s;
    if (!imu_.readSample(s)) {
        return false; // I2C hiccup — caller will see no new frame this cycle
    }

    // -----------------------------------------------------------------
    // dt (variable, measured — not assumed constant)
    // -----------------------------------------------------------------
    float dt;
    if (!haveLastSample_) {
        dt = 1.0f / Config::IMU_SAMPLE_RATE_HZ; // first sample: assume nominal
    } else {
        dt = static_cast<float>(now - lastSampleUs_) / 1000000.0f;
        // Guard against an absurd dt (e.g. after a stall/reconnect) blowing
        // up the integrator.
        if (dt <= 0.0f || dt > 0.05f) dt = 1.0f / Config::IMU_SAMPLE_RATE_HZ;
    }
    lastSampleUs_ = now;
    haveLastSample_ = true;

    // -----------------------------------------------------------------
    // Bias removal (gyro only — see calibrate() for why accel bias is
    // handled differently)
    // -----------------------------------------------------------------
    float gxDps = s.gx - gyroBiasDps_[0];
    float gyDps = s.gy - gyroBiasDps_[1];
    float gzDps = s.gz - gyroBiasDps_[2];

    // -----------------------------------------------------------------
    // Madgwick fusion -> orientation
    // -----------------------------------------------------------------
    madgwick_.update(gxDps * DEG_TO_RAD, gyDps * DEG_TO_RAD, gzDps * DEG_TO_RAD,
                      s.ax, s.ay, s.az, dt);

    float qw, qx, qy, qz;
    madgwick_.getQuaternion(qw, qx, qy, qz);

    // -----------------------------------------------------------------
    // Gravity compensation: rotate measured accel into world frame, then
    // subtract the world "up" gravity vector (0,0,+1g). What remains is
    // the linear (non-gravity) acceleration the pen actually experienced.
    // -----------------------------------------------------------------
    float worldAx, worldAy, worldAz;
    madgwick_.rotateToWorld(s.ax, s.ay, s.az, worldAx, worldAy, worldAz);
    worldAz -= 1.0f; // remove +1g "up" component

    float linAccel[3] = {worldAx * G_TO_MS2, worldAy * G_TO_MS2, worldAz * G_TO_MS2};

    // -----------------------------------------------------------------
    // Stationary / ZUPT pre-check uses the RAW (pre-filter) deviation so
    // filter lag doesn't delay detecting "we've stopped".
    // -----------------------------------------------------------------
    float accelDevMagSq = linAccel[0] * linAccel[0] +
                           linAccel[1] * linAccel[1] +
                           linAccel[2] * linAccel[2];
    float gyroMagDps = sqrtf(gxDps * gxDps + gyDps * gyDps + gzDps * gzDps);
    updateStationaryDetection(accelDevMagSq, gyroMagDps);

    // -----------------------------------------------------------------
    // Per-axis: outlier rejection -> low-pass -> dead-zone
    // -----------------------------------------------------------------
    for (int i = 0; i < 3; i++) {
        linAccel[i] = accelOutlier_[i].apply(linAccel[i]);
        linAccel[i] = accelLpf_[i].apply(linAccel[i], dt);
        linAccel[i] = deadZone(linAccel[i], Config::ACCEL_DEADZONE);
    }

    // -----------------------------------------------------------------
    // Velocity integration + damping + clamping
    // -----------------------------------------------------------------
    for (int i = 0; i < 3; i++) {
        velocity_[i] += linAccel[i] * dt;
        velocity_[i] *= Config::VELOCITY_DAMPING;

        if (velocity_[i] > Config::VELOCITY_CLAMP) velocity_[i] = Config::VELOCITY_CLAMP;
        if (velocity_[i] < -Config::VELOCITY_CLAMP) velocity_[i] = -Config::VELOCITY_CLAMP;

        // High-pass filter bleeds off slow near-DC drift in velocity that
        // survives damping (residual bias the 1-point calibration can't
        // fully remove).
        velocity_[i] = velHpf_[i].apply(velocity_[i], dt);
    }

    // -----------------------------------------------------------------
    // ZUPT: once we're confidently stationary, snap velocity to zero.
    // This is the single strongest anti-drift measure in the pipeline —
    // it's what prevents small residual velocity from silently
    // accumulating into large position error over many strokes.
    // -----------------------------------------------------------------
    if (isStationary_) {
        velocity_[0] = velocity_[1] = velocity_[2] = 0.0f;
    }

    // -----------------------------------------------------------------
    // Position integration
    // -----------------------------------------------------------------
    for (int i = 0; i < 3; i++) {
        position_[i] += velocity_[i] * dt;
    }

    // -----------------------------------------------------------------
    // Scaling to canvas pixels. We take world X/Y as the writing plane
    // (Z, "toward/away from the writer", is tracked but not drawn — a
    // 2D canvas can't show depth, and handwriting is predominantly planar
    // motion anyway).
    // -----------------------------------------------------------------
    frame_.canvasX = position_[0] * Config::POSITION_TO_PIXELS;
    frame_.canvasY = -position_[1] * Config::POSITION_TO_PIXELS; // screen Y is inverted vs world Y (up)

    // Synthetic pen-down/up is gone — this is now driven directly by the
    // debounced physical button on Config::PIN_PEN_BUTTON. "Stationary"
    // (from the ZUPT detector above) stays purely an internal drift-control
    // signal; it no longer decides what the browser draws.
    frame_.penDown = penButtonPressed ? 1 : 0;

    frame_.posX = position_[0]; frame_.posY = position_[1]; frame_.posZ = position_[2];
    frame_.velX = velocity_[0]; frame_.velY = velocity_[1]; frame_.velZ = velocity_[2];
    frame_.accX = linAccel[0]; frame_.accY = linAccel[1]; frame_.accZ = linAccel[2];
    frame_.qw = qw; frame_.qx = qx; frame_.qy = qy; frame_.qz = qz;
    frame_.stationary = isStationary_;
    frame_.sampleIntervalUs = static_cast<uint32_t>(dt * 1000000.0f);

    return true;
}
