#include "ILI9488.h"

namespace tft {

namespace {
    constexpr uint8_t CMD_PWCTR1   = 0xC0;
    constexpr uint8_t CMD_PWCTR2   = 0xC1;
    constexpr uint8_t CMD_VMCTR1   = 0xC5;
    constexpr uint8_t CMD_FRMCTR1  = 0xB1;
    constexpr uint8_t CMD_DINVCTR  = 0xB4;
    constexpr uint8_t CMD_DFUNCTR  = 0xB6;
    constexpr uint8_t CMD_ENTRYMODE = 0xB7;
    constexpr uint8_t CMD_ADJCTL3  = 0xF7;
    constexpr uint8_t CMD_GMCTRP1  = 0xE0;
    constexpr uint8_t CMD_GMCTRN1  = 0xE1;
}

ILI9488::ILI9488(SPIBus& bus)
    : DriverBase(bus, 320, 480)
{
}

void ILI9488::initSequence() {
    sendCommand(CMD_PWCTR1);
    { uint8_t d[] = {0x17, 0x15}; sendData(d, sizeof(d)); }

    sendCommand(CMD_PWCTR2);
    sendData(0x41);

    sendCommand(CMD_VMCTR1);
    { uint8_t d[] = {0x00, 0x12, 0x80}; sendData(d, sizeof(d)); }

    sendCommand(CMD_COLMOD);
    sendData(0x55); // 16 bpp, forces the panel into RGB565 even though it
                     // is natively capable of 18-bit color.

    sendCommand(CMD_ENTRYMODE);
    sendData(0x00);

    sendCommand(CMD_DINVCTR);
    sendData(0x02); // 2-dot inversion

    sendCommand(CMD_DFUNCTR);
    { uint8_t d[] = {0x02, 0x02, 0x3B}; sendData(d, sizeof(d)); }

    sendCommand(CMD_FRMCTR1);
    sendData(0xA0);

    sendCommand(CMD_ADJCTL3);
    { uint8_t d[] = {0xA9, 0x51, 0x2C, 0x82}; sendData(d, sizeof(d)); }

    sendCommand(CMD_GMCTRP1);
    {
        uint8_t d[] = {0x00, 0x03, 0x09, 0x08, 0x16, 0x0A, 0x3F,
                       0x78, 0x4C, 0x09, 0x0A, 0x08, 0x16, 0x1A, 0x0F};
        sendData(d, sizeof(d));
    }

    sendCommand(CMD_GMCTRN1);
    {
        uint8_t d[] = {0x00, 0x16, 0x19, 0x03, 0x0F, 0x05, 0x32,
                       0x45, 0x46, 0x04, 0x0E, 0x0D, 0x35, 0x37, 0x0F};
        sendData(d, sizeof(d));
    }
}

} // namespace tft
