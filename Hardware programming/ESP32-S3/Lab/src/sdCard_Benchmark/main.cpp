#include <Arduino.h>
#include <SD_MMC.h>

#define SD_CMD 4
#define SD_CLK 5
#define SD_DAT0 6

void setup() {
    Serial.begin(115200);

    SD_MMC.setPins(SD_CLK, SD_CMD, SD_DAT0);

    uint8_t *buffer;
    buffer = (uint8_t*) malloc(16*1024 * sizeof(uint8_t));

    while(Serial.available() == 0)  delay(10);

    if(!SD_MMC.begin("/sdcard", true, false, 40000, 5U)){
        Serial.println("SD init failed!");
        return;
    }

    File file = SD_MMC.open("/150mb.webm");

    if(!file){
        Serial.println("Cannot open file");
        return;
    }

    uint32_t fileSize = file.size();
    Serial.printf("File size reported: %u bytes\n", fileSize);
    size_t total = 0;
    uint32_t start = millis();

    while(total < fileSize){
        size_t toRead = min((uint32_t)(16 * 1024), fileSize - total);
        int n = file.read(buffer, toRead);

        if(n <= 0){
            Serial.println("Read error or premature EOF");
            break;
        }

        total += n;
    }

    uint32_t elapsed = millis() - start;

    file.close();

    float speed =
        (total / 1024.0) /
        (elapsed / 1000.0);

    Serial.printf("Read: %.2lf MiBs\n", total / 1024.0 / 1024.0);
    Serial.printf("Time: %lu ms\n", elapsed);
    Serial.printf("Speed: %.2f KB/s\n", speed);
    free(buffer);
}

void loop(){}