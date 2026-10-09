#pragma once
// =============================================================================
// WiFiServer.h — Access Point + LittleFS static site + WebSocket streaming
// =============================================================================
// This module owns all networking: it brings up the ESP32 as its own Wi-Fi
// Access Point (no router/internet required), serves the browser UI straight
// out of LittleFS, and pushes TrackerFrames to connected clients over a
// WebSocket (no HTTP polling — the browser receives a push the instant a new
// frame is ready).
// =============================================================================

#include "Tracker.h"
#include "Config.h"
#include <ESPAsyncWebServer.h>
#include <functional>

class PenWiFiServer {
public:
    // Brings up the AP, mounts LittleFS, registers HTTP routes + WebSocket
    // handler. Returns false if LittleFS fails to mount (site can't be
    // served) — Wi-Fi AP itself essentially never fails.
    bool begin();

    // Called from main.cpp with e.g. `[](){ tracker.resetPosition(); }` so
    // that the browser's "Clear" button can zero the on-device integrator,
    // not just wipe the local canvas — otherwise stale velocity/position
    // would immediately redraw a jump on the next frame.
    void onResetRequested(std::function<void()> cb) { resetCallback_ = cb; }

    // Sends one TrackerFrame to every connected WebSocket client as a
    // compact JSON packet. Non-blocking — AsyncWebSocket queues the send
    // and returns immediately.
    void broadcastFrame(const TrackerFrame &frame);

    // Number of currently-connected WebSocket clients (used to skip doing
    // unnecessary work broadcasting to nobody).
    size_t clientCount() const;

private:
    AsyncWebServer server_{Config::HTTP_PORT};
    AsyncWebSocket ws_{"/ws"};
    std::function<void()> resetCallback_;

    void handleWebSocketEvent(AsyncWebSocket *server, AsyncWebSocketClient *client,
                               AwsEventType type, void *arg, uint8_t *data, size_t len);
};
