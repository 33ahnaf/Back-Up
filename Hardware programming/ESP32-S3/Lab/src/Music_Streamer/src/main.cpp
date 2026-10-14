#include <Arduino.h>
#include <SD_MMC.h>
// #include <Wire.h>

#include "SerialHandleInputs.h"
#include "AudioStreamer.h"
#include "LGFX_Helper.h"
#include "globals.h"
#include "MISC.h"
#include "GUI.h"

#define xTask_AUDIO_STREAMER_STACK_SIZE_BYTES 3392

TaskHandle_t xTaskHandle_AudioStream = NULL;
void vTask_AudioStream(void*){
    while(true){
        // audio.update();
        delay(500);
        taskYIELD();
    }
}


void setup(){
    Serial.begin(115200);
    SD_MMC.setPins(SD_CLK, SD_CMD, SD_DAT0);
    if(!SD_MMC.begin("/sdcard", SD_1bit, false, SD_FREQ, 5U)){
        Serial.printf("Error: Cannot initiate SD card! [main]\n");
        while(1) delay(100);
    }

    tft.begin();
    tft.setRotation(TFT_ROTATION);
    tft.fillScreen(TFT_BLACK);

    
    // BaseType_t xReturned = xTaskCreate(
    //     vTask_AudioStream,
    //     "AudioTask",
    //     xTask_AUDIO_STREAMER_STACK_SIZE_BYTES,
    //     NULL,
    //     2,
    //     &xTaskHandle_AudioStream
    // );

    // if(xReturned != pdPASS)
    //     Serial.printf("Error: Failed to create task. [main]\n");
}


void loop(){
    UpdateGUI();
    HandleInputs();
    delay(10);
    // lcd.backlight();
    // xTask_printHighWaterMark(xTaskHandle_AudioStream, 1000, xTask_AUDIO_STREAMER_STACK_SIZE_BYTES);
}