#include <Arduino.h>
#include <stdint.h>

uint64_t dummy;

void setup(){
    Serial.begin(115200);
    unsigned long init, end;
    double interval;
    init = micros();
    for(dummy = 0; dummy < 240000000; dummy++);
    end = micros();
    interval = (double) (end - init) / 1000000;
    Serial.printf("%lf\n", interval);

    init = micros();
    for(dummy = 0; micros() - init <= 1000000; dummy++);
    Serial.printf("%ld\n", dummy);
}

void loop(){}