// #pragma once
#ifndef _AUDIO_STREAMER__H
#define _AUDIO_STREAMER__H

#include <Arduino.h>
#include <string>

void streamAudio(std::string src);
void dacLow(void);

#endif