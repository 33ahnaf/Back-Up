#include "globals.h"

AppState app;

float bassGain = 100.0f / 100.0f;
float midGain = 10.0f / 100.0f;
float treGain = 100.0f / 100.0f;

float reverbMix = 0.15f; //wet amount
float reverbFeedback = 0.25f;

float junoRate = 0.05f; // 0.05f
float junoDepth = 700.0f; // 800.0f
float junoMix = 0.95f; // 0.4f

int constrain(int amt, int low, int high){
    if(amt > high) return high;
    if(amt < low) return low;
    return amt;
}