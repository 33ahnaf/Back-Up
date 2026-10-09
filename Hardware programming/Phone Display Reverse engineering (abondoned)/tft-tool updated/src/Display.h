#pragma once
// ============================================================================
// Display
//
// Orchestrates the universal auto-detection test loop described in the
// project spec: for every known driver, reset + initialize the panel, then
// sweep rotation x color-order x inversion, filling RED/GREEN/BLUE/WHITE/
// BLACK at each combination - forever, without ever stopping for input or
// crashing on a bad/absent panel.
// ============================================================================

#include <Arduino.h>
#include "DriverBase.h"
#include "SPIBus.h"
#include "PinPermutation.h"

namespace tft {

class Display {
public:
    // drivers/driverCount: caller-owned array of driver pointers (typically
    // one statically-constructed instance per supported controller). This
    // class does not take ownership and allocates nothing itself.
    // basePins: the CS/DC/RST/MOSI/SCK GPIOs from main.cpp's `pins`
    // namespace, used as the pool for the pin-permutation sweep (see
    // PinPermutation.h). Harmless to pass even when
    // ENABLE_PIN_PERMUTATION_TEST is off - it's simply never consulted.
    Display(SPIBus& bus, DriverBase* const* drivers, size_t driverCount,
            const PinConfig& basePins);

    // Starts the SPI bus at the given frequency. Call once from setup().
    void begin(uint32_t spiFrequency);

    // Runs the full driver x rotation x color-order x invert x color sweep
    // exactly once, in order, over every configured driver, at whichever
    // pin assignment the bus currently has.
    void runFullSweepOnce();

    // Runs runFullSweepOnce() in an infinite loop. Never returns.
    //
    // When ENABLE_PIN_PERMUTATION_TEST is set, this additionally wraps that
    // loop in an outer sweep over every permutation of the CS/DC/RST/MOSI/
    // SCK pin pool (120 permutations, or 24 if RST is fixed at -1 - see
    // PinPermutation.h): every permutation is applied to the bus in turn,
    // announced on Serial via logPinPermutation(), and then exercised with
    // a full driver/rotation/color-order/invert/color sweep before moving
    // to the next one - so the tool can locate a correctly-wired panel even
    // when the CS/DC/RST/MOSI/SCK assignment documented in main.cpp doesn't
    // match the physical wiring.
    [[noreturn]] void runForever();

private:
    // Resets, initializes, and exercises a single driver across every
    // enabled rotation/color-order/invert combination.
    void testDriver(DriverBase& driver);

    // Fills RED -> GREEN -> BLUE -> WHITE -> BLACK, 200ms each, logging each
    // step, for the driver's *current* rotation/color-order/invert state.
    void runColorSequence(DriverBase& driver);

    SPIBus& _bus;
    DriverBase* const* _drivers;
    size_t _driverCount;
    PinPermutation _pinPermutation;
};

} // namespace tft
