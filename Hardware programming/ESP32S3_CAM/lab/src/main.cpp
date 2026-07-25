#include <Arduino.h>
#include <Wire.h>

constexpr uint8_t MPU_ADDR = 0x68;

int16_t ax, ay, az;
int16_t gx, gy, gz;

void writeReg(uint8_t reg, uint8_t value)
{
    Wire.beginTransmission(MPU_ADDR);
    Wire.write(reg);
    Wire.write(value);
    Wire.endTransmission();
}

void readRaw()
{
    Wire.beginTransmission(MPU_ADDR);
    Wire.write(0x3B);
    Wire.endTransmission(false);

    Wire.requestFrom(MPU_ADDR, 14);

    ax = Wire.read() << 8 | Wire.read();
    ay = Wire.read() << 8 | Wire.read();
    az = Wire.read() << 8 | Wire.read();

    Wire.read();
    Wire.read();

    gx = Wire.read() << 8 | Wire.read();
    gy = Wire.read() << 8 | Wire.read();
    gz = Wire.read() << 8 | Wire.read();
}

void setup()
{
    Serial.begin(115200);

    Wire.begin();

    writeReg(0x6B,0);

    delay(1000);

    Serial.println("MPU6050 Ready");
}

void loop()
{
    readRaw();

    Serial.printf(
        "A:%6d %6d %6d   G:%6d %6d %6d\n",
        ax,ay,az,
        gx,gy,gz);

    delay(5);
}