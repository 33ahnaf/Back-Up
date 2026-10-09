#pragma once
// ============================================================================
// SPIBus
//
// Thin, allocation-free wrapper around the ESP32 hardware SPI peripheral.
// This class knows nothing about any specific LCD controller - it only
// knows how to toggle CS/DC and shove bytes out over MOSI/SCK. Every driver
// in drivers/ is built entirely on top of this primitive, which is what lets
// the tester swap controllers at runtime instead of relying on TFT_eSPI's
// compile-time driver selection.
//
// There is intentionally no MISO handling: the target hardware is wired
// write-only (CS, DC, MOSI, SCK, RST), which is the normal wiring for a
// write-only SPI TFT.
// ============================================================================

#include <Arduino.h>
#include <SPI.h>

namespace tft {

// Common SPI clock presets. Selected at boot from the ENABLE_SLOW_SPI /
// ENABLE_FAST_SPI compile-time flags (see Utilities.h).
enum class SPISpeed : uint32_t {
    MHz40 = 40000000UL,
    MHz26 = 26000000UL,
    MHz20 = 20000000UL,
    MHz8  = 8000000UL
};

class SPIBus {
public:
    // csPin/dcPin/rstPin/mosiPin/sckPin: physical GPIO numbers on the
    // ESP32-WROOM-32. Pass rstPin = -1 if RST is tied to EN/3V3 instead of a
    // GPIO (software reset will then be used exclusively).
    SPIBus(int8_t csPin,
           int8_t dcPin,
           int8_t rstPin,
           int8_t mosiPin,
           int8_t sckPin,
           SPIClass& spi = SPI);

    // Configures pin modes and starts the underlying SPIClass. Must be
    // called once from setup() before any driver is used.
    void begin(uint32_t frequency = static_cast<uint32_t>(SPISpeed::MHz40));

    // Changes the SPI clock without re-initializing pin modes. Some
    // controllers (notably ILI9486/HX8357 clones) are unreliable above
    // 20-26 MHz, so the diagnostic tool may want to retry at a lower speed.
    void setFrequency(uint32_t frequency);

    // Re-homes every signal onto a new set of physical GPIOs, at the
    // current frequency. Used by the pin-permutation sweep (see
    // PinPermutation.h) to try a different CS/DC/RST/MOSI/SCK assignment
    // without tearing down and reconstructing the whole SPIBus/driver
    // object graph. Every previously-used pin is first released to a
    // floating input, since under a permutation sweep today's SCK pin may
    // have been yesterday's CS pin and must not be left driven while it's
    // reassigned. Pass rstPin = -1 if this permutation has no dedicated
    // reset line.
    void reconfigurePins(int8_t csPin,
                          int8_t dcPin,
                          int8_t rstPin,
                          int8_t mosiPin,
                          int8_t sckPin);

    // Pulses the hardware RST line: HIGH -> LOW (20ms) -> HIGH (150ms).
    // No-op if this bus was constructed with rstPin = -1.
    void reset() const;

    inline void csLow() const  { digitalWrite(_cs, LOW); }
    inline void csHigh() const { digitalWrite(_cs, HIGH); }
    inline void dcCommand() const { digitalWrite(_dc, LOW); }
    inline void dcData() const    { digitalWrite(_dc, HIGH); }

    // Sends a single command byte (DC = LOW).
    void writeCommand(uint8_t cmd) const;

    // Sends a single parameter/data byte (DC = HIGH).
    void writeData8(uint8_t data) const;

    // Sends an arbitrary data buffer (DC = HIGH) in one SPI transaction.
    void writeDataBuffer(const uint8_t* buffer, size_t len) const;

    // Sends one big-endian RGB565 pixel value.
    void writeData16(uint16_t data) const;

    // Streams `count` repetitions of a single RGB565 color. Used by
    // fillScreen(). Uses a small static chunk buffer so no heap allocation
    // ever occurs, regardless of how many pixels are requested.
    void writeColorRun(uint16_t color, uint32_t count) const;

    int8_t csPinNum() const   { return _cs; }
    int8_t dcPinNum() const   { return _dc; }
    int8_t rstPinNum() const  { return _rst; }
    int8_t mosiPinNum() const { return _mosi; }
    int8_t sckPinNum() const  { return _sck; }

private:
    // Sets a pin back to a floating input if it's actually wired (>= 0).
    // No-op for -1 "not connected" placeholders.
    static void releasePin(int8_t pin);

    SPIClass& _spi;
    int8_t _cs;
    int8_t _dc;
    int8_t _rst;
    int8_t _mosi;
    int8_t _sck;
    uint32_t _freq;
    SPISettings _settings;
};

} // namespace tft
