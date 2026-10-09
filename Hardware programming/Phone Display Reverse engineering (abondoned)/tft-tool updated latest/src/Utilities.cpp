#include "Utilities.h"

namespace tft {

void logTestBanner(const char* driverName, uint8_t rotation, bool bgr, bool invert) {
#if defined(ENABLE_SERIAL_LOG)
    Serial.println(F("========================="));
    Serial.print(F("Driver       : "));
    Serial.println(driverName);
    Serial.print(F("Rotation     : "));
    Serial.println(rotation);
    Serial.print(F("Color Order  : "));
    Serial.println(bgr ? F("BGR") : F("RGB"));
    Serial.print(F("Invert       : "));
    Serial.println(invert ? F("ON") : F("OFF"));
    Serial.println(F("========================="));
#else
    (void)driverName;
    (void)rotation;
    (void)bgr;
    (void)invert;
#endif
}

void logColorStep(const char* colorName) {
#if defined(ENABLE_SERIAL_LOG)
    Serial.println(colorName);
#else
    (void)colorName;
#endif
}

void logPinPermutation(size_t index, size_t total, const PinConfig& cfg) {
#if defined(ENABLE_SERIAL_LOG) || defined(ENABLE_PIN_PERMUTATION_TEST)
    TFT_PIN_LOGLN(F("===================================="));
    TFT_PIN_LOG(F("PIN PERMUTATION "));
    TFT_PIN_LOG(index + 1);
    TFT_PIN_LOG(F(" / "));
    TFT_PIN_LOGLN(total);
    TFT_PIN_LOG(F("CS="));   TFT_PIN_LOG(cfg.cs);
    TFT_PIN_LOG(F("  DC=")); TFT_PIN_LOG(cfg.dc);
    TFT_PIN_LOG(F("  RST=")); TFT_PIN_LOG(cfg.rst);
    TFT_PIN_LOG(F("  MOSI=")); TFT_PIN_LOG(cfg.mosi);
    TFT_PIN_LOG(F("  SCK=")); TFT_PIN_LOGLN(cfg.sck);
    TFT_PIN_LOGLN(F("===================================="));
#else
    (void)index;
    (void)total;
    (void)cfg;
#endif
}

} // namespace tft
