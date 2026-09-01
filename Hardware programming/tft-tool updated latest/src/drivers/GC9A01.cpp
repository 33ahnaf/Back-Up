#include "GC9A01.h"

namespace tft {

namespace {
    // Vendor "inter register enable" unlock commands. Without these the
    // rest of the extended register set below is silently ignored.
    constexpr uint8_t CMD_INREGEN1 = 0xFE;
    constexpr uint8_t CMD_INREGEN2 = 0xEF;

    constexpr uint8_t CMD_DFUNCTR  = 0xB6;
    constexpr uint8_t CMD_PWCTR2   = 0xC3;
    constexpr uint8_t CMD_PWCTR3   = 0xC4;
    constexpr uint8_t CMD_PWCTR4   = 0xC9;
    constexpr uint8_t CMD_FRAMERATE = 0xE8;
    constexpr uint8_t CMD_GMCTRP1  = 0xE0; // "Set Gamma 1"
    constexpr uint8_t CMD_GMCTRN1  = 0xE1; // "Set Gamma 2"
    constexpr uint8_t CMD_GMCTR3   = 0xE2; // "Set Gamma 3"
    constexpr uint8_t CMD_GMCTR4   = 0xE3; // "Set Gamma 4"
}

GC9A01::GC9A01(SPIBus& bus)
    : DriverBase(bus, 240, 240)
{
}

uint8_t GC9A01::madctlValue(uint8_t rotation, bool bgr) const {
    // GC9A01 boards are almost always wired BGR and its silkscreen "up"
    // direction is rotated relative to the ILI9341 reference mapping.
    uint8_t m = 0;
    switch (rotation & 0x03) {
        case 0: m = 0x00;                 break;
        case 1: m = MADCTL_MX | MADCTL_MV; break;
        case 2: m = MADCTL_MX | MADCTL_MY; break;
        case 3: m = MADCTL_MY | MADCTL_MV; break;
        default: break;
    }
    if (bgr) {
        m |= MADCTL_BGR;
    }
    return m;
}

void GC9A01::initSequence() {
    // Unlock the vendor-specific extended register block. Every write below
    // this point is ignored by the controller until both are sent.
    sendCommand(CMD_INREGEN1);
    sendCommand(CMD_INREGEN2);

    sendCommand(0xEB); // Undocumented vendor tuning register
    sendData(0x14);

    // 0x84-0x8F: vendor-internal analog/timing tuning block. GC9A01 does
    // not publish the bit-level meaning of these registers in its public
    // datasheet; the values below are the standard power-up block used
    // across the common 1.28" round-panel breakout boards.
    sendCommand(0x84);
    sendData(0x40);

    sendCommand(0x85);
    sendData(0xFF);

    sendCommand(0x86);
    sendData(0xFF);

    sendCommand(0x87);
    sendData(0xFF);

    sendCommand(0x88);
    sendData(0x0A);

    sendCommand(0x89);
    sendData(0x21);

    sendCommand(0x8A);
    sendData(0x00);

    sendCommand(0x8B);
    sendData(0x80);

    sendCommand(0x8C);
    sendData(0x01);

    sendCommand(0x8D);
    sendData(0x01);

    sendCommand(0x8E);
    sendData(0xFF);

    sendCommand(0x8F);
    sendData(0xFF);

    sendCommand(CMD_DFUNCTR); // Display function control: gate/source scan config
    { uint8_t d[] = {0x00, 0x20}; sendData(d, sizeof(d)); }

    sendCommand(CMD_COLMOD);
    sendData(0x55); // 16 bpp

    sendCommand(CMD_PWCTR2); // Power control 2: VREG1 output
    sendData(0x13);

    sendCommand(CMD_PWCTR3); // Power control 3: VREG2 output
    sendData(0x13);

    sendCommand(CMD_PWCTR4); // Power control 4: VCOM control
    sendData(0x22);

    sendCommand(0xBE); // Vendor-internal power sequencing tweak
    sendData(0x11);

    sendCommand(0xDF); // Vendor-internal gamma engine trim
    { uint8_t d[] = {0x21, 0x0c, 0x02}; sendData(d, sizeof(d)); }

    sendCommand(CMD_GMCTRP1);
    { uint8_t d[] = {0x45, 0x09, 0x08, 0x08, 0x26, 0x2A}; sendData(d, sizeof(d)); }

    sendCommand(CMD_GMCTRN1);
    { uint8_t d[] = {0x43, 0x70, 0x72, 0x36, 0x37, 0x6F}; sendData(d, sizeof(d)); }

    sendCommand(CMD_GMCTR3);
    { uint8_t d[] = {0x45, 0x09, 0x08, 0x08, 0x26, 0x2A}; sendData(d, sizeof(d)); }

    sendCommand(CMD_GMCTR4);
    { uint8_t d[] = {0x43, 0x70, 0x72, 0x36, 0x37, 0x6F}; sendData(d, sizeof(d)); }

    sendCommand(CMD_FRAMERATE);
    { uint8_t d[] = {0x34, 0x03, 0x00, 0x11, 0x01, 0x02}; sendData(d, sizeof(d)); }

    sendCommand(0xA9);
    sendData(0x1D);
}

} // namespace tft
