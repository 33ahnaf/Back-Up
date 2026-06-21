#ifndef _GLOBALS__H
#define _GLOBALS__H

#include <LiquidCrystal_I2C.h>
#include <string>

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



extern AppState app;
extern LiquidCrystal_I2C lcd;

extern std::string MUSICS_DIRECTORY;
extern std::string LYRICS_DIRECTORY;

extern const char *ssid;
extern const char *password;

extern float bassGain;
extern float midGain;
extern float treGain;

extern float reverbMix;
extern float reverbFeedback;
extern float junoRate;
extern float junoDepth;
extern float junoMix;

#endif