#include "ST7789.h"

namespace tft {

namespace {
    constexpr uint8_t CMD_PORCTRL = 0xB2;
    constexpr uint8_t CMD_GCTRL   = 0xB7;
    constexpr uint8_t CMD_VCOMS   = 0xBB;
    constexpr uint8_t CMD_LCMCTRL = 0xC0;
    constexpr uint8_t CMD_VDVVRHEN = 0xC2;
    constexpr uint8_t CMD_VRHS    = 0xC3;
    constexpr uint8_t CMD_VDVS    = 0xC4;
    constexpr uint8_t CMD_FRCTRL2 = 0xC6;
    constexpr uint8_t CMD_PWCTRL1 = 0xD0;
    constexpr uint8_t CMD_PVGAMCTRL = 0xE0;
    constexpr uint8_t CMD_NVGAMCTRL = 0xE1;
}

ST7789::ST7789(SPIBus& bus)
    : DriverBase(bus, 240, 320)
{
}

void ST7789::initSequence() {
    sendCommand(CMD_PORCTRL);
    { uint8_t d[] = {0x0C, 0x0C, 0x00, 0x33, 0x33}; sendData(d, sizeof(d)); }

    sendCommand(CMD_GCTRL);
    sendData(0x35);

    sendCommand(CMD_VCOMS);
    sendData(0x19);

    sendCommand(CMD_LCMCTRL);
    sendData(0x2C);

    sendCommand(CMD_VDVVRHEN);
    sendData(0x01);

    sendCommand(CMD_VRHS);
    sendData(0x12);

    sendCommand(CMD_VDVS);
    sendData(0x20);

    sendCommand(CMD_FRCTRL2);
    sendData(0x0F);

    sendCommand(CMD_PWCTRL1);
    { uint8_t d[] = {0xA4, 0xA1}; sendData(d, sizeof(d)); }

    sendCommand(CMD_COLMOD);
    sendData(0x55); // 16 bpp

    sendCommand(CMD_PVGAMCTRL);
    {
        uint8_t d[] = {0xD0, 0x04, 0x0D, 0x11, 0x13, 0x2B, 0x3F,
                       0x54, 0x4C, 0x18, 0x0D, 0x0B, 0x1F, 0x23};
        sendData(d, sizeof(d));
    }

    sendCommand(CMD_NVGAMCTRL);
    {
        uint8_t d[] = {0xD0, 0x04, 0x0C, 0x11, 0x13, 0x2C, 0x3F,
                       0x44, 0x51, 0x2F, 0x1F, 0x1F, 0x20, 0x23};
        sendData(d, sizeof(d));
    }
}

} // namespace tft
