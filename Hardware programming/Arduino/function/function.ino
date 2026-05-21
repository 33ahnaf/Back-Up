int celsius = 100;
void setup(){
    Serial.begin(9600);
    Serial.print(celsius_to_fahrenheit(celsius));
}

void loop(){

}

int celsius_to_fahrenheit(int celsius){
    int fahrenheit = (celsius * (9.0/5.0)) + 32; // 9.0 and 5.0 are for float division or if you try to do this by int division then the result would be 1 instead of 1.8.
    return fahrenheit;
}