#include "ILI9486.h"

namespace tft {

namespace {
    constexpr uint8_t CMD_PWCTR1  = 0xC0;
    constexpr uint8_t CMD_PWCTR2  = 0xC1;
    constexpr uint8_t CMD_PWCTR3  = 0xC2;
    constexpr uint8_t CMD_VMCTR1  = 0xC5;
    constexpr uint8_t CMD_FRMCTR1 = 0xB1;
    constexpr uint8_t CMD_DFUNCTR = 0xB6;
    constexpr uint8_t CMD_ENTRYMODE = 0xB7;
    constexpr uint8_t CMD_GMCTRP1 = 0xE0;
    constexpr uint8_t CMD_GMCTRN1 = 0xE1;
}

ILI9486::ILI9486(SPIBus& bus)
    : DriverBase(bus, 320, 480)
{
}

void ILI9486::initSequence() {
    sendCommand(CMD_PWCTR1);
    { uint8_t d[] = {0x0D, 0x0D}; sendData(d, sizeof(d)); }

    sendCommand(CMD_PWCTR2);
    { uint8_t d[] = {0x43, 0x00}; sendData(d, sizeof(d)); }

    sendCommand(CMD_PWCTR3);
    sendData(0x00);

    sendCommand(CMD_VMCTR1);
    { uint8_t d[] = {0x00, 0x48, 0x00, 0x48}; sendData(d, sizeof(d)); }

    sendCommand(CMD_COLMOD);
    sendData(0x55); // 16 bpp

    sendCommand(CMD_ENTRYMODE);
    sendData(0x00);

    sendCommand(CMD_FRMCTR1);
    { uint8_t d[] = {0xA0, 0x11}; sendData(d, sizeof(d)); }

    sendCommand(CMD_DFUNCTR);
    { uint8_t d[] = {0x02, 0x02, 0x3B}; sendData(d, sizeof(d)); }

    sendCommand(CMD_GMCTRP1);
    {
        uint8_t d[] = {0x0F, 0x1F, 0x1C, 0x0C, 0x0F, 0x08, 0x48,
                       0x98, 0x37, 0x0A, 0x13, 0x04, 0x11, 0x0D, 0x00};
        sendData(d, sizeof(d));
    }

    sendCommand(CMD_GMCTRN1);
    {
        uint8_t d[] = {0x0F, 0x32, 0x2E, 0x0B, 0x0D, 0x05, 0x47,
                       0x75, 0x37, 0x06, 0x10, 0x03, 0x24, 0x20, 0x00};
        sendData(d, sizeof(d));
    }
}

} // namespace tft
