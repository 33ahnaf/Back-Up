#include "globals.h"
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);

const char *ssid = "Music Streamer";
const char *password = "12345678";

float bassGain = 100.0f / 100.0f;
float midGain = 10.0f / 100.0f;
float treGain = 100.0f / 100.0f;

float reverbMix = 0.2f; // wet amount
float reverbFeedback = 0.4f;
float junoRate = 0.05f;
float junoDepth = 800.0f;
float junoMix = 0.5f;