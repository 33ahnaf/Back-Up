// =============================================================================
// Madgwick.cpp — Madgwick AHRS filter (IMU-only variant), implemented from
// first principles following Madgwick's 2010 report, section 3 (equations
// 12-42, without the magnetometer terms).
// =============================================================================
#include "Madgwick.h"
#include <math.h>

void Madgwick::begin(float beta) {
    beta_ = beta;
    reset();
}

void Madgwick::reset() {
    q0_ = 1.0f; q1_ = 0.0f; q2_ = 0.0f; q3_ = 0.0f;
}

void Madgwick::update(float gx, float gy, float gz,
                       float ax, float ay, float az,
                       float dt) {
    // -------------------------------------------------------------------
    // Step 1: Rate of change of quaternion from gyroscope
    // -------------------------------------------------------------------
    // A quaternion derivative from angular rate is: q_dot = 0.5 * q * omega
    // where omega is the pure-quaternion (0, gx, gy, gz).
    float qDot1 = 0.5f * (-q1_ * gx - q2_ * gy - q3_ * gz);
    float qDot2 = 0.5f * ( q0_ * gx + q2_ * gz - q3_ * gy);
    float qDot3 = 0.5f * ( q0_ * gy - q1_ * gz + q3_ * gx);
    float qDot4 = 0.5f * ( q0_ * gz + q1_ * gy - q2_ * gx);

    // -------------------------------------------------------------------
    // Step 2: Gradient-descent accelerometer correction
    // -------------------------------------------------------------------
    // Only apply the correction if the accelerometer reading is non-zero
    // (a zero vector has no direction information and would produce NaNs
    // after normalization).
    float accNormSq = ax * ax + ay * ay + az * az;
    if (accNormSq > 1e-12f) {
        // Normalize accelerometer measurement to a unit vector.
        float recipNorm = 1.0f / sqrtf(accNormSq);
        ax *= recipNorm;
        ay *= recipNorm;
        az *= recipNorm;

        // Auxiliary variables to avoid repeated arithmetic (matches
        // Madgwick's reference C implementation naming).
        float _2q0 = 2.0f * q0_;
        float _2q1 = 2.0f * q1_;
        float _2q2 = 2.0f * q2_;
        float _2q3 = 2.0f * q3_;
        float _4q0 = 4.0f * q0_;
        float _4q1 = 4.0f * q1_;
        float _4q2 = 4.0f * q2_;
        float _8q1 = 8.0f * q1_;
        float _8q2 = 8.0f * q2_;
        float q0q0 = q0_ * q0_;
        float q1q1 = q1_ * q1_;
        float q2q2 = q2_ * q2_;
        float q3q3 = q3_ * q3_;

        // Gradient of the error function f = (estimated gravity direction
        // from q) - (measured gravity direction from accelerometer),
        // differentiated with respect to each quaternion component.
        // This is the analytic Jacobian-transpose * f from the paper —
        // derived once, then hardcoded (this is the standard reference
        // form; re-deriving the symbolic Jacobian by hand each run would
        // be wasteful, but the math is exactly Madgwick eq. 25).
        float s0 = _4q0 * q2q2 + _2q2 * ax + _4q0 * q1q1 - _2q1 * ay;
        float s1 = _4q1 * q3q3 - _2q3 * ax + 4.0f * q0q0 * q1_ - _2q0 * ay
                   - _4q1 + _8q1 * q1q1 + _8q1 * q2q2 + _4q1 * az;
        float s2 = 4.0f * q0q0 * q2_ + _2q0 * ax + _4q2 * q3q3 - _2q3 * ay
                   - _4q2 + _8q2 * q1q1 + _8q2 * q2q2 + _4q2 * az;
        float s3 = 4.0f * q1q1 * q3_ - _2q1 * ax + 4.0f * q2q2 * q3_ - _2q2 * ay;

        float gradNormSq = s0 * s0 + s1 * s1 + s2 * s2 + s3 * s3;
        if (gradNormSq > 1e-12f) {
            float gradRecipNorm = 1.0f / sqrtf(gradNormSq);
            s0 *= gradRecipNorm;
            s1 *= gradRecipNorm;
            s2 *= gradRecipNorm;
            s3 *= gradRecipNorm;

            // Apply feedback: subtract the (scaled) gradient from the
            // purely gyro-derived rate of change. beta_ trades off how
            // strongly the accelerometer "pulls" orientation back toward
            // gravity-consistent vs. how much we trust the gyro.
            qDot1 -= beta_ * s0;
            qDot2 -= beta_ * s1;
            qDot3 -= beta_ * s2;
            qDot4 -= beta_ * s3;
        }
    }
    // If the accelerometer reading was degenerate, we silently fall back to
    // pure gyro integration for this step — better than injecting garbage.

    // -------------------------------------------------------------------
    // Step 3: Integrate to yield new quaternion, then re-normalize
    // -------------------------------------------------------------------
    // Quaternions must stay unit-length to represent a valid rotation;
    // floating point integration drifts off the unit sphere over time, so
    // we renormalize every step (standard practice for this filter).
    q0_ += qDot1 * dt;
    q1_ += qDot2 * dt;
    q2_ += qDot3 * dt;
    q3_ += qDot4 * dt;

    float normSq = q0_ * q0_ + q1_ * q1_ + q2_ * q2_ + q3_ * q3_;
    if (normSq > 1e-12f) {
        float recipNorm = 1.0f / sqrtf(normSq);
        q0_ *= recipNorm;
        q1_ *= recipNorm;
        q2_ *= recipNorm;
        q3_ *= recipNorm;
    } else {
        // Should never happen in practice, but guard against NaN cascade.
        reset();
    }
}

void Madgwick::getQuaternion(float &w, float &x, float &y, float &z) const {
    w = q0_; x = q1_; y = q2_; z = q3_;
}

void Madgwick::rotateToWorld(float bx, float by, float bz,
                              float &wx, float &wy, float &wz) const {
    // Standard quaternion rotation of a vector v by q: v' = q * v * q^-1.
    // Expanded into direct arithmetic (avoids constructing a pure
    // quaternion and doing full quaternion multiplication twice).
    float q0 = q0_, q1 = q1_, q2 = q2_, q3 = q3_;

    // v' = v + 2*q0*(q_vec x v) + 2*(q_vec x (q_vec x v))
    // Expanded closed form (equivalent to the rotation matrix built from q):
    float ww = q0 * q0, xx = q1 * q1, yy = q2 * q2, zz = q3 * q3;
    float wx2 = q0 * q1, wy2 = q0 * q2, wz2 = q0 * q3;
    float xy = q1 * q2, xz = q1 * q3, yz = q2 * q3;

    wx = (ww + xx - yy - zz) * bx + 2.0f * (xy - wz2) * by + 2.0f * (xz + wy2) * bz;
    wy = 2.0f * (xy + wz2) * bx + (ww - xx + yy - zz) * by + 2.0f * (yz - wx2) * bz;
    wz = 2.0f * (xz - wy2) * bx + 2.0f * (yz + wx2) * by + (ww - xx - yy + zz) * bz;
}
