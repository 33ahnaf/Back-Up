#include "ILI9341.h"

namespace tft {

namespace {
    // ILI9341-specific extended command opcodes (not part of the shared
    // MIPI-DBI base set in DriverBase).
    constexpr uint8_t CMD_PWCTR1   = 0xC0;
    constexpr uint8_t CMD_PWCTR2   = 0xC1;
    constexpr uint8_t CMD_VMCTR1   = 0xC5;
    constexpr uint8_t CMD_VMCTR2   = 0xC7;
    constexpr uint8_t CMD_FRMCTR1  = 0xB1;
    constexpr uint8_t CMD_DFUNCTR  = 0xB6;
    constexpr uint8_t CMD_PWCTRA   = 0xCB;
    constexpr uint8_t CMD_PWCTRB   = 0xCF;
    constexpr uint8_t CMD_PWRONSEQ = 0xED;
    constexpr uint8_t CMD_TIMCTRA  = 0xE8;
    constexpr uint8_t CMD_TIMCTRB  = 0xEA;
    constexpr uint8_t CMD_PUMPRATIO = 0xF7;
    constexpr uint8_t CMD_ENABLE3G = 0xF2;
    constexpr uint8_t CMD_GAMMASET  = 0x26;
    constexpr uint8_t CMD_GMCTRP1   = 0xE0;
    constexpr uint8_t CMD_GMCTRN1   = 0xE1;
}

ILI9341::ILI9341(SPIBus& bus)
    : DriverBase(bus, 240, 320)
{
}

void ILI9341::initSequence() {
    sendCommand(CMD_PWCTRB);
    { uint8_t d[] = {0x00, 0x83, 0x30}; sendData(d, sizeof(d)); }

    sendCommand(CMD_PWRONSEQ);
    { uint8_t d[] = {0x64, 0x03, 0x12, 0x81}; sendData(d, sizeof(d)); }

    sendCommand(CMD_TIMCTRA);
    { uint8_t d[] = {0x85, 0x00, 0x78}; sendData(d, sizeof(d)); }

    sendCommand(CMD_PWCTRA);
    { uint8_t d[] = {0x39, 0x2C, 0x00, 0x34, 0x02}; sendData(d, sizeof(d)); }

    sendCommand(CMD_PUMPRATIO);
    sendData(0x20);

    sendCommand(CMD_TIMCTRB);
    { uint8_t d[] = {0x00, 0x00}; sendData(d, sizeof(d)); }

    sendCommand(CMD_PWCTR1);
    sendData(0x23); // VRH: GVDD level

    sendCommand(CMD_PWCTR2);
    sendData(0x10); // BT: step-up factor

    sendCommand(CMD_VMCTR1);
    { uint8_t d[] = {0x3E, 0x28}; sendData(d, sizeof(d)); } // VCOMH / VCOML

    sendCommand(CMD_VMCTR2);
    sendData(0x86); // VCOM offset

    sendCommand(CMD_COLMOD);
    sendData(0x55); // 16 bits/pixel (RGB565)

    sendCommand(CMD_FRMCTR1);
    { uint8_t d[] = {0x00, 0x18}; sendData(d, sizeof(d)); }

    sendCommand(CMD_DFUNCTR);
    { uint8_t d[] = {0x08, 0x82, 0x27}; sendData(d, sizeof(d)); }

    sendCommand(CMD_ENABLE3G);
    sendData(0x00); // Disable 3-gamma

    sendCommand(CMD_GAMMASET);
    sendData(0x01); // Gamma curve 1

    sendCommand(CMD_GMCTRP1);
    {
        uint8_t d[] = {0x0F, 0x31, 0x2B, 0x0C, 0x0E, 0x08, 0x4E,
                       0xF1, 0x37, 0x07, 0x10, 0x03, 0x0E, 0x09, 0x00};
        sendData(d, sizeof(d));
    }

    sendCommand(CMD_GMCTRN1);
    {
        uint8_t d[] = {0x00, 0x0E, 0x14, 0x03, 0x11, 0x07, 0x31,
                       0xC1, 0x48, 0x08, 0x0F, 0x0C, 0x31, 0x36, 0x0F};
        sendData(d, sizeof(d));
    }
}

} // namespace tft
