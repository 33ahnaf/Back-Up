#pragma once
#ifndef _GLOBALS__H
#define _GLOBALS__H

#include <LiquidCrystal_I2C.h>

extern LiquidCrystal_I2C lcd;

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