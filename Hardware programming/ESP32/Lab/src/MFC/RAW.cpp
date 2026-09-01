#include "RAW.h"
#include <Arduino.h>

// ---------- Configuration ----------
#define ADC_CHANNEL     ADC1_CHANNEL_5 // GPIO33 on most ESP32 dev boards
#define ADC_ATTEN       ADC_ATTEN_DB_0   // 0-1.1V range, most linear/accurate
#define ADC_WIDTH       ADC_WIDTH_BIT_12 // 12-bit resolution (0-4095)
#define DEFAULT_VREF    1100          // Fallback, mV (only used if no eFuse calibration)
#define NUM_SAMPLES     1024           // Ultrasampling count hehehaha
#define SAMPLE_DELAY_US 50         // Delay between samples

esp_adc_cal_characteristics_t adc_chars;

void setupRawInput(void){
    adc1_config_width(ADC_WIDTH);
    adc1_config_channel_atten(ADC_CHANNEL, ADC_ATTEN);

    // Characterize ADC — uses factory calibration (Vref or Two Point) if available
    esp_adc_cal_value_t cal_type = esp_adc_cal_characterize(
        ADC_UNIT_1, ADC_ATTEN, ADC_WIDTH, DEFAULT_VREF, &adc_chars);

    // Report which calibration source is being used
    if(cal_type == ESP_ADC_CAL_VAL_EFUSE_TP){
        Serial.println("ADC calibration: Two Point (best accuracy)");
    }else if(cal_type == ESP_ADC_CAL_VAL_EFUSE_VREF){
        Serial.println("ADC calibration: eFuse Vref");
    }else
        Serial.println("ADC calibration: Default Vref (least accurate — consider external ADC)");
}

// ---------- Helper: oversampled raw reading with basic outlier rejection ----------
uint32_t readRawOversampled(){
    uint32_t samples[NUM_SAMPLES];

    // Collect samples
    for(int i = 0; i < NUM_SAMPLES; i++){
        samples[i] = adc1_get_raw(ADC_CHANNEL);
        ets_delay_us(SAMPLE_DELAY_US);
    }

    // Sort for median-based outlier trimming (simple insertion sort — fine for small N)
    for(int i = 1; i < NUM_SAMPLES; i++){
        uint32_t key = samples[i];
        int j = i - 1;
        while(j >= 0 && samples[j] > key){
            samples[j + 1] = samples[j];
            j--;
        }
        samples[j + 1] = key;
    }

    // Trim top/bottom 10% (outlier rejection), average the rest
    int trim = NUM_SAMPLES / 10;
    uint64_t sum = 0;
    int count = 0;
    for(int i = trim; i < NUM_SAMPLES - trim; i++){
        sum += samples[i];
        count++;
    }

    return (uint32_t)(sum / count);
}