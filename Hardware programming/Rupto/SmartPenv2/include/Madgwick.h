#pragma once
// =============================================================================
// Madgwick.h — Hand-written Madgwick AHRS orientation filter (IMU variant)
// =============================================================================
// This implements Sebastian Madgwick's gradient-descent orientation filter
// as described in his 2010 report "An efficient orientation filter for
// inertial and inertial/magnetic sensor arrays". We implement the IMU-only
// variant (no magnetometer), which fuses:
//
//   - Gyroscope: integrated to predict orientation change (accurate short
//     term, drifts over time)
//   - Accelerometer: measures the gravity direction, used to correct the
//     gyro's drift by nudging orientation so that gravity is remeasured as
//     "down" in the sensor's estimated world frame.
//
// The filter operates on a quaternion (w,x,y,z) representing the rotation
// from the sensor's body frame to the world (Earth) frame.
// =============================================================================

class Madgwick {
public:
    Madgwick() = default;

    // beta: filter gain — see Config::MADGWICK_BETA for tuning notes.
    void begin(float beta);

    // Resets orientation to identity (pen pointing however it was when
    // powered on is treated as "level"). Called after calibration.
    void reset();

    // Changes the gain without touching the current orientation estimate.
    // Used by Tracker to temporarily run a much higher gain during the
    // post-calibration "warm-up burst" (fast convergence onto the measured
    // gravity direction), then drop back to the normal steady-state gain
    // for real-time tracking (smoother, less noise-sensitive).
    void setBeta(float beta) { beta_ = beta; }

    // Runs one filter update step.
    //   gx,gy,gz : gyroscope reading in rad/s (already bias-removed)
    //   ax,ay,az : accelerometer reading in g (already bias-removed);
    //              does not need to be normalized, this function does it.
    //   dt       : elapsed time in seconds since the previous update
    void update(float gx, float gy, float gz,
                float ax, float ay, float az,
                float dt);

    // Current orientation quaternion (body -> world).
    void getQuaternion(float &w, float &x, float &y, float &z) const;

    // Rotates a body-frame vector into the world frame using the current
    // orientation quaternion. Used by Tracker to express measured
    // acceleration in world coordinates before subtracting gravity.
    void rotateToWorld(float bx, float by, float bz,
                        float &wx, float &wy, float &wz) const;

private:
    float beta_ = 0.1f;
    // Quaternion components, world<-body, initialized to identity (no rotation).
    float q0_ = 1.0f, q1_ = 0.0f, q2_ = 0.0f, q3_ = 0.0f;
};
