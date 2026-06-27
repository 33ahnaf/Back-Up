#include <Arduino.h>
#include <SD.h>
#include <Wire.h>

#include "SerialHandleInputs.h"
#include "AudioStreamer.h"
#include "globals.h"
#include "MISC.h"
#include "GUI.h"

#define SD_CS 5
#define xTask_AUDIO_STREAMER_STACK_SIZE_BYTES 3392

TaskHandle_t xTaskHandle_AudioStream = NULL;
void vTask_AudioStream(void*){
    while(true){
        audio.update();
        taskYIELD();
    }
}


void setup(){
    Serial.begin(115200);
    if(!SD.begin(SD_CS, SPI, 40000000)){
        Serial.printf("Error: Cannot initiate SD card! [main]\n");
        while(1) delay(100);
    }
    lcd.begin();

    
    BaseType_t xReturned = xTaskCreate(
        vTask_AudioStream,
        "AudioTask",
        xTask_AUDIO_STREAMER_STACK_SIZE_BYTES,
        NULL,
        2,
        &xTaskHandle_AudioStream
    );

    if(xReturned != pdPASS)
        Serial.printf("Error: Failed to create task. [main]\n");
}


void loop(){
    UpdateGUI();
    HandleInputs();
    delay(10);
    // xTask_printHighWaterMark(xTaskHandle_AudioStream, 1000, xTask_AUDIO_STREAMER_STACK_SIZE_BYTES);
}