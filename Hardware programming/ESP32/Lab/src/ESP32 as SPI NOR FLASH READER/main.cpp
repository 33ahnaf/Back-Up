#include <Arduino.h>
#include <SPI.h>

#define FLASH_CS    5

#define PIN_SCK     18
#define PIN_MISO    19
#define PIN_MOSI    23

#define FLASH_SIZE  0x1000000UL
#define BLOCK_SIZE  256

uint8_t buffer[BLOCK_SIZE];

void readFlash(uint32_t addr, uint8_t *buf, uint32_t len){
    SPI.beginTransaction(SPISettings(20000000, MSBFIRST, SPI_MODE0));

    digitalWrite(FLASH_CS, LOW);

    SPI.transfer(0x0B);          // Fast Read
    SPI.transfer(addr >> 16);
    SPI.transfer(addr >> 8);
    SPI.transfer(addr);
    SPI.transfer(0x00);          // Dummy byte

    for(uint32_t i = 0; i < len; i++)
        buf[i] = SPI.transfer(0);

    digitalWrite(FLASH_CS, HIGH);

    SPI.endTransaction();
}

void setup(){
    Serial.begin(250000);

    SPI.begin(PIN_SCK, PIN_MISO, PIN_MOSI, FLASH_CS);

    pinMode(FLASH_CS, OUTPUT);
    digitalWrite(FLASH_CS, HIGH);

    delay(1000);

    // Wait for PC
    while(!Serial.available())
        delay(1);

    Serial.read();

    for(uint32_t addr = 0; addr < FLASH_SIZE; addr += BLOCK_SIZE){
        readFlash(addr, buffer, BLOCK_SIZE);
        // memset(buffer, 0x55, BLOCK_SIZE);

        size_t sent = 0;

        Serial.write(buffer, BLOCK_SIZE);
    }
}

void loop(){}












// #include <Arduino.h>
// #include <SPI.h>

// #define FLASH_CS 5

// void setup() {
//     Serial.begin(115200);

//     SPI.begin(18,19,23,FLASH_CS);

//     pinMode(FLASH_CS,OUTPUT);
//     digitalWrite(FLASH_CS,HIGH);

//     delay(100);

//     digitalWrite(FLASH_CS,LOW);

//     SPI.transfer(0x9F);

//     byte m = SPI.transfer(0);
//     byte t = SPI.transfer(0);
//     byte c = SPI.transfer(0);

//     digitalWrite(FLASH_CS,HIGH);

//     Serial.printf("ID: %02X %02X %02X\n",m,t,c);
// }

// void loop(){}