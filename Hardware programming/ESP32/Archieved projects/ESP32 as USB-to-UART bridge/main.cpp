// USB <-> STB UART bridge
#include <Arduino.h>

#define STB_RX 16   // ESP32 receives from STB TX
#define STB_TX 17   // ESP32 transmits to STB RX

#define STB_BAUD 115200

void setup(){
    Serial.begin(115200);

    Serial2.begin(
        STB_BAUD,
        SERIAL_8N1,
        STB_RX,
        STB_TX
    );

    Serial.println("UART bridge ready.");
}

void loop(){
    // STB -> PC
    while(Serial2.available() > 0){
        Serial.write(Serial2.read());
    }

    // PC -> STB
    while(Serial.available() > 0){
        Serial2.write(Serial.read());
    }
}







// #include <Arduino.h>

// volatile uint32_t count = 0;

// #define RX_PIN 16   // ESP32 receives from STB TX

// void setup(){
//     Serial.begin(115200);
// }

// void loop(){
//     static int last = HIGH;
//     int now = digitalRead(RX_PIN);

//     if(now != last){
//         count++;
//         last = now;
//     }

//     static uint32_t t = 0;
//     if(millis() - t > 1000){
//         t = millis();
//         Serial.println(count);
//         count = 0;
//     }
// }