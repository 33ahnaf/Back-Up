#define OUTPUT_PIN 9
#define PLUS_DELAY 1 // 200, 1
#define MINUS_DELAY 1 // 200, 1
#define PLUS_PLUS 1 // 100, 1
#define MINUS_MINUS 1 // 100, 1
int i;
void setup(){
    pinMode(OUTPUT_PIN, OUTPUT);
}
void loop(){
    for (i = 0; i < 255; i+=PLUS_PLUS)
    {
        analogWrite(OUTPUT_PIN, i);
        delay(PLUS_DELAY);
    }
    
    for (i = 255; i > 0; i-=MINUS_MINUS)
    {
        analogWrite(OUTPUT_PIN, i);
        delay(MINUS_DELAY);
    }
}