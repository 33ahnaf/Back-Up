#include "AudioStreamer.h"
#include "globals.h"
#include "DSP_Effects.h"
#include "MISC.h"
#include "AudioFile.h"
#include "LyricsFile.h"
#include <Arduino.h>
#include <stdint.h>
#include <SD.h>
#include <string>

#define BUFF_SIZE 1024
#define HIGH_LIMIT 1.0f
#define LOW_LIMIT 0.0f
#define DELTA 0.1f
#define TRUE 1
#define FALSE 0

typedef std::string string;

uint8_t inBuf[BUFF_SIZE];
uint8_t outBuf[BUFF_SIZE * 2];
AudioFile audioFile;
LyricsFile lyricsFile;
EQState left = {};
EQState right = {};
ReverbState revL = {};
ReverbState revR = {};
JunoState junoL = {};
JunoState junoR = {};

void streamAudio(string src){
    junoR.phase1 = 3.141592f;
    junoR.phase2 = 0.0f;
    
    string audioPath = "/SigmaDelta/Musics/" + src + ".wav";
    string lyricsPath = "/SigmaDelta/Lyrics/" + src + ".lrc";

    bool isLyricsAvailable = lyricsFile.load(lyricsPath);
    audioFile.stream = SD.open(audioPath.c_str());
    if(!audioFile.stream){
        Serial.printf("Cannot open source file!\n");
        dacLow();
        return;
    }
    audioFile.init();
    i2s_attach(BUFF_SIZE, audioFile.sample_rate);
    Reverb_Juno_allocate_all(audioFile.sample_rate, &revL, &revR, &junoL, &junoR);

    uint8_t pauseAudio = FALSE;
    uint8_t exitFlag = FALSE;
    uint32_t bytesWritten = 0; // unused
    int bytesRead; // must NOT be unsigned for it is used by FS::read() which returns -1 on error occurrence
    size_t outIndex = 0;
    size_t currentTime = 0;
    size_t previousTime = 0;
    audioFile.stream.seek(audioFile.header_size);

    while(1){
        if(Serial.available() > 0){
            char c = (char) Serial.read();
            switch(c){
                case 'q': bassGain = bassGain >= HIGH_LIMIT ? HIGH_LIMIT : bassGain + DELTA; showINFO(); break;
                case 'a': bassGain = bassGain <= LOW_LIMIT ? LOW_LIMIT : bassGain - DELTA; showINFO(); break;

                case 'w': midGain = midGain >= HIGH_LIMIT ? HIGH_LIMIT : midGain + DELTA; showINFO(); break;
                case 's': midGain = midGain <= LOW_LIMIT ? LOW_LIMIT : midGain - DELTA; showINFO(); break;

                case 'e': treGain = treGain >= HIGH_LIMIT ? HIGH_LIMIT : treGain + DELTA; showINFO(); break;
                case 'd': treGain = treGain <= LOW_LIMIT ? LOW_LIMIT : treGain - DELTA; showINFO(); break;

                case 'r': junoRate = junoRate >= HIGH_LIMIT ? HIGH_LIMIT : junoRate + 0.05f; showINFO(); break;
                case 'f': junoRate = junoRate <= LOW_LIMIT ? LOW_LIMIT : junoRate - 0.05f; showINFO(); break;

                case 't': junoDepth = junoDepth >= 10000 ? 10000 : junoDepth + 100.0f; showINFO(); break;
                case 'g': junoDepth = junoDepth <= 0 ? 0 : junoDepth - 100.0f; showINFO(); break;

                case 'y': junoMix = junoMix >= HIGH_LIMIT ? HIGH_LIMIT : junoMix + 0.05f; showINFO(); break;
                case 'h': junoMix = junoMix <= LOW_LIMIT ? LOW_LIMIT : junoMix - 0.05f; showINFO(); break;

                case 'u': reverbMix = reverbMix >= HIGH_LIMIT ? HIGH_LIMIT : reverbMix + 0.05f; showINFO(); break;
                case 'j': reverbMix = reverbMix <= LOW_LIMIT ? LOW_LIMIT : reverbMix - 0.05f; showINFO(); break;

                case 'i': reverbFeedback = reverbFeedback >= HIGH_LIMIT ? HIGH_LIMIT : reverbFeedback + 0.05f; showINFO(); break;
                case 'k': reverbFeedback = reverbFeedback <= LOW_LIMIT ? LOW_LIMIT : reverbFeedback - 0.05f; showINFO(); break;

                case ' ': pauseAudio = !pauseAudio; Serial.println(pauseAudio ? "Streaming paused!" : "Resumed!"); break;
                case 'x': exitFlag = TRUE; break;

                case ',': rewindAudio(&audioFile); progressBar(&audioFile); break;
                case '.': fastForwardAudio(&audioFile); progressBar(&audioFile); break;
            }
        }
        if(exitFlag)
            break;
        if(pauseAudio){
            delay(10);
            continue;
        }
        outIndex = 0;
        bytesRead = audioFile.stream.read(inBuf, BUFF_SIZE);
        if(bytesRead == 0)  break;
        for(size_t i = 0; i < bytesRead; i+=2){ // do i+1 instead of only i to make sure it's safe when bytesRead is odd (no need)
            // left.applyEQ(&inBuf[i], &revL, &junoL);
            // right.applyEQ(&inBuf[i+1], &revR, &junoR);
            outBuf[outIndex++] = inBuf[i];
            outBuf[outIndex++] = inBuf[i + 1];
            outBuf[outIndex++] = inBuf[i];
            outBuf[outIndex++] = inBuf[i + 1];
        }
        i2s_write(I2S_NUM_0, outBuf, outIndex, &bytesWritten, portMAX_DELAY); // use outIndex exclusively, as the outBuf becomes x2 of inBuf
        currentTime = millis();
        if(currentTime - previousTime >= 1000 && !isLyricsAvailable){
            progressBar(&audioFile);
            previousTime = currentTime;
        }
        if(isLyricsAvailable)
            lyricsFile.render(&audioFile);
    }
    
    audioFile.stream.close();
    i2s_detach();
    Reverb_Juno_release_all(&revL, &revR, &junoL, &junoR);
    lyricsFile.unload();
    dacLow();
}



/*
    Simple audio streaming Mono/Stereo without Oversampling:
        uint8_t buffer[BUFFER_SIZE:1024]; 

        uint32_t bytesWritten = 0;
        uint32_t bytesRead = audioFile.read(buffer, BUFFER_SIZE);
        if(bytesRead == 0)  break;
        i2s_write(I2S_NUM_0, buffer, bytesRead, &bytesWritten, portMAX_DELAY);
         * Use >bytesRead< instead of direct >buffer< as the actualy bytesRead
         * becomes less than buffer size at the very end of the file.
        
    Audio streaming Mono with Oversampling:
        uint8_t inBuf[BUFFER_SIZE:1024];
        uint8_t outBuf[BUFFER_SIZE * 2: 1024 * 2: 2048];

        uint32_t outIndex = 0;
        uint32_t bytesRead = audioFile.read(inBuf, BUFFER_SIZE);
        if(bytesRead == 0)  break;
        for(uint32_t i = 0; i < bytesRead; i++){
            outBuf[outIndex++] = inBuf[i]; // original
            outBuf[outIndex++] = inBuf[i]; // duplicate
        }
        i2s_write(I2S_NUM_0, outBuf, outIndex, &bytesWritten, portMAX_DELAY); // use outIndex exclusively, as the outBuf becomes x2 of inBuf
*/
