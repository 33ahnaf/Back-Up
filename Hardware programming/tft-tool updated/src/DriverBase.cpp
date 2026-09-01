#include "DriverBase.h"

namespace tft {

DriverBase::DriverBase(SPIBus& bus, uint16_t nativeWidth, uint16_t nativeHeight)
    : _bus(bus),
      _nativeWidth(nativeWidth),
      _nativeHeight(nativeHeight),
      _rotation(0),
      _bgr(false),
      _inverted(false)
{
}

void DriverBase::hardwareReset() const {
    _bus.reset();
}

void DriverBase::softwareReset() {
    sendCommand(CMD_SWRESET);
    delay(150); // Per spec: allow the controller's internal reset to settle.
}

void DriverBase::initialize() {
    softwareReset();
    initSequence();
    sleepOut();
    setRotation(0);
    setColorOrder(false);
    setInversion(false);
    displayOn();
}

void DriverBase::sleepOut() {
    sendCommand(CMD_SLPOUT);
    delay(120);
}

void DriverBase::displayOn() {
    sendCommand(CMD_DISPON);
    delay(20);
}

void DriverBase::sendCommand(uint8_t cmd) const {
    _bus.writeCommand(cmd);
}

void DriverBase::sendData(uint8_t data) const {
    _bus.writeData8(data);
}

void DriverBase::sendData(const uint8_t* data, size_t len) const {
    _bus.writeDataBuffer(data, len);
}

uint8_t DriverBase::madctlValue(uint8_t rotation, bool bgr) const {
    uint8_t m = 0;
    switch (rotation & 0x03) {
        case 0: m = MADCTL_MX | MADCTL_MY;             break; // portrait
        case 1: m = MADCTL_MY | MADCTL_MV;             break; // landscape
        case 2: m = 0x00;                              break; // portrait flipped
        case 3: m = MADCTL_MX | MADCTL_MV;             break; // landscape flipped
        default: break;
    }
    if (bgr) {
        m |= MADCTL_BGR;
    }
    return m;
}

void DriverBase::setRotation(uint8_t rotation) {
    _rotation = rotation & 0x03;
    sendCommand(CMD_MADCTL);
    sendData(madctlValue(_rotation, _bgr));
}

void DriverBase::setColorOrder(bool bgr) {
    _bgr = bgr;
    // MADCTL packs color order and rotation into the same byte, so any
    // change to either must re-send the full combined value.
    sendCommand(CMD_MADCTL);
    sendData(madctlValue(_rotation, _bgr));
}

void DriverBase::setInversion(bool invertOn) {
    _inverted = invertOn;
    sendCommand(invertOn ? CMD_INVON : CMD_INVOFF);
}

void DriverBase::setAddressWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1) const {
    sendCommand(CMD_CASET);
    uint8_t caset[4] = {
        static_cast<uint8_t>(x0 >> 8), static_cast<uint8_t>(x0 & 0xFF),
        static_cast<uint8_t>(x1 >> 8), static_cast<uint8_t>(x1 & 0xFF)
    };
    sendData(caset, sizeof(caset));

    sendCommand(CMD_RASET);
    uint8_t raset[4] = {
        static_cast<uint8_t>(y0 >> 8), static_cast<uint8_t>(y0 & 0xFF),
        static_cast<uint8_t>(y1 >> 8), static_cast<uint8_t>(y1 & 0xFF)
    };
    sendData(raset, sizeof(raset));

    // RAMWR itself takes no parameters here; the caller streams pixel data
    // immediately afterward (see SPIBus::writeColorRun / fillScreen()).
    sendCommand(CMD_RAMWR);
}

void DriverBase::fillScreen(uint16_t color565) {
    const uint16_t w = width();
    const uint16_t h = height();
    setAddressWindow(0, 0, w - 1, h - 1);
    const uint32_t totalPixels = static_cast<uint32_t>(w) * static_cast<uint32_t>(h);
    _bus.writeColorRun(color565, totalPixels);
}

void DriverBase::writePixels(const uint16_t* colors, uint32_t count) const {
    // Reused static staging buffer - converts RGB565 values to big-endian
    // byte pairs in fixed-size chunks so arbitrarily long pixel streams
    // never require a heap allocation.
    static constexpr uint32_t kChunkPixels = 64;
    static uint8_t chunk[kChunkPixels * 2];

    uint32_t offset = 0;
    while (offset < count) {
        uint32_t pixelsThisPass = (count - offset > kChunkPixels) ? kChunkPixels : (count - offset);
        for (uint32_t i = 0; i < pixelsThisPass; ++i) {
            const uint16_t c = colors[offset + i];
            chunk[i * 2]     = static_cast<uint8_t>(c >> 8);
            chunk[i * 2 + 1] = static_cast<uint8_t>(c & 0xFF);
        }
        sendData(chunk, pixelsThisPass * 2);
        offset += pixelsThisPass;
    }
}

uint16_t DriverBase::width() const {
    return (_rotation == 1 || _rotation == 3) ? _nativeHeight : _nativeWidth;
}

uint16_t DriverBase::height() const {
    return (_rotation == 1 || _rotation == 3) ? _nativeWidth : _nativeHeight;
}

} // namespace tft
