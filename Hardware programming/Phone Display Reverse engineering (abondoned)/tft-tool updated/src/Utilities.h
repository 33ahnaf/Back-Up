#pragma once
// ============================================================================
// Utilities
//
// RGB565 color-conversion helpers, compile-time SPI speed selection, and
// serial logging helpers used throughout the tester. Everything here is
// constexpr/inline where possible so it costs nothing at runtime.
// ============================================================================

#include <Arduino.h>
#include "SPIBus.h"
#include "PinPermutation.h"

namespace tft {

// ---- RGB565 color conversion ----------------------------------------------

// Packs 8-bit-per-channel color into RGB565 (5 red / 6 green / 5 blue).
constexpr uint16_t rgb888to565(uint8_t r, uint8_t g, uint8_t b) {
    return static_cast<uint16_t>(((r & 0xF8) << 8) |
                                  ((g & 0xFC) << 3) |
                                  ((b & 0xF8) >> 3));
}

// Unpacks an RGB565 value back to approximate 8-bit-per-channel components.
inline void rgb565to888(uint16_t color, uint8_t& r, uint8_t& g, uint8_t& b) {
    r = static_cast<uint8_t>((color >> 11) & 0x1F) << 3;
    g = static_cast<uint8_t>((color >> 5) & 0x3F) << 2;
    b = static_cast<uint8_t>(color & 0x1F) << 3;
}

// Linear interpolation between two RGB565 colors, t in [0, 255].
inline uint16_t lerp565(uint16_t from, uint16_t to, uint8_t t) {
    uint8_t r0, g0, b0, r1, g1, b1;
    rgb565to888(from, r0, g0, b0);
    rgb565to888(to, r1, g1, b1);
    const uint8_t r = static_cast<uint8_t>(r0 + (((int32_t)(r1 - r0) * t) / 255));
    const uint8_t g = static_cast<uint8_t>(g0 + (((int32_t)(g1 - g0) * t) / 255));
    const uint8_t b = static_cast<uint8_t>(b0 + (((int32_t)(b1 - b0) * t) / 255));
    return rgb888to565(r, g, b);
}

// Standard test colors, precomputed at compile time.
namespace Colors {
    constexpr uint16_t RED    = rgb888to565(255, 0, 0);
    constexpr uint16_t GREEN  = rgb888to565(0, 255, 0);
    constexpr uint16_t BLUE   = rgb888to565(0, 0, 255);
    constexpr uint16_t WHITE  = rgb888to565(255, 255, 255);
    constexpr uint16_t BLACK  = rgb888to565(0, 0, 0);
    constexpr uint16_t YELLOW = rgb888to565(255, 255, 0);
    constexpr uint16_t CYAN   = rgb888to565(0, 255, 255);
    constexpr uint16_t MAGENTA = rgb888to565(255, 0, 255);
    constexpr uint16_t GRAY   = rgb888to565(128, 128, 128);
}

// ---- Compile-time SPI speed selection --------------------------------------
// ENABLE_SLOW_SPI / ENABLE_FAST_SPI (platformio.ini build_flags) override the
// default 26 MHz "safe middle ground" speed used for auto-detection, where
// wiring quality is unknown up front.
#if defined(ENABLE_SLOW_SPI)
    constexpr uint32_t kDefaultSPIFrequency = static_cast<uint32_t>(SPISpeed::MHz8);
#elif defined(ENABLE_FAST_SPI)
    constexpr uint32_t kDefaultSPIFrequency = static_cast<uint32_t>(SPISpeed::MHz40);
#else
    constexpr uint32_t kDefaultSPIFrequency = static_cast<uint32_t>(SPISpeed::MHz26);
#endif

// ---- Serial logging ---------------------------------------------------------
// Wrapped in macros (rather than always-on Serial.print calls) so the whole
// logging subsystem compiles out to nothing when ENABLE_SERIAL_LOG is not
// defined, saving flash/time on a "quiet" build.
#if defined(ENABLE_SERIAL_LOG)
    #define TFT_LOG(...)      Serial.print(__VA_ARGS__)
    #define TFT_LOGLN(...)    Serial.println(__VA_ARGS__)
    #define TFT_LOGF(...)     Serial.printf(__VA_ARGS__)
#else
    #define TFT_LOG(...)      do {} while (0)
    #define TFT_LOGLN(...)    do {} while (0)
    #define TFT_LOGF(...)     do {} while (0)
#endif

// The pin-permutation banner is deliberately on its own switch: it's the
// entire point of ENABLE_PIN_PERMUTATION_TEST (you cannot use that mode
// usefully without seeing which permutation is currently wired), so it
// prints whenever that flag is set even if ENABLE_SERIAL_LOG's more verbose
// per-color logging is not also enabled. main.cpp starts Serial under the
// same condition.
#if defined(ENABLE_SERIAL_LOG) || defined(ENABLE_PIN_PERMUTATION_TEST)
    #define TFT_PIN_LOG(...)   Serial.print(__VA_ARGS__)
    #define TFT_PIN_LOGLN(...) Serial.println(__VA_ARGS__)
#else
    #define TFT_PIN_LOG(...)   do {} while (0)
    #define TFT_PIN_LOGLN(...) do {} while (0)
#endif

// Prints the "====== Driver: X / Rotation: Y / ... ======" banner described
// in the project spec.
void logTestBanner(const char* driverName, uint8_t rotation, bool bgr, bool invert);

// Prints a single color-name line (e.g. "RED") during a fill test.
void logColorStep(const char* colorName);

// Prints which pin permutation (1-based, out of `total`) is currently
// active and the physical GPIO -> role mapping it represents, e.g.:
//   ===== PIN PERMUTATION 47 / 120 =====
//   CS=18  DC=23  RST=-1  MOSI=5  SCK=2
void logPinPermutation(size_t index, size_t total, const PinConfig& cfg);

} // namespace tft
