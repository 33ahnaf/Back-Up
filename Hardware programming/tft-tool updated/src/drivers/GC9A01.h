#pragma once
#include "../DriverBase.h"

namespace tft {

// GC9A01: 240x240 round LCD (the common 1.28" "smartwatch" panel).
// Requires a vendor-specific unlock sequence (0xFE/0xEF) before any other
// register writes are accepted, and uses its own MADCTL orientation
// mapping.
class GC9A01 : public DriverBase {
public:
    explicit GC9A01(SPIBus& bus);

    const char* name() const override { return "GC9A01"; }

protected:
    void initSequence() override;
    uint8_t madctlValue(uint8_t rotation, bool bgr) const override;
};

} // namespace tft
