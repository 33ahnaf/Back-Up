#ifndef _AUDIO_STREAMER__H
#define _AUDIO_STREAMER__H

#include <stdint.h>
#include "AudioFile.h"
#include "LyricsFile.h"
#include "DSP_Effects.h"

#define BUFF_SIZE 1024
#define HIGH_LIMIT 1.0f
#define LOW_LIMIT 0.0f
#define DELTA 0.1f

typedef struct {
    uint8_t inBuf[BUFF_SIZE];
    uint16_t outBuf[BUFF_SIZE];
    AudioFile audioFile;
    LyricsFile lyricsFile;
    EQState left  = {0};
    EQState right = {0};
    ReverbState revL = {0};
    ReverbState revR = {0};
    JunoState junoL = {0};
    JunoState junoR = {0};
    size_t bytesRead;
    size_t bytesWritten;
    size_t outIndex;

    bool pauseAudio = false;
    bool isLyricsAvailable;
    bool isLoaded = false;
    bool isUnloaded = false;

    time_t currentTime;
    time_t previousTime;

    void dacLow     (void);
    void showINFO   (void);
    void i2s_attach (uint32_t buffer_size, uint32_t sample_rate);
    void i2s_detach (void);

    void fastForwardAudio (size_t milliseconds);
    void rewindAudio      (size_t milliseconds);
    void progressBar      (void);

    void load  (std::string src);
    void update(void);
    void unload(void);
} AudioStreamer;

extern AudioStreamer audio;



#endif