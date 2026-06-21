#include "AudioStreamer.h"
#include <Arduino.h>
#include <stdint.h>
#include <string>
#include <SD.h>
#include <driver/i2s.h>
#include "globals.h"
#include "DSP_Effects.h"
#include "MISC.h"
#include "AudioFile.h"
#include "LyricsFile.h"

#define MODULE_NAME "AudioStreamer"

AudioStreamer audio;

void AudioStreamer::load(std::string src){

    junoR.phase1 = 3.141592f;
    junoR.phase2 = 0.0f;
    junoL.phase1 = 0.0f;
    junoL.phase2 = 3.141592f;

    std::string audioPath =  MUSICS_DIRECTORY + "/" + src + ".wav";
    std::string lyricsPath =  LYRICS_DIRECTORY + "/" + src + ".lrc";

    audioFile.stream = SD.open(audioPath.c_str());
    isLyricsAvailable = lyricsFile.load(lyricsPath);

    if(!audioFile.stream){
        Serial.printf("Error: Cannot open source file! [%s]\n", MODULE_NAME);
        dacLow();
        app.isPlaying = false;
        return;
    }

    audioFile.init();
    i2s_attach(BUFF_SIZE, audioFile.sample_rate);
    Reverb_Juno_allocate_all(audioFile.sample_rate, &revL, &revR, &junoL, &junoR);

    Serial.printf("Now playing: %s\tSample rate: %u\n", src.c_str(), audioFile.sample_rate);
    audioFile.stream.seek(audioFile.header_size);
    isLoaded = true;
    isUnloaded = false;
}

void AudioStreamer::unload(void){
    Reverb_Juno_release_all(&revL, &revR, &junoL, &junoR);
    i2s_detach();
    lyricsFile.unload();
    audioFile.stream.close();
    dacLow();
    printf("\nExiting from Streamer...\n");
    isLoaded = false;
    isUnloaded = true;
    app.isPlaying = false;
}

void AudioStreamer::update(void){
    if(app.isPlaying && !isLoaded)
        load(app.selectedSong);

    if(!app.isPlaying){
        if(isLoaded && !isUnloaded){
            unload();
            return;
        }else{
            delay(100);
            return;
        }
    }

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

            case ',': rewindAudio(5000); progressBar(); break;
            case '.': fastForwardAudio(5000); progressBar(); break;
        }
    }

    if(pauseAudio){
        delay(10);
        return;
    }

    bytesRead = audioFile.stream.read(inBuf, BUFF_SIZE);
    if(bytesRead == 0){
        app.isPlaying = false;
        delay(100);
        return;
    }

    outIndex = 0;
    for(size_t i = 0; i < bytesRead; i+=2){ // do i+1 instead of only i to make sure it's safe when bytesRead is odd (no need)
        left.applyEQ(&inBuf[i], &revL, &junoL);
        right.applyEQ(&inBuf[i+1], &revR, &junoR);
        outBuf[outIndex++] = inBuf[i];
        outBuf[outIndex++] = inBuf[i+1];
        outBuf[outIndex++] = inBuf[i];
        outBuf[outIndex++] = inBuf[i+1];
    }i2s_write(I2S_NUM_0, outBuf, outIndex, &bytesWritten, portMAX_DELAY); // use outIndex exclusively, as the outBuf ~becomes x2 of inBuf

    currentTime = millis();
    if(currentTime - previousTime >= 1000 && !isLyricsAvailable){
        progressBar();
        previousTime = currentTime;
    }
    
    if(isLyricsAvailable)
        lyricsFile.render(&audioFile);
}

void AudioStreamer::fastForwardAudio(size_t milliseconds){
    if(audioFile.stream.position() + audioFile.sample_rate*2*(milliseconds / 1000.0) > audioFile.file_size){
        audioFile.stream.seek(audioFile.file_size-1);
        Serial.printf("\nCurrent position: %dth byte\n", audioFile.stream.position());
    }else{
        audioFile.stream.seek(audioFile.stream.position() + audioFile.sample_rate*2*(milliseconds / 1000.0));
        Serial.printf("\nCurrent position: %dth byte\n", audioFile.stream.position());
    }
}

void AudioStreamer::rewindAudio(size_t milliseconds){
    if(audioFile.stream.position() - audioFile.sample_rate*2*(milliseconds / 1000.0) > 0){
        audioFile.stream.seek(audioFile.stream.position() - audioFile.sample_rate*2*(milliseconds / 1000.0));
        Serial.printf("\nCurrent position: %dth byte\n", audioFile.stream.position());
    }else{
        audioFile.stream.seek(audioFile.header_size);
        Serial.printf("\nCurrent position: %dth byte\n", audioFile.stream.position());
    }
}

void AudioStreamer::progressBar(void){
    if(audioFile.data_size == 0) return;
    int progress = (int)((double)audioFile.stream.position() / audioFile.data_size * 100.0f);
    int totalSeconds = audioFile.data_size/(audioFile.sample_rate*2);
    int currentSecond = audioFile.stream.position()/(audioFile.sample_rate*2);
    Serial.printf("\r%3d%%", progress);
    Serial.printf(" [");
    for(int i = 0; i < 50; i++){
        if(i < progress/2)
            Serial.write('+');
        else
            Serial.write(' ');
    }
    Serial.printf("]\t%02d:%02d / %02d:%02d", currentSecond/60, currentSecond%60, totalSeconds/60, totalSeconds%60);
    Serial.flush();
}

void showINFO(void){
    Serial.printf("bass: %1.1f  mid: %1.1f  tre: %1.1f     junoRate: %1.2f  junoDepth: %4.1f  junoMix: %1.2f     reverbMix: %1.2f  reverbFB: %1.2f\n", bassGain, midGain, treGain, junoRate, junoDepth, junoMix, reverbMix, reverbFeedback);
}

void dacLow(void){
    pinMode(25, OUTPUT);
    pinMode(26, OUTPUT);
    digitalWrite(25, LOW);
    digitalWrite(26, LOW);
}

void i2s_attach(uint32_t buffer_size, uint32_t sample_rate){
    i2s_config_t cfg = {
        .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_TX | I2S_MODE_DAC_BUILT_IN),
        .sample_rate = sample_rate,
        .bits_per_sample = I2S_BITS_PER_SAMPLE_8BIT,
        .channel_format = I2S_CHANNEL_FMT_RIGHT_LEFT,
        .communication_format = I2S_COMM_FORMAT_STAND_MSB,
        .intr_alloc_flags = 0,
        .dma_buf_count = 8,
        .dma_buf_len = (int) buffer_size,
        .use_apll = true,
        .tx_desc_auto_clear = true,
        .fixed_mclk = 0
    };
    i2s_driver_install(I2S_NUM_0, &cfg, 0, NULL);
    i2s_set_dac_mode(I2S_DAC_CHANNEL_BOTH_EN);
    i2s_zero_dma_buffer(I2S_NUM_0);
}

void i2s_detach(void){
    i2s_driver_uninstall(I2S_NUM_0);
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
