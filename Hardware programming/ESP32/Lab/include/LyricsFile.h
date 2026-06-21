#ifndef _LYRICS_FILE__H
#define _LYRICS_FILE__H

#include "AudioFile.h"
#include <SD.h>
#include <stdint.h>
#include <string>
#include <vector>

typedef struct {
    uint32_t time_ms;
    std::string text;
} LyricsLine;

typedef struct {
    File stream;
    std::vector<LyricsLine> lines;
    size_t readPos;

    bool load(std::string path);
    void unload(void);
    void render(AudioFile *af);
} LyricsFile;

#endif