#include <Arduino.h>

const int pins_to_avoid[23] = {
    26, 27, 28, 29, 30, 31, 32,     // FLASH/PSRAM
    33, 34, 35, 36, 37,             // Octal PSRAM
    3, 45, 46,                      // Strappings
    19, 20,                         // USB
    43, 44,                         // Serial
    22, 23, 24, 25                  // GPIO pins of ESP32-S3 are numbered from 0 ~ 21 and 26 ~ 48
};

bool PinSholdBeAvoided(int pin){
    for(int i = 0; i < 23; i++)
        if(pin == pins_to_avoid[i])
            return true;
    return false;
}

void setup(){
    Serial.begin(115200);
    for(int i = 0; i <= 48; i++){
        if(PinSholdBeAvoided(i))
            continue;
        pinMode(i, OUTPUT);
        Serial.printf("%d enabled\n", i);
    }
}

void loop(){
    if(Serial.available() > 0){
        int pin = Serial.parseInt();
        int val = Serial.parseInt();
        while(Serial.available() > 0 && Serial.peek() == '\n' || Serial.peek() == '\r')
            Serial.read();
        Serial.printf("PIN == %d, VALUE == %d\n", pin, val);
        digitalWrite(pin, val);
    }
}