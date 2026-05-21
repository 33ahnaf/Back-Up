#include <Arduino.h>
// #include <SD.h>
#include <stdint.h>
#include <TFT_eSPI.h>
// #include "AudioStreamer.h"
// #include "globals.h"
// #include <Wire.h>
// #include <LiquidCrystal_I2C.h>

// #include "WiFi_Downloader.h"
// #include "AudioStreamerTemp.h"

// #define SD_CS 5
// #define LCD_SDA 16
// #define LCD_SCL 17

TFT_eSPI tft = TFT_eSPI();

void setup(){
    Serial.begin(115200);
    // Wire.begin(LCD_SDA, LCD_SCL);
    // lcd.begin();
    // dacLow();
    // if(!SD.begin(SD_CS, SPI, 40000000)){
    //     Serial.printf("Cannot initialize SD card module!\n");
    //     while(1);
    // }

    tft.init();
    tft.setRotation(0);
}

void loop(){
    // if(Serial.available() > 0){
    //     String inputString = Serial.readStringUntil('\n');
    //     inputString.trim();
    //     if(!strcmp(inputString.c_str(), "upload")){
    //         // downloadFile("/SigmaDelta/Musics/");
    //         Serial.println("Uploading feature is not available right now.");
    //     }else{
    //         Serial.printf("Now Playing: %s\n", inputString.c_str());
    //         streamAudio(inputString.c_str());
    //         Serial.printf("Playback Stopped\n\n");
    //     }
    //     while(Serial.available() > 0)
    //             Serial.read();
    // }




    tft.fillScreen(TFT_BLACK);
    delay(1000);

    tft.fillScreen(TFT_RED);
    delay(1000);

    tft.fillScreen(TFT_GREEN);
    delay(1000);

    tft.fillScreen(TFT_BLUE);
    delay(1000);
}



































// #include <Arduino.h>
// #include <SPI.h>

// #define CS   5
// #define DC   21
// #define RST  22

// void sendByte(uint8_t val, bool isData) {
//   digitalWrite(DC, isData ? HIGH : LOW);
//   digitalWrite(CS, LOW);
//   SPI.transfer(val);
//   digitalWrite(CS, HIGH);
// }

// void resetLCD() {
//   digitalWrite(RST, LOW);
//   delay(50);
//   digitalWrite(RST, HIGH);
//   delay(150);
// }

// void setup() {
//   pinMode(CS, OUTPUT);
//   pinMode(DC, OUTPUT);
//   pinMode(RST, OUTPUT);

//   digitalWrite(CS, HIGH);

//   Serial.begin(115200);

//   // Try different SPI modes automatically
//   for (int mode = 0; mode < 4; mode++) {

//     Serial.print("Testing SPI mode: ");
//     Serial.println(mode);

//     SPI.begin(18, -1, 23, CS);
//     SPI.beginTransaction(SPISettings(1000000, MSBFIRST, mode));

//     resetLCD();

//     // Send a basic wake sequence first
//     sendByte(0x01, false); // reset
//     delay(100);
//     sendByte(0x11, false); // sleep out
//     delay(100);

//     // BRUTE FORCE LOOP
//     for (int i = 0; i < 500; i++) {
//       for (int b = 0; b < 256; b++) {
//         sendByte(b, false); // command
//         delayMicroseconds(50);
//         sendByte(b, true);  // data
//         delayMicroseconds(50);
//       }
//     }

//     SPI.endTransaction();

//     delay(2000); // pause between modes
//   }
// }

// void loop() {}