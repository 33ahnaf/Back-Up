#ifndef _AUDIO_STREAMER__H
#define _AUDIO_STREAMER__H

#include <string>
#include "AudioFile.h"
#include "LyricsFile.h"
#include "DSP_Effects.h"
#include <raylib.h>
#include <alsa/asoundlib.h>

#define BUFF_SIZE 1024
#define HIGH_LIMIT 1.0f
#define LOW_LIMIT 0.0f
#define DELTA 0.1f

typedef struct {
    uint8_t inBuf[BUFF_SIZE];
    uint8_t outBuf[BUFF_SIZE]; // although ouBuf is unsed, could've done everything with using only inBuf but still it is present for future use
    AudioFile audioFile;
    LyricsFile lyricsFile;
    EQState left  = {0};
    EQState right = {0};
    ReverbState revL = {0};
    ReverbState revR = {0};
    JunoState junoL = {0};
    JunoState junoR = {0};
    size_t bytesRead;
    size_t outIndex;

    bool pauseAudio = false;
    bool isLyricsAvailable;
    bool isLoaded = false;
    bool isUnloaded = false;

    time_t currentTime;
    time_t previousTime;
    snd_pcm_t *pcm;

    void fastForwardAudio(size_t milliseconds);
    void rewindAudio(size_t milliseconds);
    void progressBar(void);

    void load(std::string path);
    void update(void);
    void unload(void);
} AudioStreamer;

extern AudioStreamer audio;

void showINFO(void);

#endif