// =============================================================================
// Button.cpp — Debounced digital input implementation
// =============================================================================
#include "Button.h"
#include <Arduino.h>

void DebouncedButton::begin(int pin, uint32_t debounceMs, bool activeLow) {
    pin_ = pin;
    debounceMs_ = debounceMs;
    activeLow_ = activeLow;

    pinMode(pin_, activeLow_ ? INPUT_PULLUP : INPUT);

    // Seed the initial state from a real read instead of defaulting to
    // "released", so a button already held down at boot is recognized
    // immediately rather than waiting for a transition.
    bool raw = digitalRead(pin_);
    lastRawPressed_ = activeLow_ ? !raw : raw;
    stablePressed_ = lastRawPressed_;
    lastChangeMs_ = millis();
}

void DebouncedButton::update() {
    justPressed_ = false;
    justReleased_ = false;

    bool raw = digitalRead(pin_);
    bool rawPressed = activeLow_ ? !raw : raw;

    uint32_t now = millis();

    if (rawPressed != lastRawPressed_) {
        // Raw reading changed — start (or restart) the debounce timer.
        // This deliberately restarts on every bounce, so we only ever
        // commit once the signal has been quiet for the full window.
        lastRawPressed_ = rawPressed;
        lastChangeMs_ = now;
    }

    if (rawPressed != stablePressed_ && (now - lastChangeMs_) >= debounceMs_) {
        stablePressed_ = rawPressed;
        if (stablePressed_) justPressed_ = true;
        else justReleased_ = true;
    }
}
