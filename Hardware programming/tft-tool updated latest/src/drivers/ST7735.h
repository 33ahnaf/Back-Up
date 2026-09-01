#pragma once
#include "../DriverBase.h"

namespace tft {

// ST7735: 128x160, very common on small 1.8" boards. Overrides madctlValue()
// because the ST7735 reference orientation differs from the ILI9341-style
// default used elsewhere in this project.
class ST7735 : public DriverBase {
public:
    explicit ST7735(SPIBus& bus);

    const char* name() const override { return "ST7735"; }

protected:
    void initSequence() override;
    uint8_t madctlValue(uint8_t rotation, bool bgr) const override;
};

} // namespace tft
