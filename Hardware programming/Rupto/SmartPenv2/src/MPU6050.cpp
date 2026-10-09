// =============================================================================
// MPU6050.cpp — Register-level MPU6050 driver implementation
// =============================================================================
#include "MPU6050.h"
#include "Config.h"
#include <Wire.h>
#include <Arduino.h>

// ---------------------------------------------------------------------------
// Register map (only the registers we actually use)
// ---------------------------------------------------------------------------
namespace Reg {
constexpr uint8_t SMPLRT_DIV   = 0x19;
constexpr uint8_t CONFIG       = 0x1A; // DLPF config
constexpr uint8_t GYRO_CONFIG  = 0x1B;
constexpr uint8_t ACCEL_CONFIG = 0x1C;
constexpr uint8_t ACCEL_XOUT_H = 0x3B; // first of 14 contiguous bytes:
                                       // accel(6) + temp(2) + gyro(6)
constexpr uint8_t PWR_MGMT_1   = 0x6B;
constexpr uint8_t WHO_AM_I     = 0x75;
} // namespace Reg

constexpr uint8_t WHO_AM_I_EXPECTED = 0x68; // MPU6050 always reports this

// ---------------------------------------------------------------------------
// Low-level I2C
// ---------------------------------------------------------------------------

bool MPU6050::writeRegister(uint8_t reg, uint8_t value) {
    Wire.beginTransmission(Config::MPU6050_ADDR);
    Wire.write(reg);
    Wire.write(value);
    return Wire.endTransmission() == 0;
}

bool MPU6050::readRegisters(uint8_t reg, uint8_t *buf, uint8_t len) {
    Wire.beginTransmission(Config::MPU6050_ADDR);
    Wire.write(reg);
    if (Wire.endTransmission(false) != 0) { // repeated start, keep bus held
        return false;
    }
    uint8_t got = Wire.requestFrom(static_cast<int>(Config::MPU6050_ADDR),
                                    static_cast<int>(len), 1 /*sendStop*/);
    if (got != len) return false;
    for (uint8_t i = 0; i < len; i++) {
        buf[i] = Wire.read();
    }
    return true;
}

bool MPU6050::readRegister(uint8_t reg, uint8_t &value) {
    return readRegisters(reg, &value, 1);
}

// ---------------------------------------------------------------------------
// Initialization
// ---------------------------------------------------------------------------

bool MPU6050::begin() {
    Wire.begin(Config::PIN_SDA, Config::PIN_SCL);
    Wire.setClock(Config::I2C_CLOCK_HZ);

    uint8_t whoami = 0;
    if (!readRegister(Reg::WHO_AM_I, whoami) || whoami != WHO_AM_I_EXPECTED) {
        connected_ = false;
        return false;
    }

    // Wake the device up: PWR_MGMT_1 defaults to sleep=1 on power-on.
    // Bit layout: [DEVICE_RESET, SLEEP, CYCLE, -, TEMP_DIS, CLKSEL[2:0]]
    // We select CLKSEL=1 (PLL with X-axis gyro reference) — more stable
    // than the internal 8MHz oscillator.
    if (!writeRegister(Reg::PWR_MGMT_1, 0x01)) return false;
    delay(50); // datasheet: allow time for the clock source to stabilize

    // Configure DLPF (CONFIG register, bits 2:0 = DLPF_CFG).
    // DLPF_CFG=3 -> accel BW 44Hz/gyro BW 42Hz, gyro output rate 1kHz.
    // This is the digital anti-alias filter INSIDE the sensor, upstream of
    // our own software low-pass filter — it prevents high-frequency
    // vibration/noise from aliasing into our sample stream at all.
    if (!writeRegister(Reg::CONFIG, 0x03)) return false;

    // Sample rate divider: Sample Rate = GyroOutputRate / (1 + SMPLRT_DIV)
    // Gyro output rate is 1kHz when DLPF is enabled (DLPF_CFG != 0).
    // For a 200Hz target: divider = 1000/200 - 1 = 4.
    uint8_t divider = static_cast<uint8_t>(
        (1000 / Config::IMU_SAMPLE_RATE_HZ) - 1);
    if (!writeRegister(Reg::SMPLRT_DIV, divider)) return false;

    // Gyro full-scale range: FS_SEL=1 -> +-500 deg/s (bits 4:3 = 01)
    if (!writeRegister(Reg::GYRO_CONFIG, 0x08)) return false;
    gyro_lsb_per_dps_ = 65.5f; // datasheet table 6.1, FS_SEL=1

    // Accel full-scale range: AFS_SEL=1 -> +-4g (bits 4:3 = 01)
    if (!writeRegister(Reg::ACCEL_CONFIG, 0x08)) return false;
    accel_lsb_per_g_ = 8192.0f; // datasheet table 6.2, AFS_SEL=1

    connected_ = true;
    return true;
}

bool MPU6050::ping() {
    uint8_t whoami = 0;
    connected_ = readRegister(Reg::WHO_AM_I, whoami) && whoami == WHO_AM_I_EXPECTED;
    return connected_;
}

// ---------------------------------------------------------------------------
// Sampling
// ---------------------------------------------------------------------------

bool MPU6050::readSample(ImuSample &out) {
    // ACCEL_XOUT_H..GYRO_ZOUT_L are 14 contiguous bytes:
    // [ax_h ax_l ay_h ay_l az_h az_l temp_h temp_l gx_h gx_l gy_h gy_l gz_h gz_l]
    uint8_t raw[14];
    if (!readRegisters(Reg::ACCEL_XOUT_H, raw, sizeof(raw))) {
        connected_ = false;
        return false;
    }

    auto combine = [](uint8_t hi, uint8_t lo) -> int16_t {
        return static_cast<int16_t>((static_cast<uint16_t>(hi) << 8) | lo);
    };

    int16_t ax_raw = combine(raw[0], raw[1]);
    int16_t ay_raw = combine(raw[2], raw[3]);
    int16_t az_raw = combine(raw[4], raw[5]);
    int16_t temp_raw = combine(raw[6], raw[7]);
    int16_t gx_raw = combine(raw[8], raw[9]);
    int16_t gy_raw = combine(raw[10], raw[11]);
    int16_t gz_raw = combine(raw[12], raw[13]);

    out.ax = static_cast<float>(ax_raw) / accel_lsb_per_g_;
    out.ay = static_cast<float>(ay_raw) / accel_lsb_per_g_;
    out.az = static_cast<float>(az_raw) / accel_lsb_per_g_;

    out.gx = static_cast<float>(gx_raw) / gyro_lsb_per_dps_;
    out.gy = static_cast<float>(gy_raw) / gyro_lsb_per_dps_;
    out.gz = static_cast<float>(gz_raw) / gyro_lsb_per_dps_;

    // Datasheet section 6.3: Temp_degC = raw/340 + 36.53
    out.temperature = static_cast<float>(temp_raw) / 340.0f + 36.53f;

    out.timestamp_us = micros();
    return true;
}
