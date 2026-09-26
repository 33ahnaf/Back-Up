#include <Arduino.h>
#include "esp_flash.h"

String get_safe_flash_mode() {
    if (esp_flash_default_chip == NULL) return "Flash Not Initialized";
    
    // Read the active live flash configuration structure
    int mode = esp_flash_default_chip->read_mode;
    switch(mode) {
        case 0:  return "SLOWRD (Single Data Line)";
        case 1:  return "FASTRD (Single Data Line)";
        case 2:  return "DOUT (Dual Output)";
        case 3:  return "DIO (Dual I/O)";
        case 4:  return "QOUT (Quad Output)";
        case 5:  return "QIO (Quad I/O) - Full Quad Speed!";
        case 6:  return "OPI_STR (Octal SPI)";
        case 7:  return "OPI_DTR (Octal SPI)";
        default: return "Unknown Mode";
    }
}

#define TEST_BUFFER_SIZE 4096
uint8_t read_buffer[TEST_BUFFER_SIZE];

void run_flash_benchmark() {
    Serial.println("\n--- Running Flash Read Benchmark ---");
    uint32_t address = 0x10000; 
    uint32_t start_time = micros();
    
    // Read 4KB blocks 50 times (Total 200KB)
    for(int i = 0; i < 50; i++) {
        esp_flash_read(esp_flash_default_chip, read_buffer, address, TEST_BUFFER_SIZE);
    }
    
    uint32_t end_time = micros();
    uint32_t duration = end_time - start_time;
    
    Serial.printf("Time taken to read 200KB from flash: %u microseconds\n", duration);
    Serial.printf("Approximate Read Speed: %.2f MB/s\n", (200.0 * 1000000.0) / (duration * 1024.0));
}

void setup() {
    Serial.begin(115200);
    while(!Serial); 
    delay(2000);

    Serial.println("\n=== Live Flash Configuration Info ===");
    Serial.printf("Flash size reported by API: %d bytes (%d MB)\n", 
                  ESP.getFlashChipSize(), ESP.getFlashChipSize() / (1024 * 1024));

    Serial.print("Active App Flash SPI Mode: ");
    Serial.println(get_safe_flash_mode());

    run_flash_benchmark();


    Serial.println("=== PSRAM ===");
    Serial.printf("Flash: %u bytes\n", ESP.getFlashChipSize());
    Serial.printf("PSRAM: %u bytes\n", ESP.getPsramSize());
    Serial.printf("PSRAM type: %s\n",
                  psramFound() ? "Detected" : "Not detected");
}

void loop() {}
