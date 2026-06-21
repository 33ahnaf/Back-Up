#include "MISC.h"
#include <Arduino.h>
#include "esp_system.h"
#include "esp_heap_caps.h"

void get_HEAP_AND_STACK_info(void){
    Serial.printf("\n\nFree heap: %u bytes\n", ESP.getFreeHeap());
    Serial.printf("Free heap: %u\n", heap_caps_get_free_size(MALLOC_CAP_8BIT));
    Serial.printf("Largest block: %u\n\n", heap_caps_get_largest_free_block(MALLOC_CAP_8BIT));
}