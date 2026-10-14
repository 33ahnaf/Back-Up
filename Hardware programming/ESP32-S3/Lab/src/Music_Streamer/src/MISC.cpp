#include "MISC.h"
#include <Arduino.h>
#include "esp_system.h"
#include "esp_heap_caps.h"

void get_HEAP_AND_STACK_info(void){
    Serial.printf("\n\nFree heap: %u bytes\n", ESP.getFreeHeap());
    Serial.printf("Free heap: %u\n", heap_caps_get_free_size(MALLOC_CAP_8BIT));
    Serial.printf("Largest block: %u\n\n", heap_caps_get_largest_free_block(MALLOC_CAP_8BIT));
}

void xTask_printHighWaterMark(uint32_t milliseconds, uint32_t stack_size){
    static uint32_t last = 0;
    uint32_t water_mark = uxTaskGetStackHighWaterMark(NULL);
    if(millis() - last > milliseconds){
        Serial.printf("Free stack: %u bytes [%.2f%%]\n", water_mark, 100.0 - ((float)water_mark / (float)stack_size * 100.0));
        last = millis();
    }
}

void xTask_printHighWaterMark(TaskHandle_t xTask, uint32_t milliseconds, uint32_t stack_size){
    static uint32_t last = 0;
    uint32_t water_mark = uxTaskGetStackHighWaterMark(xTask);
    if(millis() - last > milliseconds){
        Serial.printf("Free stack: %u bytes [%.2f%%]\n", water_mark, 100.0 - ((float)water_mark / (float)stack_size * 100.0));
        last = millis();
    }
}