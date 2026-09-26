#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

// PIN 48 is standard for official Espressif DevKits. 
// Change to 38, 21, or 18 if your specific board variant requires it.
#define RGB_LED_PIN   48 
#define NUM_PIXELS    1 

Adafruit_NeoPixel pixels(NUM_PIXELS, RGB_LED_PIN, NEO_GRB + NEO_KHZ800);

// Function Declarations (Required for pure C++ in PlatformIO)
void policeStrobe();
void rainbowCycle(int speedDelay);
void cyberpunkPulse(int cycles);
void glitchEffect(unsigned long duration);
void fireBreath(unsigned long duration);

void setup() {
    Serial.begin(115200);
    pixels.begin(); 
    pixels.setBrightness(255); // 40/255 brightness to protect your eyes
    Serial.println("ESP32-S3 RGB Crazy Effects Demo Started!");
}

void loop() {
    // Effect 1: Police Strobe
    for(int i = 0; i < 8; i++) {
        policeStrobe();
    }
    
    // Effect 2: Smooth Rainbow Cycle
    rainbowCycle(15);
    
    // Effect 3: Cyberpunk Neon Pulse
    cyberpunkPulse(4);
    
    // Effect 4: Chaotic Glitch / Static
    glitchEffect(2500); 
    
    // Effect 5: Breathing Fire
    fireBreath(3000); 
}

// --- EFFECT 1: POLICE STROBE ---
void policeStrobe() {
    pixels.setPixelColor(0, pixels.Color(255, 0, 0)); // Red
    pixels.show();
    delay(100);
    pixels.setPixelColor(0, pixels.Color(0, 0, 255)); // Blue
    pixels.show();
    delay(100);
}

// --- EFFECT 2: SMOOTH RAINBOW HUE CYCLE ---
void rainbowCycle(int speedDelay) {
    for(long firstPixelHue = 0; firstPixelHue < 3 * 65536; firstPixelHue += 256) {
        pixels.setPixelColor(0, pixels.gamma32(pixels.ColorHSV(firstPixelHue)));
        pixels.show();
        delay(speedDelay);
    }
}

// --- EFFECT 3: CYBERPUNK NEON PULSE ---
void cyberpunkPulse(int cycles) {
    for(int c = 0; c < cycles; c++) {
        // Fade from Hot Pink to Bright Cyan
        for(int i = 0; i <= 255; i += 8) {
            pixels.setPixelColor(0, pixels.Color(255 - i, i, 150 + (i/4)));
            pixels.show();
            delay(4);
        }
        // Fade from Bright Cyan back to Hot Pink
        for(int i = 255; i >= 0; i -= 8) {
            pixels.setPixelColor(0, pixels.Color(255 - i, i, 150 + (i/4)));
            pixels.show();
            delay(4);
        }
    }
}

// --- EFFECT 4: CHAOTIC GLITCH / STATIC ---
void glitchEffect(unsigned long duration) {
    unsigned long startTime = millis();
    while(millis() - startTime < duration) {
        int r = random(0, 256);
        int g = random(0, 256);
        int b = random(0, 256);
        
        // Randomly inject dropouts for a harsher stutter effect
        if(random(0, 4) == 0) {
            pixels.setPixelColor(0, pixels.Color(0, 0, 0));
        } else {
            pixels.setPixelColor(0, pixels.Color(r, g, b));
        }
        
        pixels.show();
        delay(random(8, 60)); 
    }
}

// --- EFFECT 5: BREATHING FIRE ---
void fireBreath(unsigned long duration) {
    unsigned long startTime = millis();
    while(millis() - startTime < duration) {
        int r = random(220, 256);
        int g = random(15, 85); // Shifting green values produce orange & yellow tints
        int b = 0;              
        
        pixels.setPixelColor(0, pixels.Color(r, g, b));
        pixels.show();
        delay(random(20, 100));
    }
}
