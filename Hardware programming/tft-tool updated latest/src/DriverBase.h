#pragma once
// ============================================================================
// DriverBase
//
// Abstract base class for every supported LCD controller. Concrete drivers
// (ILI9341, ILI9486, ILI9488, ST7735, ST7789, HX8357, GC9A01) only need to
// supply their controller-specific power-up register sequence via
// initSequence(); everything else (address window, fill, rotation, color
// order, inversion) is implemented once here since the MIPI-DBI command set
// (0x2A/0x2B/0x2C/0x36/0x3A/...) is shared across all of them.
//
// This is what allows the tester to reset the panel and swap to a
// completely different controller object at runtime, without recompiling -
// something TFT_eSPI's compile-time driver selection cannot do.
// ============================================================================

#include <Arduino.h>
#include "SPIBus.h"

namespace tft {

class DriverBase {
public:
    DriverBase(SPIBus& bus, uint16_t nativeWidth, uint16_t nativeHeight);
    virtual ~DriverBase() = default;

    // Human readable controller name, used only for serial logging.
    virtual const char* name() const = 0;

    // Pulses the physical RST pin (delegates to SPIBus::reset()). Call this
    // before initialize() when probing a new/unknown controller.
    void hardwareReset() const;

    // Sends the controller's software-reset command (0x01) and waits for it
    // to settle. Automatically invoked by initialize().
    virtual void softwareReset();

    // Runs the full controller-specific power-up sequence (initSequence()),
    // exits sleep mode, resets rotation/color-order/inversion to sane
    // defaults, and turns the display on. Safe to call repeatedly.
    void initialize();

    // ---- Runtime configuration --------------------------------------------
    // rotation: 0=portrait, 1=landscape, 2=portrait flipped, 3=landscape
    // flipped, matching the conventional Adafruit_GFX rotation numbering.
    virtual void setRotation(uint8_t rotation);
    void setColorOrder(bool bgr);
    void setInversion(bool invertOn);

    // ---- Drawing ------------------------------------------------------------
    // Programs CASET/RASET/RAMWR so that the next stream of pixel data lands
    // in the [x0,x1] x [y0,y1] inclusive rectangle (in the *current*
    // rotation's coordinate space).
    void setAddressWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1) const;

    // Fills the entire visible screen (accounting for current rotation)
    // with a single RGB565 color.
    void fillScreen(uint16_t color565);

    // Streams an arbitrary array of RGB565 pixels to whatever address
    // window is currently active (caller must have already called
    // setAddressWindow()). Used by Patterns.cpp for non-solid test
    // patterns. Converts to big-endian on the fly using a small reused
    // static buffer - no heap allocation.
    void writePixels(const uint16_t* colors, uint32_t count) const;

    // ---- Raw command/data passthrough --------------------------------------
    void sendCommand(uint8_t cmd) const;
    void sendData(uint8_t data) const;
    void sendData(const uint8_t* data, size_t len) const;

    virtual void sleepOut();
    virtual void displayOn();

    // Effective panel dimensions, with width/height swapped automatically
    // for landscape rotations (1 and 3).
    uint16_t width() const;
    uint16_t height() const;

    uint8_t rotation() const     { return _rotation; }
    bool colorOrderBGR() const   { return _bgr; }
    bool inverted() const        { return _inverted; }
    uint16_t nativeWidth() const  { return _nativeWidth; }
    uint16_t nativeHeight() const { return _nativeHeight; }

protected:
    // Every concrete driver implements exactly this: the sequence of
    // commands/parameters that brings the panel out of power-on reset into
    // a known, addressable RGB565 state. Called once per initialize().
    virtual void initSequence() = 0;

    // Computes the MADCTL (0x36) parameter byte for a given rotation and
    // color order. The default mapping below matches the convention used by
    // the vast majority of ILI/ST/HX/GC panels; a handful of drivers
    // (ST7735, GC9A01) override this because their silkscreened orientation
    // differs from the ILI9341 reference layout.
    virtual uint8_t madctlValue(uint8_t rotation, bool bgr) const;

    SPIBus& _bus;
    uint16_t _nativeWidth;
    uint16_t _nativeHeight;
    uint8_t _rotation;
    bool _bgr;
    bool _inverted;

    // ---- Shared MIPI-DBI Type-B command set --------------------------------
    static constexpr uint8_t CMD_NOP     = 0x00;
    static constexpr uint8_t CMD_SWRESET = 0x01;
    static constexpr uint8_t CMD_SLPIN   = 0x10;
    static constexpr uint8_t CMD_SLPOUT  = 0x11;
    static constexpr uint8_t CMD_PTLON   = 0x12;
    static constexpr uint8_t CMD_NORON   = 0x13;
    static constexpr uint8_t CMD_INVOFF  = 0x20;
    static constexpr uint8_t CMD_INVON   = 0x21;
    static constexpr uint8_t CMD_GAMSET  = 0x26;
    static constexpr uint8_t CMD_DISPOFF = 0x28;
    static constexpr uint8_t CMD_DISPON  = 0x29;
    static constexpr uint8_t CMD_CASET   = 0x2A;
    static constexpr uint8_t CMD_RASET   = 0x2B;
    static constexpr uint8_t CMD_RAMWR   = 0x2C;
    static constexpr uint8_t CMD_MADCTL  = 0x36;
    static constexpr uint8_t CMD_COLMOD  = 0x3A;

    // ---- MADCTL (0x36) bit definitions -------------------------------------
    static constexpr uint8_t MADCTL_MY  = 0x80; // Row address order
    static constexpr uint8_t MADCTL_MX  = 0x40; // Column address order
    static constexpr uint8_t MADCTL_MV  = 0x20; // Row/Column exchange
    static constexpr uint8_t MADCTL_ML  = 0x10; // Vertical refresh order
    static constexpr uint8_t MADCTL_BGR = 0x08; // RGB/BGR pixel order
    static constexpr uint8_t MADCTL_MH  = 0x04; // Horizontal refresh order
};

} // namespace tft
