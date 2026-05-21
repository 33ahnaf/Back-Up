#include "MISC.h"
#include "globals.h"
#include "AudioFile.h"
#include <Arduino.h>
#include <driver/i2s.h>
#include "esp_system.h"
#include "esp_heap_caps.h"

void dacLow(void){
    pinMode(25, OUTPUT);
    pinMode(26, OUTPUT);
    digitalWrite(25, LOW);
    digitalWrite(26, LOW);
}

void showINFO(void){
    Serial.printf("bass: %1.1f  mid: %1.1f  tre: %1.1f     junoRate: %1.2f  junoDepth: %4.1f  junoMix: %1.2f     reverbMix: %1.2f  reverbFB: %1.2f\n", bassGain, midGain, treGain, junoRate, junoDepth, junoMix, reverbMix, reverbFeedback);
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

void fastForwardAudio(AudioFile *audioFile){
    if(audioFile->stream.position() + audioFile->sample_rate*2*5 > audioFile->file_size){
        audioFile->stream.seek(audioFile->file_size-1);
        Serial.printf("\nCurrent position: %dth byte\n", audioFile->stream.position());
    }else{
        audioFile->stream.seek(audioFile->stream.position() + audioFile->sample_rate*2*5);
        Serial.printf("\nCurrent position: %dth byte\n", audioFile->stream.position());
    }
}

void rewindAudio(AudioFile *audioFile){
    if(audioFile->stream.position() - audioFile->sample_rate*2*5 > 0){
        audioFile->stream.seek(audioFile->stream.position() - audioFile->sample_rate*2*5);
        Serial.printf("\nCurrent position: %dth byte\n", audioFile->stream.position());
    }else{
        audioFile->stream.seek(audioFile->header_size);
        Serial.printf("\nCurrent position: %dth byte\n", audioFile->stream.position());
    }
}

void progressBar(AudioFile *audioFile){
    int progress = (int)((double)audioFile->stream.position() / audioFile->data_size * 100.0f);
    int totalSeconds = audioFile->data_size/(audioFile->sample_rate*2);
    int currentSecond = audioFile->stream.position()/(audioFile->sample_rate*2);
    Serial.printf("\r%3d%%", progress);
    Serial.printf(" [");
    for(int i = 0; i < 50; i++){
        if(i < progress/2)
            Serial.printf("+");
        else
            Serial.printf(" ");
    }
    Serial.printf("]\t%02d:%02d / %02d:%02d", currentSecond/60, currentSecond%60, totalSeconds/60, totalSeconds%60);
    Serial.flush(1);
}

void get_HEAP_AND_STACK_info(void){
    Serial.printf("\n\nFree heap: %u bytes\n", ESP.getFreeHeap());
    Serial.printf("Free heap: %u\n", heap_caps_get_free_size(MALLOC_CAP_8BIT));
    Serial.printf("Largest block: %u\n\n", heap_caps_get_largest_free_block(MALLOC_CAP_8BIT));
}