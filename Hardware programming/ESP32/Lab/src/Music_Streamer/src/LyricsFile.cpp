#include "LyricsFile.h"
#include "globals.h"
#include <Arduino.h>
#include <string>
#include <LiquidCrystal_I2C.h>

#define MODULE_NAME "LyricsFile"

uint32_t parseTimeToMS(std::string timeTag){
    int min = std::stoi(timeTag.substr(0, 2));
    int sec = std::stoi(timeTag.substr(3, 5));
    int frac = 0;

    if(timeTag.length() > 6){
        std::string f = timeTag.substr(6);
        if(f.length() == 2) frac = std::stoi(f) * 10;
        else frac = std::stoi(f);
    }

    return min * 60000 + sec * 1000 + frac;
}

bool LyricsFile::load(std::string path){
    stream = SD.open(path.c_str(), "r");
    if(!stream){
        Serial.printf("INFO: Cannot open the file containing lyrics! [%s]\n", MODULE_NAME);
        return 0;
    }

    lines.clear();
    readPos = 0;

    char buffer[256];
    
    while(stream.available()){
        int len = stream.readBytesUntil('\n', buffer, sizeof(buffer));
        buffer[len] = '\0';
        if(len > 0 && buffer[len - 1] == '\r')
            buffer[len - 1] = '\0';
        std::string line = buffer;
        if(line[0] != '[')              continue;
        int closeIdx = line.find(']');
        if(closeIdx == std::string::npos)    continue;
        std::string timeTag = line.substr(1, closeIdx - 1);
        if(timeTag[0] < '0' || timeTag[0] > '9')
            continue;
        std::string text = line.substr(closeIdx + 1);

        LyricsLine l;
        l.time_ms = parseTimeToMS(timeTag);
        l.text = text.c_str();
        lines.push_back(l);
    }
    stream.close();
    return 1;
}

void LyricsFile::unload(void){
    lines.clear();
    lines.shrink_to_fit();
}

void LyricsFile::render(AudioFile *af){
    if(readPos >= lines.size())
        return;
    uint32_t currentTimeMS = (double) (af->stream.position() - af->header_size) / (af->sample_rate*2.0/1000.0);
    if(currentTimeMS >= lines[readPos].time_ms){
        printf("%s\n", lines[readPos].text.c_str());
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print(lines[readPos].text.c_str());
        readPos++;
    }
}