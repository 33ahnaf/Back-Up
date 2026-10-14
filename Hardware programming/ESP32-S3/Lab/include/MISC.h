#ifndef _MISC__H
#define _MISC__H

#include <Arduino.h>
#include <stdint.h>

void get_HEAP_AND_STACK_info(void);
void xTask_printHighWaterMark(uint32_t milliseconds, uint32_t stack_size);
void xTask_printHighWaterMark(TaskHandle_t xTask, uint32_t milliseconds, uint32_t stack_size);

#endif