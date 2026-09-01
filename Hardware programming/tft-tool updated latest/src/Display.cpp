#include "Display.h"
#include "Utilities.h"

#if defined(ENABLE_PATTERN_TESTS)
#include "Patterns.h"
#endif

#if defined(ENABLE_PIN_PERMUTATION_TEST)
namespace {

// Blocks until a non-empty line (terminated by '\n' or '\r') has been
// received on Serial, then returns it trimmed of whitespace. Bare CR/LF
// line-ending bytes with nothing before them are skipped rather than
// returned as an "empty" line, so CRLF terminals don't short-circuit the
// prompt with a blank answer.
String readSerialLine() {
    String line;
    for (;;) {
        while (!Serial.available()) {
            delay(5);
        }
        const char c = static_cast<char>(Serial.read());
        if (c == '\n' || c == '\r') {
            if (line.length() > 0) {
                break;
            }
            continue;
        }
        line += c;
    }
    line.trim();
    return line;
}

// Blocking prompt, asked once on entry to the pin-permutation sweep: which
// permutation index (0-based) should the sweep start checking from? Blank
// input defaults to 0. Re-prompts on non-numeric or out-of-range input.
size_t promptForStartIndex(size_t total) {
    Serial.println();
    Serial.println(F("===================================="));
    Serial.print(F("Pin permutation sweep: "));
    Serial.print(total);
    Serial.println(F(" combinations available."));

    for (;;) {
        Serial.print(F("Enter permutation index to start at (0-"));
        Serial.print(total - 1);
        Serial.println(F("), or press Enter for 0:"));

        const String line = readSerialLine();
        if (line.length() == 0) {
            return 0;
        }

        bool numeric = true;
        for (size_t i = 0; i < line.length(); ++i) {
            if (!isDigit(line[i])) {
                numeric = false;
                break;
            }
        }
        if (!numeric) {
            Serial.println(F("Please enter a plain number."));
            continue;
        }

        const long value = line.toInt();
        if (value < 0 || static_cast<size_t>(value) >= total) {
            Serial.println(F("Out of range, try again."));
            continue;
        }
        return static_cast<size_t>(value);
    }
}

// Blocks until a lone 'n'/'N' byte is received on Serial; everything else
// received while waiting is silently discarded. This is what turns the
// permutation sweep from automatic into single-step: nothing advances to
// the next permutation until this returns.
void waitForNextCommand() {
    Serial.println(F("Send 'n' to advance to the next permutation..."));
    for (;;) {
        while (!Serial.available()) {
            delay(5);
        }
        const char c = static_cast<char>(Serial.read());
        if (c == 'n' || c == 'N') {
            // Swallow a trailing CR/LF that may have arrived alongside it
            // (e.g. typed 'n' + Enter in a serial monitor) so it isn't
            // misread as input by whatever prompts next.
            while (Serial.available()) {
                const char next = static_cast<char>(Serial.peek());
                if (next == '\n' || next == '\r') {
                    Serial.read();
                } else {
                    break;
                }
            }
            return;
        }
        // Anything other than 'n'/'N' is ignored - only that byte advances
        // the sweep.
    }
}

} // namespace
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
    const size_t total = _pinPermutation.count();
    size_t i = promptForStartIndex(total);

    for (;;) {
        const PinConfig cfg = _pinPermutation.permutationAt(i);
        // Even a "wrong" permutation is safe to drive: every role here
        // is push-pull output-only (no MISO), so worst case is nothing
        // visible happens on the panel and the sweep moves on, exactly
        // like an absent/miswired panel already does in the base tool.
        _bus.reconfigurePins(cfg.cs, cfg.dc, cfg.rst, cfg.mosi, cfg.sck);
        logPinPermutation(i, total, cfg);
        runFullSweepOnce();

        // Single-step: hold here until the user explicitly asks to move
        // on, rather than sweeping unattended.
        waitForNextCommand();
        i = (i + 1) % total;
    }
#else
    for (;;) {
        runFullSweepOnce();
    }
#endif
}

} // namespace tft
