#ifndef _GLOBALS__H
#define _GLOBALS__H

// #include <LiquidCrystal_I2C.h>
#include <string>

#define LGFX_DEFINATION_WIDTH  240
#define LGFX_DEFINATION_HEIGHT 320
#define TFT_W 320
#define TFT_H 240
#define TFT_ROTATION 1

#define TFT_CS    10
#define TFT_RST   8
#define TFT_DC    18
#define TFT_MOSI  13
#define TFT_SCLK  9
#define TFT_MISO  11
// pin 12 and 14 are reserved for additional SPI slaves

#define SD_CMD 4
#define SD_CLK 5
#define SD_DAT0 6
#define SD_FREQ 40000
#define SD_1bit true


enum Screen {
    SCREEN_MENU,
    SCREEN_SONG_BROWSER,
    SCREEN_AUDIO_PLAYER
};

typedef struct {
    Screen currentScreen = SCREEN_MENU;

    std::string selectedSong;

    bool isPlaying = false;
} AppState;


typedef struct {
    std::string rootPasswd;
    std::string WiFi_Passwd;
    std::string WiFi_SSID;
    bool scroll_wrapping;
    uint8_t brightness;
} Settings;


extern Settings settings;
extern AppState app;
// extern LiquidCrystal_I2C lcd;

extern std::string MUSICS_DIRECTORY;
extern std::string LYRICS_DIRECTORY;

extern uint32_t TFT_WRITE_FREQUENCY;

extern float bassGain;
extern float midGain;
extern float treGain;

extern float reverbMix;
extern float reverbFeedback;
extern float junoRate;
extern float junoDepth;
extern float junoMix;

#endif