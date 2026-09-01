// ============================================================================
// Universal SPI TFT Auto-Detection Tool
// Target: ESP32-WROOM-32 (Arduino / PlatformIO)
//
// Wire up an unknown SPI TFT panel (CS, DC, MOSI, SCK, RST - no MISO
// required) using the pin definitions below, flash this project, and watch
// the serial monitor + the panel itself: the tool cycles through every
// supported controller driver, every rotation, both color orders, and both
// inversion states, filling the screen with a known color sequence at each
// combination. Whichever combination makes the panel display correct,
// non-garbled colors identifies the controller and the correct runtime
// configuration to use going forward.
// ============================================================================

#include <Arduino.h>
#include "SPIBus.h"
#include "Display.h"
#include "Utilities.h"
#include "PinPermutation.h"

#include "drivers/ILI9341.h"
#include "drivers/ILI9486.h"
#include "drivers/ILI9488.h"
#include "drivers/ST7735.h"
#include "drivers/ST7789.h"
#include "drivers/HX8357.h"
#include "drivers/GC9A01.h"

// ============================================================================
// PIN CONFIGURATION - edit these to match your wiring.
// All five signals are required except RST (set to -1 if RST is tied
// directly to 3V3/EN instead of a GPIO; software reset will be used
// exclusively in that case).
// ============================================================================
namespace pins {
    constexpr int8_t CS   = 5;
    constexpr int8_t DC   = 2;
    constexpr int8_t RST  = 4;
    constexpr int8_t MOSI = 23;
    constexpr int8_t SCK  = 18;
}

// ---- Bus + driver instances -------------------------------------------------
// A single SPIBus is shared by every driver instance: the bus itself has no
// controller-specific state, so it never needs to be re-created when the
// tester switches from one driver to the next.
static tft::SPIBus g_bus(pins::CS, pins::DC, pins::RST, pins::MOSI, pins::SCK);

static tft::ILI9341 g_ili9341(g_bus);
static tft::ILI9486 g_ili9486(g_bus);
static tft::ILI9488 g_ili9488(g_bus);
static tft::ST7735  g_st7735(g_bus);
static tft::ST7789  g_st7789(g_bus);
static tft::HX8357  g_hx8357(g_bus);
static tft::GC9A01  g_gc9a01(g_bus);

// The order here is the order drivers are tried in, every sweep, forever.
static tft::DriverBase* const g_drivers[] = {
    &g_ili9341,
    &g_ili9486,
    &g_ili9488,
    &g_st7735,
    &g_st7789,
    &g_hx8357,
    &g_gc9a01,
};

static constexpr size_t g_driverCount = sizeof(g_drivers) / sizeof(g_drivers[0]);

// basePins is the pool of GPIOs the pin-permutation sweep (see
// PinPermutation.h) shuffles across CS/DC/RST/MOSI/SCK when
// ENABLE_PIN_PERMUTATION_TEST is set. Harmless to build/pass unconditionally
// - it's simply unused when that flag is off.
static const tft::PinConfig g_basePins{
    pins::CS, pins::DC, pins::RST, pins::MOSI, pins::SCK
};

static tft::Display g_display(g_bus, g_drivers, g_driverCount, g_basePins);

void setup() {
    // Serial needs to come up under either flag: ENABLE_SERIAL_LOG for the
    // full verbose per-step log, ENABLE_PIN_PERMUTATION_TEST because
    // announcing the active pin permutation on Serial is the entire point
    // of that mode (see logPinPermutation()).
#if defined(ENABLE_SERIAL_LOG) || defined(ENABLE_PIN_PERMUTATION_TEST)
    Serial.begin(115200);
    // Give the host-side serial monitor time to attach before the first
    // banner is printed; harmless if nothing is listening.
    delay(300);
#endif

#if defined(ENABLE_SERIAL_LOG)
    Serial.println();
    Serial.println(F("Universal SPI TFT Auto-Detection Tool"));
    Serial.print(F("Drivers under test : "));
    Serial.println(g_driverCount);
    Serial.print(F("SPI frequency (Hz) : "));
    Serial.println(tft::kDefaultSPIFrequency);
    Serial.println(F("Pins -> CS/DC/RST/MOSI/SCK configured in main.cpp"));
#endif

#if defined(ENABLE_PIN_PERMUTATION_TEST)
    Serial.print(F("Pin permutation sweep ENABLED - "));
    Serial.print(tft::PinPermutation(g_basePins).count());
    Serial.println(F(" combinations of the pin pool below will be tried."));
    Serial.print(F("Pool: CS/DC/RST/MOSI/SCK = "));
    Serial.print(pins::CS);   Serial.print(F("/"));
    Serial.print(pins::DC);   Serial.print(F("/"));
    Serial.print(pins::RST);  Serial.print(F("/"));
    Serial.print(pins::MOSI); Serial.print(F("/"));
    Serial.println(pins::SCK);
#endif

    g_display.begin(tft::kDefaultSPIFrequency);
}

void loop() {
    // The entire test program lives inside runForever(): reset, initialize,
    // sweep rotation/color-order/inversion, fill colors, repeat - forever,
    // never blocking on user input, never halting on a failed/absent panel.
    g_display.runForever();
}
