#pragma once
#include "../DriverBase.h"

namespace tft {

// ILI9488: 320x480, 3.5"/4.0" panels. Natively supports 18-bit color but
// this driver programs it into the 16-bit RGB565 pixel format so the
// generic fillScreen()/writeColorRun() pixel pump works identically across
// every supported controller.
class ILI9488 : public DriverBase {
public:
    explicit ILI9488(SPIBus& bus);

    const char* name() const override { return "ILI9488"; }

protected:
    void initSequence() override;
};

} // namespace tft
