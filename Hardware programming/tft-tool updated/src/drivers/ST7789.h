#pragma once
#include "../DriverBase.h"

namespace tft {

// ST7789: 240x320 (also very commonly sold as 240x240 / 135x240 variants;
// the extra rows/columns are simply clipped off-panel on smaller glass, so
// using the larger 240x320 window here is safe for auto-detection purposes).
class ST7789 : public DriverBase {
public:
    explicit ST7789(SPIBus& bus);

    const char* name() const override { return "ST7789"; }

protected:
    void initSequence() override;
};

} // namespace tft
