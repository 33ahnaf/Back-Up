#pragma once
// =============================================================================
// Config.h — Central configuration for the SmartPen firmware
// =============================================================================
// Every "magic number" in the project lives here so the rest of the codebase
// stays readable and so tuning the tracker doesn't require hunting through
// multiple files.
// =============================================================================

#include <Arduino.h>
#include <stdint.h>

namespace Config {

// ---------------------------------------------------------------------------
// I2C / Hardware pins (XIAO ESP32-S3)
// ---------------------------------------------------------------------------
// The XIAO ESP32-S3 exposes its default I2C pins as D4 (SDA) / D5 (SCL),
// which map to GPIO5 (SDA) and GPIO6 (SCL) on the Seeed board.
constexpr int PIN_SDA = D4;
constexpr int PIN_SCL = D5;
constexpr uint32_t I2C_CLOCK_HZ = 400000;      // 400kHz fast-mode I2C
constexpr uint8_t MPU6050_ADDR = 0x68;         // AD0 pin low (default)

// Physical "pen tip" button — wired between D7 and GND, using the pin's
// internal pull-up (no external resistor needed). Reads LOW while pressed,
// HIGH while released. D7 maps to GPIO44, which doubles as the chip's
// UART0 RX pin — that's fine here because Serial on the ESP32-S3 XIAO goes
// over native USB-CDC (HWCDC), not UART0, so GPIO44 is free for GPIO use.
constexpr int PIN_PEN_BUTTON = D7;
constexpr uint32_t BUTTON_DEBOUNCE_MS = 15;

// ---------------------------------------------------------------------------
// Sampling / timing
// ---------------------------------------------------------------------------
// Target IMU sample rate. The MPU6050's internal DLPF + sample-rate divider
// are configured to get as close to this as the sensor allows.
constexpr uint32_t IMU_SAMPLE_RATE_HZ = 200;
constexpr uint32_t IMU_SAMPLE_PERIOD_US = 1000000UL / IMU_SAMPLE_RATE_HZ;

// How often we push a position update to the browser. We intentionally send
// at a lower rate than we sample/integrate at — the integration needs the
// full 200Hz to keep dt small and error low, but the network + browser only
// need to render at display frame rate.
constexpr uint32_t STREAM_RATE_HZ = 60;
constexpr uint32_t STREAM_PERIOD_US = 1000000UL / STREAM_RATE_HZ;

// ---------------------------------------------------------------------------
// Calibration
// ---------------------------------------------------------------------------
// Number of samples averaged during startup calibration. At 200Hz this is
// ~2 seconds — long enough to average out sensor noise, short enough that
// the user doesn't get impatient waiting with the pen held still.
constexpr int CALIBRATION_SAMPLES = 1000;

// Gyro bias values below this (deg/s) after calibration are considered good;
// otherwise we flag a warning over Serial (probably wasn't held still).
constexpr float CALIBRATION_GYRO_SANITY_DPS = 5.0f;

// ---------------------------------------------------------------------------
// Madgwick filter
// ---------------------------------------------------------------------------
// Beta is the Madgwick filter's convergence rate — how strongly the
// accelerometer correction pulls the gyro-integrated orientation back toward
// "gravity down". Higher = faster correction but noisier; lower = smoother
// but slower to correct drift. 0.1 is a reasonable middle ground for a
// handheld device that moves quickly (a pen).
constexpr float MADGWICK_BETA = 0.10f;

// ---------------------------------------------------------------------------
// Filtering
// ---------------------------------------------------------------------------
// Low-pass filter cutoff for linear acceleration (Hz). Handwriting motion
// lives roughly in the 0.5–10Hz band; anything faster is mostly sensor noise
// and high-frequency vibration.
constexpr float ACCEL_LPF_CUTOFF_HZ = 8.0f;

// High-pass filter cutoff for velocity (Hz). This slowly bleeds off any
// constant-offset creep in the integrated velocity (a residual bias the
// accelerometer calibration didn't fully remove). Set low so it doesn't
// fight real slow strokes.
constexpr float VELOCITY_HPF_CUTOFF_HZ = 0.3f;

// Acceleration dead-zone (m/s^2). Any compensated acceleration with
// magnitude below this is treated as noise and zeroed — this is what stops
// the pen from "creeping" while sitting still.
constexpr float ACCEL_DEADZONE = 0.08f;

// ---------------------------------------------------------------------------
// Drift reduction / ZUPT (Zero velocity update)
// ---------------------------------------------------------------------------
// A window is classified "stationary" when both accel deviation from 1g and
// gyro magnitude stay below these thresholds for STATIONARY_WINDOW_SAMPLES
// consecutive samples.
constexpr float STATIONARY_ACCEL_VARIANCE_THRESH = 0.35f; // (m/s^2)^2
constexpr float STATIONARY_GYRO_THRESH_DPS = 3.0f;        // deg/s
constexpr int STATIONARY_WINDOW_SAMPLES = 12;             // ~60ms @ 200Hz

// Velocity damping factor applied every integration step (simple exponential
// decay). This is the single biggest lever against runaway drift: without
// it, any tiny residual bias integrates into a velocity that never returns
// to zero. Value is per-sample multiplier, so it's very close to 1.0.
constexpr float VELOCITY_DAMPING = 0.985f;

// Hard clamp on integrated velocity (m/s). Real handwriting rarely exceeds
// ~0.5 m/s; clamping guards against a bad sample spiking the integrator.
constexpr float VELOCITY_CLAMP = 0.6f;

// ---------------------------------------------------------------------------
// Output scaling
// ---------------------------------------------------------------------------
// Converts integrated position (meters) into canvas pixels. Tune this to
// match how large you want strokes to appear — larger value = more
// sensitive/bigger strokes for the same physical hand motion.
constexpr float POSITION_TO_PIXELS = 4000.0f;

// ---------------------------------------------------------------------------
// Networking
// ---------------------------------------------------------------------------
constexpr const char *WIFI_SSID = "SmartPen";
constexpr const char *WIFI_PASSWORD = "12345678";
constexpr uint8_t WIFI_CHANNEL = 6;
constexpr uint16_t HTTP_PORT = 80;

// ---------------------------------------------------------------------------
// Debug
// ---------------------------------------------------------------------------
constexpr uint32_t SERIAL_BAUD = 115200;
constexpr uint32_t DEBUG_PRINT_PERIOD_MS = 200; // throttle serial spam

} // namespace Config
