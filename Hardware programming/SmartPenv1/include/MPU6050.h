#pragma once
// =============================================================================
// MPU6050.h — Minimal, transparent register-level driver for the MPU6050
// =============================================================================
// This is intentionally NOT built on top of a vendor abstraction library.
// Every register write is a documented, named constant, and every conversion
// from raw LSB counts to physical units is spelled out — so you can see
// exactly what the sensor is doing and why, rather than trusting a black box.
//
// Datasheet reference: InvenSense MPU-6000/MPU-6050 Register Map (RM-MPU-6000A-00)
// =============================================================================

#include <stdint.h>

// A single physical sample, already converted from raw LSBs into SI-ish
// units, but BEFORE any bias removal or filtering — that happens downstream
// in Tracker.
struct ImuSample {
    float ax, ay, az;   // accelerometer, g
    float gx, gy, gz;   // gyroscope, deg/s
    float temperature;  // degrees C (useful for debug / thermal drift awareness)
    uint32_t timestamp_us; // micros() at time of read
};

class MPU6050 {
public:
    MPU6050() = default;

    // Initializes I2C, verifies WHO_AM_I, and configures the sensor:
    // - wakes it from sleep
    // - sets gyro range to +-500 dps, accel range to +-4g (good balance of
    //   resolution vs. clipping for handwriting-scale motion)
    // - configures the digital low-pass filter (DLPF) and sample rate divider
    //   to land close to Config::IMU_SAMPLE_RATE_HZ
    // Returns false if the sensor does not respond / WHO_AM_I mismatches.
    bool begin();

    // True once begin() succeeded.
    bool isConnected() const { return connected_; }

    // Blocking read of one sample directly from sensor registers over I2C.
    // Converts raw int16 register values into g's / deg/s using the
    // configured full-scale ranges. Returns false on I2C read failure.
    bool readSample(ImuSample &out);

    // Re-checks the WHO_AM_I register — cheap way to detect a sensor that
    // disconnected mid-operation (loose wire, brownout, etc).
    bool ping();

private:
    bool connected_ = false;

    // Full-scale sensitivity divisors (LSB per unit), set by begin() to
    // match the ranges we configure in hardware. See datasheet section 6.
    float accel_lsb_per_g_ = 8192.0f;      // +-4g  -> 8192 LSB/g
    float gyro_lsb_per_dps_ = 65.5f;       // +-500dps -> 65.5 LSB/(deg/s)

    // --- low level I2C helpers ---
    bool writeRegister(uint8_t reg, uint8_t value);
    bool readRegisters(uint8_t reg, uint8_t *buf, uint8_t len);
    bool readRegister(uint8_t reg, uint8_t &value);
};
