#ifndef RAW__H
#define RAW__H

#include "esp_adc_cal.h"
#include "driver/adc.h"

extern esp_adc_cal_characteristics_t adc_chars;

void setupRawInput(void);
uint32_t readRawOversampled();

#endif