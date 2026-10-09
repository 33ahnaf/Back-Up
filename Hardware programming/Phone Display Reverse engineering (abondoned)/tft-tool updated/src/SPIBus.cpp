#include "SPIBus.h"

namespace tft {

SPIBus::SPIBus(int8_t csPin,
               int8_t dcPin,
               int8_t rstPin,
               int8_t mosiPin,
               int8_t sckPin,
               SPIClass& spi)
    : _spi(spi),
      _cs(csPin),
      _dc(dcPin),
      _rst(rstPin),
      _mosi(mosiPin),
      _sck(sckPin),
      _freq(static_cast<uint32_t>(SPISpeed::MHz40)),
      _settings(_freq, MSBFIRST, SPI_MODE0)
{
}

void SPIBus::begin(uint32_t frequency) {
    pinMode(_cs, OUTPUT);
    pinMode(_dc, OUTPUT);
    digitalWrite(_cs, HIGH);
    digitalWrite(_dc, HIGH);

    if (_rst >= 0) {
        pinMode(_rst, OUTPUT);
        digitalWrite(_rst, HIGH);
    }

    // No MISO: pass -1 so the ESP32 SPI driver does not reserve/configure
    // a MISO pin at all.
    _spi.begin(_sck, -1, _mosi, _cs);
    setFrequency(frequency);
}

void SPIBus::setFrequency(uint32_t frequency) {
    _freq = frequency;
    _settings = SPISettings(_freq, MSBFIRST, SPI_MODE0);
}

void SPIBus::releasePin(int8_t pin) {
    if (pin >= 0) {
        pinMode(pin, INPUT);
    }
}

void SPIBus::reconfigurePins(int8_t csPin,
                              int8_t dcPin,
                              int8_t rstPin,
                              int8_t mosiPin,
                              int8_t sckPin) {
    // Let go of every GPIO this bus currently owns before reassigning
    // roles. Under a permutation sweep the same physical pin can move from
    // (say) CS to SCK between iterations; leaving it actively driven as an
    // OUTPUT would fight whatever it's about to become, and floating it
    // first is cheap insurance either way.
    releasePin(_cs);
    releasePin(_dc);
    releasePin(_rst);
    // _mosi/_sck are relinquished by the SPI peripheral itself in end().

    _spi.end();

    _cs   = csPin;
    _dc   = dcPin;
    _rst  = rstPin;
    _mosi = mosiPin;
    _sck  = sckPin;

    pinMode(_cs, OUTPUT);
    pinMode(_dc, OUTPUT);
    digitalWrite(_cs, HIGH);
    digitalWrite(_dc, HIGH);

    if (_rst >= 0) {
        pinMode(_rst, OUTPUT);
        digitalWrite(_rst, HIGH);
    }

    _spi.begin(_sck, -1, _mosi, _cs);
    setFrequency(_freq);
}

void SPIBus::reset() const {
    if (_rst < 0) {
        // No dedicated hardware reset line wired - caller must rely on the
        // controller's software reset command (0x01) instead.
        return;
    }
    digitalWrite(_rst, HIGH);
    delay(10);
    digitalWrite(_rst, LOW);
    delay(20);
    digitalWrite(_rst, HIGH);
    delay(150);
}

void SPIBus::writeCommand(uint8_t cmd) const {
    _spi.beginTransaction(_settings);
    csLow();
    dcCommand();
    _spi.transfer(cmd);
    csHigh();
    _spi.endTransaction();
}

void SPIBus::writeData8(uint8_t data) const {
    _spi.beginTransaction(_settings);
    csLow();
    dcData();
    _spi.transfer(data);
    csHigh();
    _spi.endTransaction();
}

void SPIBus::writeDataBuffer(const uint8_t* buffer, size_t len) const {
    if (len == 0 || buffer == nullptr) {
        return;
    }
    _spi.beginTransaction(_settings);
    csLow();
    dcData();
    // transferBytes() performs a raw, allocation-free burst write; the
    // received-data pointer is left null since these controllers are
    // write-only from the MCU's perspective (no MISO wired).
    _spi.transferBytes(const_cast<uint8_t*>(buffer), nullptr,
                        static_cast<uint32_t>(len));
    csHigh();
    _spi.endTransaction();
}

void SPIBus::writeData16(uint16_t data) const {
    uint8_t buf[2] = {
        static_cast<uint8_t>(data >> 8),
        static_cast<uint8_t>(data & 0xFF)
    };
    writeDataBuffer(buf, 2);
}

void SPIBus::writeColorRun(uint16_t color, uint32_t count) const {
    // Fixed-size, reused chunk buffer -> zero heap allocation regardless of
    // how many pixels are requested. 64 pixels = 128 bytes, small enough to
    // sit comfortably on the stack/BSS and still give good SPI throughput.
    static constexpr uint32_t kChunkPixels = 64;
    static uint8_t chunk[kChunkPixels * 2];

    const uint8_t hi = static_cast<uint8_t>(color >> 8);
    const uint8_t lo = static_cast<uint8_t>(color & 0xFF);
    for (uint32_t i = 0; i < kChunkPixels; ++i) {
        chunk[i * 2]     = hi;
        chunk[i * 2 + 1] = lo;
    }

    if (count == 0) {
        return;
    }

    _spi.beginTransaction(_settings);
    csLow();
    dcData();

    uint32_t remaining = count;
    while (remaining > 0) {
        uint32_t pixelsThisPass = (remaining > kChunkPixels) ? kChunkPixels : remaining;
        _spi.transferBytes(chunk, nullptr, pixelsThisPass * 2);
        remaining -= pixelsThisPass;
    }

    csHigh();
    _spi.endTransaction();
}

} // namespace tft
