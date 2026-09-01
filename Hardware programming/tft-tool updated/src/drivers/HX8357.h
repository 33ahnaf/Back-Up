#pragma once
#include "../DriverBase.h"

namespace tft {

// HX8357 (HX8357-B/C/D family): 320x480, common on larger 3.5" shields.
class HX8357 : public DriverBase {
public:
    explicit HX8357(SPIBus& bus);

    const char* name() const override { return "HX8357"; }

protected:
    void initSequence() override;
};

} // namespace tft
