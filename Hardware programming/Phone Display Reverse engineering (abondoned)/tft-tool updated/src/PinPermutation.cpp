#include "PinPermutation.h"

namespace tft {

namespace {
constexpr size_t kFactorial[6] = {1, 1, 2, 6, 24, 120};
} // namespace

PinPermutation::PinPermutation(const PinConfig& basePins) {
    _rstFixed = (basePins.rst < 0);

    if (_rstFixed) {
        _n = 4;
        _pool[0] = basePins.cs;
        _pool[1] = basePins.dc;
        _pool[2] = basePins.mosi;
        _pool[3] = basePins.sck;
        _pool[4] = -1; // unused
    } else {
        _n = 5;
        _pool[0] = basePins.cs;
        _pool[1] = basePins.dc;
        _pool[2] = basePins.rst;
        _pool[3] = basePins.mosi;
        _pool[4] = basePins.sck;
    }

    _count = kFactorial[_n];
}

PinConfig PinPermutation::permutationAt(size_t i) const {
    // Factorial number system: decode index i (0 <= i < n!) into the
    // unique ordering of _pool it represents. At each of the n slots we
    // pick the (idx / (n-1-slot)!)-th item still remaining in the pool,
    // then remove it and continue with the remainder - n steps total, no
    // search and no need to materialize all n! orderings up front.
    int8_t remaining[5];
    for (uint8_t k = 0; k < _n; ++k) {
        remaining[k] = _pool[k];
    }
    uint8_t remainingCount = _n;

    int8_t ordered[5] = {-1, -1, -1, -1, -1};
    size_t idx = (_count == 0) ? 0 : (i % _count);

    for (uint8_t slot = 0; slot < _n; ++slot) {
        const size_t placeValue = kFactorial[_n - 1 - slot];
        const size_t pick = idx / placeValue;
        idx %= placeValue;

        ordered[slot] = remaining[pick];
        for (uint8_t k = pick; k + 1 < remainingCount; ++k) {
            remaining[k] = remaining[k + 1];
        }
        --remainingCount;
    }

    PinConfig cfg;
    if (_rstFixed) {
        cfg.cs   = ordered[0];
        cfg.dc   = ordered[1];
        cfg.rst  = -1;
        cfg.mosi = ordered[2];
        cfg.sck  = ordered[3];
    } else {
        cfg.cs   = ordered[0];
        cfg.dc   = ordered[1];
        cfg.rst  = ordered[2];
        cfg.mosi = ordered[3];
        cfg.sck  = ordered[4];
    }
    return cfg;
}

} // namespace tft
