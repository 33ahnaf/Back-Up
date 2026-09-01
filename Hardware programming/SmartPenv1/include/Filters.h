#pragma once
// =============================================================================
// Filters.h — Reusable single-purpose DSP building blocks
// =============================================================================
// Each filter here does exactly one job and is deliberately simple (all are
// first-order IIR filters, which only need O(1) memory and O(1) time per
// sample — important on an MCU running at 200Hz with no room for FFTs or
// buffers of history). Tracker.cpp wires several of these together into the
// full pipeline.
// =============================================================================

#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846f
#endif

// -----------------------------------------------------------------------
// LowPassFilter — first-order RC-style low-pass ("exponential moving
// average" tuned to a cutoff frequency instead of a raw alpha constant).
//
// Why: raw accelerometer readings are noisy at high frequency (sensor
// noise + hand tremor + mechanical vibration from holding a pen). Real
// handwriting motion lives well below ~10Hz, so smoothing above that
// removes noise without removing the signal we care about.
// -----------------------------------------------------------------------
class LowPassFilter {
public:
    void begin(float cutoffHz) { cutoffHz_ = cutoffHz; }

    float apply(float input, float dt) {
        // Standard RC low-pass alpha derivation:
        //   alpha = dt / (RC + dt), RC = 1 / (2*pi*cutoffHz)
        float rc = 1.0f / (2.0f * static_cast<float>(M_PI) * cutoffHz_);
        float alpha = dt / (rc + dt);
        value_ = value_ + alpha * (input - value_);
        return value_;
    }

    void reset(float initial = 0.0f) { value_ = initial; }
    float value() const { return value_; }

private:
    float cutoffHz_ = 5.0f;
    float value_ = 0.0f;
};

// -----------------------------------------------------------------------
// HighPassFilter — first-order high-pass, complementary to the low-pass
// above (output = input - lowpass(input)).
//
// Why: we use this on integrated velocity, not on raw acceleration. Any
// residual accelerometer bias that calibration didn't fully remove
// integrates into a slow, near-constant drift in velocity. A gentle
// high-pass filter on velocity slowly bleeds off exactly that kind of
// near-DC drift while leaving genuine (higher-frequency) velocity changes
// from real strokes intact.
// -----------------------------------------------------------------------
class HighPassFilter {
public:
    void begin(float cutoffHz) { cutoffHz_ = cutoffHz; }

    float apply(float input, float dt) {
        float rc = 1.0f / (2.0f * static_cast<float>(M_PI) * cutoffHz_);
        float alpha = rc / (rc + dt);
        // Classic discrete high-pass: y[n] = alpha*(y[n-1] + x[n] - x[n-1])
        float output = alpha * (prevOutput_ + input - prevInput_);
        prevInput_ = input;
        prevOutput_ = output;
        return output;
    }

    void reset() { prevInput_ = 0.0f; prevOutput_ = 0.0f; }

private:
    float cutoffHz_ = 0.3f;
    float prevInput_ = 0.0f;
    float prevOutput_ = 0.0f;
};

// -----------------------------------------------------------------------
// MovingAverageFilter — simple fixed-window average (optional extra
// smoothing stage, e.g. for the values shown on the debug graphs so they
// don't look jittery, without affecting the "hot path" integration math).
// -----------------------------------------------------------------------
template <int WINDOW>
class MovingAverageFilter {
public:
    float apply(float input) {
        sum_ -= buf_[idx_];
        buf_[idx_] = input;
        sum_ += input;
        idx_ = (idx_ + 1) % WINDOW;
        if (count_ < WINDOW) count_++;
        return sum_ / static_cast<float>(count_);
    }

    void reset() {
        for (int i = 0; i < WINDOW; i++) buf_[i] = 0.0f;
        sum_ = 0.0f; idx_ = 0; count_ = 0;
    }

private:
    float buf_[WINDOW] = {0};
    float sum_ = 0.0f;
    int idx_ = 0;
    int count_ = 0;
};

// -----------------------------------------------------------------------
// deadZone — kills small values outright.
//
// Why: this is what actually stops a stationary pen from "creeping" across
// the canvas. Even after gravity compensation and low-pass filtering,
// there's always a little residual noise; if left alone it eventually
// integrates into drift. Anything under the threshold gets snapped to
// zero, cutting off the noise floor before it ever reaches the integrator.
// -----------------------------------------------------------------------
inline float deadZone(float value, float threshold) {
    return (fabsf(value) < threshold) ? 0.0f : value;
}

// -----------------------------------------------------------------------
// OutlierRejector — rejects single-sample spikes (e.g. an I2C glitch or a
// momentary bad read) by comparing against a running average and ignoring
// (repeating the last good value for) anything wildly out of family.
//
// Why: a single corrupted sample, if allowed straight into the integrator,
// can inject a velocity/position spike that never gets undone. Rejecting
// implausible single-sample jumps is cheap insurance against that.
// -----------------------------------------------------------------------
class OutlierRejector {
public:
    void begin(float maxJump) { maxJump_ = maxJump; }

    float apply(float input) {
        if (!initialized_) {
            last_ = input;
            initialized_ = true;
            return input;
        }
        if (fabsf(input - last_) > maxJump_) {
            // Implausible jump — hold the previous value instead of
            // propagating a glitch into the integration pipeline.
            return last_;
        }
        last_ = input;
        return input;
    }

    void reset() { initialized_ = false; last_ = 0.0f; }

private:
    float maxJump_ = 4.0f;
    float last_ = 0.0f;
    bool initialized_ = false;
};
