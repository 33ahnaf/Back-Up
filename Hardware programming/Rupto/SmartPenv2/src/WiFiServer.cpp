// =============================================================================
// WiFiServer.cpp — AP mode + LittleFS + AsyncWebSocket implementation
// =============================================================================
#include "WiFiServer.h"
#include <WiFi.h>
#include <LittleFS.h>

bool PenWiFiServer::begin() {
    if (!LittleFS.begin(true /*formatOnFail*/)) {
        Serial.println(F("[WiFiServer] LittleFS mount failed."));
        return false;
    }

    // --- Access Point ---
    // We don't need STA mode at all — the whole point is a standalone
    // device that works with zero infrastructure (no router, no internet).
    WiFi.mode(WIFI_AP);
    bool apOk = WiFi.softAP(Config::WIFI_SSID, Config::WIFI_PASSWORD,
                             Config::WIFI_CHANNEL);
    if (!apOk) {
        Serial.println(F("[WiFiServer] softAP() failed to start."));
        return false;
    }
    Serial.print(F("[WiFiServer] AP started. Connect to \""));
    Serial.print(Config::WIFI_SSID);
    Serial.print(F("\", then browse to http://"));
    Serial.println(WiFi.softAPIP());

    // --- WebSocket ---
    ws_.onEvent([this](AsyncWebSocket *server, AsyncWebSocketClient *client,
                        AwsEventType type, void *arg, uint8_t *data, size_t len) {
        handleWebSocketEvent(server, client, type, arg, data, len);
    });
    server_.addHandler(&ws_);

    // --- Static site from LittleFS ---
    // serveStatic handles index.html/style.css/app.js and any future
    // assets automatically, with a default index of index.html at "/".
    server_.serveStatic("/", LittleFS, "/").setDefaultFile("index.html");

    // A tiny JSON status endpoint — handy for curl-based debugging without
    // needing to open a WebSocket by hand.
    server_.on("/status", HTTP_GET, [](AsyncWebServerRequest *request) {
        String json = "{\"clients\":";
        json += request->client() ? "1" : "0";
        json += "}";
        request->send(200, "application/json", json);
    });

    server_.onNotFound([](AsyncWebServerRequest *request) {
        request->send(404, "text/plain", "Not found");
    });

    server_.begin();
    return true;
}

void PenWiFiServer::handleWebSocketEvent(AsyncWebSocket *server, AsyncWebSocketClient *client,
                                          AwsEventType type, void *arg, uint8_t *data, size_t len) {
    switch (type) {
        case WS_EVT_CONNECT:
            Serial.printf("[WiFiServer] Client #%u connected from %s\n",
                          client->id(), client->remoteIP().toString().c_str());
            break;

        case WS_EVT_DISCONNECT:
            Serial.printf("[WiFiServer] Client #%u disconnected\n", client->id());
            break;

        case WS_EVT_DATA: {
            // We don't require any inbound protocol from the browser for
            // normal operation, but we do accept a couple of simple text
            // commands sent from the UI (e.g. a manual "ping" for latency
            // measurement, echoed straight back).
            AwsFrameInfo *info = static_cast<AwsFrameInfo *>(arg);
            if (info->final && info->index == 0 && info->len == len &&
                info->opcode == WS_TEXT) {
                String msg(reinterpret_cast<char *>(data), len);
                if (msg == "ping") {
                    client->text("pong");
                } else if (msg == "reset") {
                    if (resetCallback_) resetCallback_();
                    Serial.println(F("[WiFiServer] Reset requested by client."));
                }
            }
            break;
        }

        case WS_EVT_ERROR:
            Serial.printf("[WiFiServer] Client #%u WebSocket error\n", client->id());
            break;

        case WS_EVT_PONG:
        default:
            break;
    }
}

void PenWiFiServer::broadcastFrame(const TrackerFrame &frame) {
    if (ws_.count() == 0) return; // nobody listening — skip the work entirely

    // Compact JSON packet. We deliberately keep this human-readable JSON
    // (rather than a binary struct) for now, per the spec's note that JSON
    // is fine to start with — the field set below is intentionally small
    // so it stays cheap to parse in the browser even at 60Hz.
    char buf[192];
    int n = snprintf(buf, sizeof(buf),
        "{\"x\":%.2f,\"y\":%.2f,\"pen\":%u,\"vx\":%.3f,\"vy\":%.3f,"
        "\"stationary\":%u,\"dt\":%lu}",
        frame.canvasX, frame.canvasY, frame.penDown,
        frame.velX, frame.velY,
        frame.stationary ? 1 : 0,
        static_cast<unsigned long>(frame.sampleIntervalUs));

    if (n > 0 && n < static_cast<int>(sizeof(buf))) {
        ws_.textAll(buf, n);
    }

    // Periodically clean up any WebSocket clients that disconnected
    // without a clean close handshake (e.g. phone locked mid-session) —
    // cheap to call, AsyncWebSocket no-ops if there's nothing to clean.
    ws_.cleanupClients();
}

size_t PenWiFiServer::clientCount() const {
    return ws_.count();
}
