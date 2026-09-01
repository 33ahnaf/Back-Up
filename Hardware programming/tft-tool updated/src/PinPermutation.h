#pragma once
// ============================================================================
// PinPermutation
//
// Supports "blind" pin-wiring discovery: instead of trusting that the CS/
// DC/RST/MOSI/SCK assignment in main.cpp's `pins` namespace is correct,
// ENABLE_PIN_PERMUTATION_TEST reassigns the same *pool* of five physical
// GPIOs across all five roles, one permutation at a time, and reports each
// one over Serial. If a panel lights up correctly under some permutation
// other than the "labelled" one, that tells you the wiring diagram (or the
// silkscreen on the panel) doesn't match reality, and exactly how to fix it.
//
// Five roles -> 5! = 120 permutations when RST has a dedicated GPIO.
// If RST is tied directly to 3V3/EN (rstPin < 0), it isn't a real signal to
// shuffle, so it's held fixed at -1 and only the remaining four roles
// (CS/DC/MOSI/SCK) are permuted -> 4! = 24 permutations instead.
// ============================================================================

#include <Arduino.h>

namespace tft {

// One candidate physical-pin assignment for the five TFT signal roles.
struct PinConfig {
    int8_t cs   = -1;
    int8_t dc   = -1;
    int8_t rst  = -1;
    int8_t mosi = -1;
    int8_t sck  = -1;
};

class PinPermutation {
public:
    // basePins: the pool of physical GPIOs to shuffle, taken directly from
    // the `pins` namespace in main.cpp. Order within basePins doesn't
    // matter beyond determining basePins.rst < 0 (fixed) vs >= 0 (shuffled).
    explicit PinPermutation(const PinConfig& basePins);

    // 120 when all five roles have a real GPIO, 24 when RST is fixed at -1.
    size_t count() const { return _count; }

    // Returns the pin assignment for permutation index i, where
    // 0 <= i < count(). Every index in that range maps to a distinct
    // ordering of the pool; the mapping is computed directly (factorial
    // number system / Lehmer code), so this is cheap to call every
    // iteration and needs no stored/generated table.
    PinConfig permutationAt(size_t i) const;

private:
    int8_t _pool[5];
    uint8_t _n;
    bool _rstFixed;
    size_t _count;
};

} // namespace tft
