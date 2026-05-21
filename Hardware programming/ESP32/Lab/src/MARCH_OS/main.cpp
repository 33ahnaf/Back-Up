#include <Arduino.h>
#include <SD.h>

#define SD_CS 5

File root;

void showFiles(File *file);

void setup(){
    Serial.begin(115200);
    if(!SD.begin(SD_CS, SPI, 40000000)){
        Serial.printf("Cannot initialize SD card module!\n");
        while(1);
    }
    root = SD.open("/");
}

void loop(){
    if(Serial.available() > 0){
        String command = Serial.readStringUntil('\n');
        command.trim();
        if(!strcmp(command.c_str(), "ls"))
            showFiles(&root);
        while(Serial.available() > 0)
            Serial.read();
        Serial.printf("> ");
    }
}



void showFiles(File *file){
    file->rewindDirectory();
    while(1){
        File entry = file->openNextFile();
        if(!entry) break;
        Serial.println(entry.name());
        entry.close();
    }
}