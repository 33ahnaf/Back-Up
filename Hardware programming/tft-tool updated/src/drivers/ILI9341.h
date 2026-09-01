#pragma once
#include "../DriverBase.h"

namespace tft {

// ILI9341: 240x320, extremely common (2.2"-2.8" "HX8347/ILI9341" boards).
class ILI9341 : public DriverBase {
public:
    explicit ILI9341(SPIBus& bus);

    const char* name() const override { return "ILI9341"; }

protected:
    void initSequence() override;
};

} // namespace tft
