#include "Display.h"
#include "Utilities.h"

#if defined(ENABLE_PATTERN_TESTS)
#include "Patterns.h"
#endif

namespace tft {

Display::Display(SPIBus& bus, DriverBase* const* drivers, size_t driverCount,
                  const PinConfig& basePins)
    : _bus(bus), _drivers(drivers), _driverCount(driverCount),
      _pinPermutation(basePins)
{
}

void Display::begin(uint32_t spiFrequency) {
    _bus.begin(spiFrequency);
}

void Display::runColorSequence(DriverBase& driver) {
    struct ColorStep {
        uint16_t color;
        const char* name;
    };

    static const ColorStep steps[] = {
        { Colors::RED,   "RED"   },
        { Colors::GREEN, "GREEN" },
        { Colors::BLUE,  "BLUE"  },
        { Colors::WHITE, "WHITE" },
        { Colors::BLACK, "BLACK" },
    };

    for (const ColorStep& step : steps) {
        driver.fillScreen(step.color);
        logColorStep(step.name);
        delay(200);
    }

#if defined(ENABLE_PATTERN_TESTS)
    patterns::horizontalRGBBars(driver);
    delay(200);
    patterns::verticalRGBBars(driver);
    delay(200);
    patterns::checkerboard(driver);
    delay(200);
    patterns::diagonalLines(driver);
    delay(200);
    patterns::crosshair(driver);
    delay(200);
    patterns::gradient(driver, Colors::BLUE, Colors::YELLOW);
    delay(200);
    patterns::movingSquare(driver, 20, 1500);
#endif
}

void Display::testDriver(DriverBase& driver) {
    // "Hardware reset" then "Initialize" exactly as specified. Both steps
    // are wrapped so that a controller which is absent/miswired (i.e. every
    // SPI transaction is going nowhere) can never hang or crash the loop -
    // there is nothing here that blocks on a response, since these panels
    // have no MISO line to read status back from.
    driver.hardwareReset();
    driver.initialize();

#if defined(ENABLE_ROTATION_TEST)
    static constexpr uint8_t kRotations[] = {0, 1, 2, 3};
#else
    static constexpr uint8_t kRotations[] = {0};
#endif

#if defined(ENABLE_BGR_TEST)
    static constexpr bool kColorOrders[] = {false, true}; // RGB, then BGR
#else
    static constexpr bool kColorOrders[] = {false};
#endif

#if defined(ENABLE_INVERT_TEST)
    static constexpr bool kInversions[] = {false, true}; // OFF, then ON
#else
    static constexpr bool kInversions[] = {false};
#endif

    for (uint8_t rotation : kRotations) {
        driver.setRotation(rotation);

        for (bool bgr : kColorOrders) {
            driver.setColorOrder(bgr);

            for (bool invert : kInversions) {
                driver.setInversion(invert);

                logTestBanner(driver.name(), rotation, bgr, invert);
                runColorSequence(driver);
            }
        }
    }
}

void Display::runFullSweepOnce() {
    for (size_t i = 0; i < _driverCount; ++i) {
        DriverBase* driver = _drivers[i];
        if (driver == nullptr) {
            // Defensive: never dereference a null entry. Robustness
            // requirement - the tool must never crash regardless of how the
            // driver table was populated.
            continue;
        }
        testDriver(*driver);
    }
}

void Display::runForever() {
#if defined(ENABLE_PIN_PERMUTATION_TEST)
    for (;;) {
        const size_t total = _pinPermutation.count();
        for (size_t i = 37; i < total; ++i) {
            const PinConfig cfg = _pinPermutation.permutationAt(i);
            // Even a "wrong" permutation is safe to drive: every role here
            // is push-pull output-only (no MISO), so worst case is nothing
            // visible happens on the panel and the sweep moves on, exactly
            // like an absent/miswired panel already does in the base tool.
            _bus.reconfigurePins(cfg.cs, cfg.dc, cfg.rst, cfg.mosi, cfg.sck);
            logPinPermutation(i, total, cfg);
            runFullSweepOnce();
        }
    }
#else
    for (;;) {
        runFullSweepOnce();
    }
#endif
}

} // namespace tft
