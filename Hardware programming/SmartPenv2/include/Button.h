#pragma once
// =============================================================================
// Button.h — Debounced digital input
// =============================================================================
// A mechanical button bounces for a few milliseconds when pressed/released,
// which without debouncing shows up as several rapid spurious transitions
// instead of one clean edge. This is a small time-based debouncer: it only
// commits to a new stable state after the raw reading has held steady for
// Config::BUTTON_DEBOUNCE_MS.
//
// Not IMU-specific at all — kept generic so it could debounce any future
// digital input (a second button, a reed switch, etc) without change.
// =============================================================================

#include <stdint.h>

class DebouncedButton {
public:
    // pin: GPIO to read. activeLow: true if the pin reads LOW while
    // pressed (typical for INPUT_PULLUP wiring to GND, which is how the
    // pen-tip button is wired — see Config::PIN_PEN_BUTTON).
    void begin(int pin, uint32_t debounceMs, bool activeLow = true);

    // Call every loop() iteration. Cheap (one digitalRead + a timestamp
    // comparison), safe to call as fast as the main loop runs.
    void update();

    // Debounced, "is it currently pressed" state.
    bool isPressed() const { return stablePressed_; }

    // True only on the exact update() call where the debounced state
    // transitioned from released -> pressed (edge-triggered, useful if a
    // future feature wants to react once per press rather than every
    // loop while held).
    bool justPressed() const { return justPressed_; }
    bool justReleased() const { return justReleased_; }

private:
    int pin_ = -1;
    bool activeLow_ = true;
    uint32_t debounceMs_ = 15;

    bool stablePressed_ = false;
    bool lastRawPressed_ = false;
    uint32_t lastChangeMs_ = 0;

    bool justPressed_ = false;
    bool justReleased_ = false;
};
