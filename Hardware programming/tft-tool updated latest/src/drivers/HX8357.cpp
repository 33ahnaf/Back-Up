#include "HX8357.h"

namespace tft {

namespace {
    constexpr uint8_t CMD_SETPOWER  = 0xB1;
    constexpr uint8_t CMD_SETRGB    = 0xB3;
    constexpr uint8_t CMD_SETCYC    = 0xB4;
    constexpr uint8_t CMD_SETCOM    = 0xB6;
    constexpr uint8_t CMD_SETEXTC   = 0xB9;
    constexpr uint8_t CMD_SETSTBA   = 0xC0;
    constexpr uint8_t CMD_SETPANEL  = 0xCC;
    constexpr uint8_t CMD_SETGAMMA  = 0xE0;
}

HX8357::HX8357(SPIBus& bus)
    : DriverBase(bus, 320, 480)
{
}

void HX8357::initSequence() {
    sendCommand(CMD_SETEXTC);
    { uint8_t d[] = {0xFF, 0x83, 0x57}; sendData(d, sizeof(d)); }
    delay(150);

    sendCommand(CMD_SETRGB);
    { uint8_t d[] = {0x80, 0x00, 0x06, 0x06}; sendData(d, sizeof(d)); }

    sendCommand(CMD_SETCOM);
    sendData(0x25); // VCOM

    sendCommand(0xB0);
    sendData(0x68); // Normal mode 70Hz, Idle mode 55Hz

    sendCommand(CMD_SETPOWER);
    { uint8_t d[] = {0x00, 0x15, 0x0D, 0x0D, 0x83, 0x48}; sendData(d, sizeof(d)); }

    sendCommand(CMD_SETSTBA);
    { uint8_t d[] = {0x25, 0x25, 0x02, 0x02, 0x76, 0x76}; sendData(d, sizeof(d)); }

    sendCommand(CMD_SETCYC);
    { uint8_t d[] = {0x02, 0x40, 0x00, 0x2A, 0x2A, 0x0D, 0x78}; sendData(d, sizeof(d)); }

    sendCommand(CMD_SETGAMMA);
    {
        uint8_t d[] = {0x02, 0x0A, 0x11, 0x1D, 0x23, 0x35, 0x41, 0x4B,
                       0x4B, 0x42, 0x3A, 0x27, 0x1B, 0x08, 0x09, 0x03,
                       0x02, 0x0A, 0x11, 0x1D, 0x23, 0x35, 0x41, 0x4B,
                       0x4B, 0x42, 0x3A, 0x27, 0x1B, 0x08, 0x09, 0x03,
                       0x00, 0x01};
        sendData(d, sizeof(d));
    }

    sendCommand(CMD_COLMOD);
    sendData(0x55); // 16 bpp

    sendCommand(CMD_SETPANEL);
    sendData(0x05);
}

} // namespace tft
