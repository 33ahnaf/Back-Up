#include "globals.h"

AppState app;

std::string MUSICS_DIRECTORY = "./assets/Musics/";
std::string LYRICS_DIRECTORY = "./assets/Lyrics/";

float bassGain = 100.0f / 100.0f;
float midGain = 100.0f / 100.0f;
float treGain = 100.0f / 100.0f;

float reverbMix = 0.00f; //wet amount
float reverbFeedback = 0.00f;

float junoRate = 0.00f; // 0.05f
float junoDepth = 000.0f; // 800.0f
float junoMix = 0.00f; // 0.4f