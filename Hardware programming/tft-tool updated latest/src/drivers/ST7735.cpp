#include "ST7735.h"

namespace tft {

namespace {
    constexpr uint8_t CMD_FRMCTR1 = 0xB1;
    constexpr uint8_t CMD_FRMCTR2 = 0xB2;
    constexpr uint8_t CMD_FRMCTR3 = 0xB3;
    constexpr uint8_t CMD_INVCTR  = 0xB4;
    constexpr uint8_t CMD_PWCTR1  = 0xC0;
    constexpr uint8_t CMD_PWCTR2  = 0xC1;
    constexpr uint8_t CMD_PWCTR3  = 0xC2;
    constexpr uint8_t CMD_PWCTR4  = 0xC3;
    constexpr uint8_t CMD_PWCTR5  = 0xC4;
    constexpr uint8_t CMD_VMCTR1  = 0xC5;
    constexpr uint8_t CMD_GMCTRP1 = 0xE0;
    constexpr uint8_t CMD_GMCTRN1 = 0xE1;
}

ST7735::ST7735(SPIBus& bus)
    : DriverBase(bus, 128, 160)
{
}

uint8_t ST7735::madctlValue(uint8_t rotation, bool bgr) const {
    uint8_t m = 0;
    switch (rotation & 0x03) {
        case 0: m = MADCTL_MX | MADCTL_MY;            break;
        case 1: m = MADCTL_MY | MADCTL_MV;            break;
        case 2: m = 0x00;                             break;
        case 3: m = MADCTL_MX | MADCTL_MV;            break;
        default: break;
    }
    // ST7735 modules are almost universally wired BGR internally; the
    // BGR/RGB test loop still toggles this bit explicitly so a genuine
    // RGB-wired panel is still detected correctly.
    if (bgr) {
        m |= MADCTL_BGR;
    }
    return m;
}

void ST7735::initSequence() {
    sendCommand(CMD_FRMCTR1);
    { uint8_t d[] = {0x01, 0x2C, 0x2D}; sendData(d, sizeof(d)); }

    sendCommand(CMD_FRMCTR2);
    { uint8_t d[] = {0x01, 0x2C, 0x2D}; sendData(d, sizeof(d)); }

    sendCommand(CMD_FRMCTR3);
    {
        uint8_t d[] = {0x01, 0x2C, 0x2D, 0x01, 0x2C, 0x2D};
        sendData(d, sizeof(d));
    }

    sendCommand(CMD_INVCTR);
    sendData(0x07);

    sendCommand(CMD_PWCTR1);
    { uint8_t d[] = {0xA2, 0x02, 0x84}; sendData(d, sizeof(d)); }

    sendCommand(CMD_PWCTR2);
    sendData(0xC5);

    sendCommand(CMD_PWCTR3);
    { uint8_t d[] = {0x0A, 0x00}; sendData(d, sizeof(d)); }

    sendCommand(CMD_PWCTR4);
    { uint8_t d[] = {0x8A, 0x2A}; sendData(d, sizeof(d)); }

    sendCommand(CMD_PWCTR5);
    { uint8_t d[] = {0x8A, 0xEE}; sendData(d, sizeof(d)); }

    sendCommand(CMD_VMCTR1);
    sendData(0x0E);

    sendCommand(CMD_COLMOD);
    sendData(0x05); // 16 bpp

    sendCommand(CMD_GMCTRP1);
    {
        uint8_t d[] = {0x02, 0x1C, 0x07, 0x12, 0x37, 0x32, 0x29, 0x2D,
                       0x29, 0x25, 0x2B, 0x39, 0x00, 0x01, 0x03, 0x10};
        sendData(d, sizeof(d));
    }

    sendCommand(CMD_GMCTRN1);
    {
        uint8_t d[] = {0x03, 0x1D, 0x07, 0x06, 0x2E, 0x2C, 0x29, 0x2D,
                       0x2E, 0x2E, 0x37, 0x3F, 0x00, 0x00, 0x02, 0x10};
        sendData(d, sizeof(d));
    }
}

} // namespace tft
