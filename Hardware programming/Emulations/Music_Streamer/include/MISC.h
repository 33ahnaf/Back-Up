#ifndef _MISC__H
#define _MISC__H

#include "AudioFile.h"

void showINFO(void);
void i2s_attach(uint32_t buffer_size, uint32_t sample_rate);
void i2s_detach(void);
void fastForwardAudio(AudioFile *audioFile);
void rewindAudio(AudioFile *audioFile);
void progressBar(AudioFile *audioFile);
void get_HEAP_AND_STACK_info(void);

#endif