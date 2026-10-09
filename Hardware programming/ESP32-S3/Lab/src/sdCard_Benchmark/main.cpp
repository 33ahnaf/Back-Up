#include <SPI.h>
#include <SD.h>

#define SD_CS 9

void setup() {
    uint8_t *buffer;
    buffer = (uint8_t*) malloc(16*1024 * sizeof(uint8_t));
    Serial.begin(115200);

    if (!SD.begin(SD_CS, SPI, 40000000)) {
        Serial.println("SD init failed!");
        return;
    }

    File file = SD.open("/150mb.webm");

    if (!file) {
        Serial.println("Cannot open file");
        return;
    }

    uint32_t fileSize = file.size();
    Serial.printf("File size reported: %u bytes\n", fileSize);
    size_t total = 0;
    uint32_t start = millis();

    while (total < fileSize) {
        size_t toRead = min((uint32_t)(16 * 1024), fileSize - total);
        int n = file.read(buffer, toRead);

        if (n <= 0){
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

void loop() {}