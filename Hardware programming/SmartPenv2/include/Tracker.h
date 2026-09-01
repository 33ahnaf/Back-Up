#pragma once
// =============================================================================
// Tracker.h — Orchestrates the full pipeline:
//
//   Raw MPU6050 -> Calibration -> Bias removal -> Madgwick -> Orientation ->
//   Gravity compensation -> Low-pass -> High-pass -> Dead-zone ->
//   Velocity integration -> Velocity damping -> Position integration ->
//   ZUPT -> Scaling -> (output consumed by WiFiServer)
//
// This is the "brain" of the project. Everything sensor/math-related lives
// here or in the modules it composes (MPU6050, Madgwick, Filters).
// =============================================================================

#include "MPU6050.h"
#include "Madgwick.h"
#include "Filters.h"
#include <stdint.h>

// One fully-processed output frame, ready to be serialized and sent to the
// browser (or printed for debugging).
struct TrackerFrame {
    float canvasX, canvasY;   // pixel-space position (already scaled+offset)
    uint8_t penDown;          // 1 = actively writing, 0 = stationary/"lifted"

    // Everything below is extra context, primarily for the debug graphs /
    // Serial debug output — the browser's main draw loop only needs the
    // three fields above.
    float posX, posY, posZ;         // integrated position, meters
    float velX, velY, velZ;         // integrated velocity, m/s
    float accX, accY, accZ;         // gravity-compensated world accel, m/s^2
    float qw, qx, qy, qz;           // orientation quaternion
    bool stationary;                // current ZUPT state
    uint32_t sampleIntervalUs;      // actual dt of this sample, for FPS/debug
};

class Tracker {
public:
    bool begin();

    // Runs a full blocking calibration: asks the pen to be held still,
    // averages CALIBRATION_SAMPLES readings, computes gyro bias and an
    // initial orientation from the measured gravity direction. Persists
    // the gyro bias to NVS (flash) so a quick power-cycle doesn't require
    // re-calibrating (still recommended if the device changes temperature
    // or gets bumped, hence also exposed as a serial command).
    void calibrate();

    // Call every loop() iteration. Internally rate-limits itself to
    // Config::IMU_SAMPLE_RATE_HZ using timestamps (not delay()), so it's
    // safe to call as fast as possible from a non-blocking main loop.
    //   penButtonPressed: the debounced state of the physical pen-tip
    //   button (Config::PIN_PEN_BUTTON). This is the authoritative
    //   pen-down/up signal now — no more guessing from motion. The
    //   internal ZUPT stationary detector still runs and is still used
    //   for drift-correcting velocity (see Tracker.cpp), but it no longer
    //   decides what gets reported as "writing".
    // Returns true if a new sample was processed (i.e. a new TrackerFrame
    // is available via latestFrame()).
    bool update(bool penButtonPressed);

    const TrackerFrame &latestFrame() const { return frame_; }

    bool imuConnected() const { return imu_.isConnected(); }

    // True if begin() found and loaded a valid saved calibration from
    // flash. main.cpp uses this to skip the blocking startup calibration
    // on a quick power cycle (still recommended after a temperature
    // change or bump — force it any time with the 'c' serial command).
    bool hasStoredCalibration() const { return calibrated_; }

    // Resets integrated velocity/position back to the canvas center —
    // used by the "Clear" button round-trip and also callable from a
    // serial command for convenience while debugging.
    void resetPosition();

private:
    MPU6050 imu_;
    Madgwick madgwick_;

    // --- calibration state ---
    float gyroBiasDps_[3] = {0, 0, 0};
    bool calibrated_ = false;

    // --- per-axis filters (world frame X/Y/Z) ---
    LowPassFilter accelLpf_[3];
    HighPassFilter velHpf_[3];
    OutlierRejector accelOutlier_[3];

    // --- integrator state ---
    float velocity_[3] = {0, 0, 0};
    float position_[3] = {0, 0, 0};

    // --- stationary / ZUPT detection ---
    int stationaryCount_ = 0;
    bool isStationary_ = false;

    // --- timing ---
    uint32_t lastSampleUs_ = 0;
    bool haveLastSample_ = false;

    TrackerFrame frame_{};

    // Persist / restore gyro bias so a cold boot can skip full
    // recalibration if the last calibration is still reasonably fresh
    // (see WiFiServer / main.cpp for how this is surfaced to the user).
    void saveCalibrationToNvs();
    bool loadCalibrationFromNvs();

    // Internal step helpers (kept as separate methods so each pipeline
    // stage is independently readable/testable).
    void updateStationaryDetection(float accelDevMagSq, float gyroMagDps);
};
