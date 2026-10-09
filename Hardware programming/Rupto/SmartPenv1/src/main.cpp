// =============================================================================
// main.cpp — SmartPen entry point
// =============================================================================
// Deliberately thin: this file's only job is to wire the modules together
// and run the non-blocking main loop. All real logic lives in Tracker
// (sensor pipeline) and PenWiFiServer (networking).
// =============================================================================
#include <Arduino.h>
#include "Config.h"
#include "Tracker.h"
#include "WiFiServer.h"

namespace {

Tracker tracker;
PenWiFiServer wifiServer;

uint32_t lastStreamUs = 0;
uint32_t lastDebugMs = 0;

// Loop-timing stats, purely for the Serial debug readout.
uint32_t loopCount = 0;
uint32_t loopMaxDurationUs = 0;

// -----------------------------------------------------------------------
// Serial command handling
// -----------------------------------------------------------------------
// Simple single-character commands, per the spec's "optional calibration
// command over Serial":
//   c -> recalibrate
//   r -> reset position to canvas center
//   d -> toggle verbose per-sample debug printing
// -----------------------------------------------------------------------
bool verboseDebug = false;

void handleSerialCommands() {
    while (Serial.available() > 0) {
        char c = static_cast<char>(Serial.read());
        switch (c) {
            case 'c':
            case 'C':
                Serial.println(F("[main] Recalibration requested."));
                tracker.calibrate();
                break;
            case 'r':
            case 'R':
                tracker.resetPosition();
                Serial.println(F("[main] Position reset to origin."));
                break;
            case 'd':
            case 'D':
                verboseDebug = !verboseDebug;
                Serial.print(F("[main] Verbose debug: "));
                Serial.println(verboseDebug ? F("ON") : F("OFF"));
                break;
            default:
                break; // ignore newlines / unknown chars
        }
    }
}

// -----------------------------------------------------------------------
// Debug printing — throttled so it doesn't itself become a bottleneck
// -----------------------------------------------------------------------
void printDebugIfDue() {
    uint32_t nowMs = millis();
    if (nowMs - lastDebugMs < Config::DEBUG_PRINT_PERIOD_MS) return;
    lastDebugMs = nowMs;

    const TrackerFrame &f = tracker.latestFrame();

    Serial.printf(
        "[dbg] pos=(%.4f,%.4f,%.4f)m vel=(%.3f,%.3f,%.3f)m/s "
        "acc=(%.3f,%.3f,%.3f)m/s2 q=(%.2f,%.2f,%.2f,%.2f) "
        "stat=%d pen=%d clients=%u loopMaxUs=%lu\n",
        f.posX, f.posY, f.posZ,
        f.velX, f.velY, f.velZ,
        f.accX, f.accY, f.accZ,
        f.qw, f.qx, f.qy, f.qz,
        f.stationary ? 1 : 0, f.penDown,
        static_cast<unsigned>(wifiServer.clientCount()),
        static_cast<unsigned long>(loopMaxDurationUs));

    loopMaxDurationUs = 0; // reset the max window for the next interval
}

} // namespace

void setup() {
    Serial.begin(Config::SERIAL_BAUD);
    uint32_t serialWaitStart = millis();
    while (!Serial && millis() - serialWaitStart < 2000) {
        ; // give USB-CDC a moment to enumerate, but don't hang forever if
          // nothing is plugged in (this is a standalone device)
    }

    Serial.println(F("\n=== SmartPen booting ==="));

    if (!tracker.begin()) {
        Serial.println(F("[main] FATAL: MPU6050 not detected. Check wiring "
                          "(SDA=GPIO5, SCL=GPIO6) and power. Halting."));
        // We don't spin forever silently — keep announcing the problem so
        // it's obvious on a reconnecting serial monitor, and give the user
        // a fighting chance to fix wiring and reset without recompiling.
        while (true) {
            Serial.println(F("[main] Waiting for MPU6050... (reset the "
                              "board after fixing wiring)"));
            delay(2000);
        }
    }
    Serial.println(F("[main] MPU6050 online."));

    if (tracker.hasStoredCalibration()) {
        Serial.println(F("[main] Using saved calibration from flash. Send "
                          "'c' over Serial any time to recalibrate."));
    } else {
        tracker.calibrate();
    }

    wifiServer.onResetRequested([]() { tracker.resetPosition(); });

    if (!wifiServer.begin()) {
        Serial.println(F("[main] FATAL: Wi-Fi/LittleFS init failed. "
                          "Halting."));
        while (true) {
            delay(1000);
        }
    }

    Serial.println(F("[main] Ready. Serial commands: c=calibrate, "
                      "r=reset position, d=toggle verbose debug."));
}

void loop() {
    uint32_t loopStartUs = micros();

    handleSerialCommands();

    // Defensive: if the sensor drops off the bus mid-operation (loose
    // wire, brownout), detect it and keep retrying rather than silently
    // streaming garbage/stale data forever.
    static uint32_t lastPingMs = 0;
    if (!tracker.imuConnected()) {
        uint32_t nowMs = millis();
        if (nowMs - lastPingMs > 500) {
            lastPingMs = nowMs;
            Serial.println(F("[main] MPU6050 disconnected — retrying..."));
            tracker.begin();
        }
    }

    bool haveNewSample = tracker.update();

    if (haveNewSample) {
        // Stream to the browser at STREAM_RATE_HZ, decoupled from the
        // (faster) IMU sample rate — the integrator wants small dt, the
        // network/browser doesn't need updates faster than it can render.
        uint32_t nowUs = micros();
        if (nowUs - lastStreamUs >= Config::STREAM_PERIOD_US) {
            lastStreamUs = nowUs;
            wifiServer.broadcastFrame(tracker.latestFrame());
        }

        if (verboseDebug) {
            printDebugIfDue();
        }
    }

    // Always let the throttled summary print run, even if verboseDebug is
    // off — this is the "always-on heartbeat" so you can tell at a glance
    // the firmware hasn't hung, without opting into full verbose spam.
    if (!verboseDebug) {
        printDebugIfDue();
    }

    uint32_t loopDurationUs = micros() - loopStartUs;
    if (loopDurationUs > loopMaxDurationUs) loopMaxDurationUs = loopDurationUs;
    loopCount++;
}