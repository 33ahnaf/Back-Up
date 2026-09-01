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
    // When ENABLE_PIN_PERMUTATION_TEST is set, this instead becomes an
    // interactive, single-stepped sweep over every permutation of the
    // CS/DC/RST/MOSI/SCK pin pool (120 permutations, or 24 if RST is fixed
    // at -1 - see PinPermutation.h):
    //   1. On entry, it blocks and asks over Serial which permutation index
    //      to start checking from (blank input defaults to 0).
    //   2. It applies that permutation to the bus, announces it via
    //      logPinPermutation(), and runs one full driver/rotation/
    //      color-order/invert/color sweep so the panel can be inspected.
    //   3. It then blocks, waiting for a lone 'n' byte on Serial before
    //      advancing to the next permutation (wrapping back to 0 after the
    //      last one) and repeating from step 2 - so the sweep only ever
    //      moves forward one permutation at a time, on demand, rather than
    //      running unattended.
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
