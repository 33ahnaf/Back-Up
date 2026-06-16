#include <SPI.h>
#include <SD.h>

#define SD_CS 21
#define SD_SCK 7
#define SD_MISO 8
#define SD_MOSI 9

void setup() {
    delay(5000);
    uint8_t *buffer;
    buffer = (uint8_t*) malloc(16*1024 * sizeof(uint8_t));
    Serial.begin(115200);

    SPI.begin(SD_SCK, SD_MISO, SD_MOSI, SD_CS);
    if (!SD.begin(SD_CS, SPI, 40000000)) {
        Serial.println("SD init failed!");
        return;
    }

    File file = SD.open("/150MB.webm");

    if (!file) {
        Serial.println("Cannot open file");
        return;
    }

    uint32_t start = millis();
    size_t total = 0;

    Serial.printf("Starting counting...\n");
    while (file.available()) {
        int n = file.read(buffer, 16*1024);

        if (n <= 0)
            break;

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