char a;
char b;

void setup() {
    Serial.begin(9600);
}

void loop() {
    if (Serial.available() >= 2) {
        a = Serial.read();
        b = Serial.read();
        printChars(a, b);
    }
}

void printChars(char a, char b) {
    Serial.print(a);
    Serial.print(b);
}
