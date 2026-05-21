#ifndef _AUDIO_STREAMER__H
#define _AUDIO_STREAMER__H

#include <alsa/asoundlib.h>
#include <string>
#include "AudioFile.h"
#include "LyricsFile.h"
#include "DSP_Effects.h"
#include "globals.h"
#include "MISC.h"
#include "raylib.h"

#define BUFF_SIZE 1024
#define HIGH_LIMIT 1.0f
#define LOW_LIMIT 0.0f
#define DELTA 0.1f
#define TRUE 1
#define FALSE 0

typedef struct {
    uint8_t inBuf[BUFF_SIZE];
    uint8_t outBuf[BUFF_SIZE]; // although ouBuf is unsed, could've done everything with using only inBuf but still it is present for future use
    AudioFile audioFile;
    LyricsFile lyricsFile;
    EQState left = {};
    EQState right = {};
    ReverbState revL = {};
    ReverbState revR = {};
    JunoState junoL = {};
    JunoState junoR = {};
    size_t bytesRead;
    size_t outIndex;

    bool pauseAudio = FALSE;
    bool audioShouldStop = FALSE;
    bool isLyricsAvailable;

    time_t currentTime;
    time_t previousTime;
    snd_pcm_t *pcm; std::string src;

    bool load(std::string path);
    void update(void);
    void unload(void);
} AudioStreamer;

#endif