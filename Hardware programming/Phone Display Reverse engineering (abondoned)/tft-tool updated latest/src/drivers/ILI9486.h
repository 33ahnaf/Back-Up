#pragma once
#include "../DriverBase.h"

namespace tft {

// ILI9486: 320x480, common on 3.5" TFT shields.
class ILI9486 : public DriverBase {
public:
    explicit ILI9486(SPIBus& bus);

    const char* name() const override { return "ILI9486"; }

protected:
    void initSequence() override;
};

} // namespace tft
