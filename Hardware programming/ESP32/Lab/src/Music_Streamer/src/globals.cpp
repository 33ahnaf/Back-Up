#include "globals.h"
#include <string>
#include <LiquidCrystal_I2C.h>

AppState app;
Settings settings;
LiquidCrystal_I2C lcd(0x27, 20, 4);

std::string MUSICS_DIRECTORY = "/SigmaDelta/Musics";
std::string LYRICS_DIRECTORY = "/SigmaDelta/Lyrics";

float bassGain = 100.0f / 100.0f;
float midGain = 100.0f / 100.0f;
float treGain = 100.0f / 100.0f;

float reverbMix = 0.0f; // wet amount
float reverbFeedback = 0.0f;

float junoRate = 0.00f;
float junoDepth = 000.0f;
float junoMix = 0.00f;