#include "LyricsFile.h"
#include "globals.h"

uint32_t parseTimeToMS(string timeTag){
    int min = std::stoi(timeTag.substr(0, 2));
    int sec = std::stoi(timeTag.substr(3, 5));
    int frac = 0;

    if(timeTag.length() > 6){
        string f = timeTag.substr(6);
        if(f.length() == 2) frac = std::stoi(f) * 10;
        else frac = std::stoi(f);
    }

    return min * 60000 + sec * 1000 + frac;
}

bool LyricsFile::load(string path){
    stream = fopen(path.c_str(), "r");
    if(!stream){
        printf("Cannot open the file containing lyrics!\n");
        return 0;
    }

    lines.clear();
    readPos = 0;

    char buffer[256];

    while(fgets(buffer, sizeof(buffer), stream)){
        string line = buffer;
        if(line[0] != '[')              continue;
        int closeIdx = line.find(']');
        if(closeIdx == (int)string::npos)    continue;
        string timeTag = line.substr(1, closeIdx - 1);
        if(timeTag[0] < '0' || timeTag[0] > '9')
            continue;
        string text = line.substr(closeIdx + 1);

        LyricsLine l;
        l.time_ms = parseTimeToMS(timeTag);
        l.text = text;
        lines.push_back(l);
    }
    fclose(stream);
    return 1;
}

void LyricsFile::unload(void){
    lines.clear();
    lines.shrink_to_fit();
}

void LyricsFile::render(AudioFile *af){
    if(readPos >= lines.size())
        return;
    uint32_t currentTimeMS = (double) (ftell(af->stream) - af->header_size) / (af->sample_rate*2.0/1000.0);
    if(currentTimeMS >= lines[readPos].time_ms){
        printf("%s", lines[readPos++].text.c_str());
    }
}