#include "esp_camera.h"
#include <WiFi.h>
#include <WebServer.h>

// 📡 Access Point credentials
const char* ap_ssid = "ESP32-CAM";
const char* ap_pass = "12345678"; // min 8 chars

WebServer server(80);

// 📷 XIAO ESP32S3 Sense camera pins (OV2640)
#define PWDN_GPIO_NUM     -1
#define RESET_GPIO_NUM    -1
#define XCLK_GPIO_NUM     10
#define SIOD_GPIO_NUM     40
#define SIOC_GPIO_NUM     39

#define Y9_GPIO_NUM       48
#define Y8_GPIO_NUM       11
#define Y7_GPIO_NUM       12
#define Y6_GPIO_NUM       14
#define Y5_GPIO_NUM       16
#define Y4_GPIO_NUM       18
#define Y3_GPIO_NUM       17
#define Y2_GPIO_NUM       15
#define VSYNC_GPIO_NUM    38
#define HREF_GPIO_NUM     47
#define PCLK_GPIO_NUM     13

// 🧠 Init camera
bool init_camera() {
    camera_config_t config;

    config.ledc_channel = LEDC_CHANNEL_0;
    config.ledc_timer = LEDC_TIMER_0;
    config.pin_d0 = Y2_GPIO_NUM;
    config.pin_d1 = Y3_GPIO_NUM;
    config.pin_d2 = Y4_GPIO_NUM;
    config.pin_d3 = Y5_GPIO_NUM;
    config.pin_d4 = Y6_GPIO_NUM;
    config.pin_d5 = Y7_GPIO_NUM;
    config.pin_d6 = Y8_GPIO_NUM;
    config.pin_d7 = Y9_GPIO_NUM;
    config.pin_xclk = XCLK_GPIO_NUM;
    config.pin_pclk = PCLK_GPIO_NUM;
    config.pin_vsync = VSYNC_GPIO_NUM;
    config.pin_href = HREF_GPIO_NUM;
    config.pin_sscb_sda = SIOD_GPIO_NUM;
    config.pin_sscb_scl = SIOC_GPIO_NUM;
    config.pin_pwdn = PWDN_GPIO_NUM;
    config.pin_reset = RESET_GPIO_NUM;

    config.xclk_freq_hz = 20000000;
    config.pixel_format = PIXFORMAT_JPEG;

    if (psramFound()) {
        Serial.println("✅ PSRAM detected");
        config.frame_size = FRAMESIZE_VGA;
        config.jpeg_quality = 12;
        config.fb_count = 2;
    } else {
        Serial.println("⚠️ No PSRAM");
        config.frame_size = FRAMESIZE_QVGA;
        config.jpeg_quality = 16;
        config.fb_count = 1;
    }

    esp_err_t err = esp_camera_init(&config);
    if (err != ESP_OK) {
        Serial.printf("❌ Camera init failed: 0x%x\n", err);
        return false;
    }

    Serial.println("✅ Camera initialized");
    return true;
}

// 📷 Stream handler (MJPEG)
void handle_stream() {
    WiFiClient client = server.client();

    String response = 
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: multipart/x-mixed-replace; boundary=frame\r\n\r\n";
    server.sendContent(response);

    while (client.connected()) {
        camera_fb_t * fb = esp_camera_fb_get();
        if (!fb) {
            Serial.println("Capture failed");
            continue;
        }

        server.sendContent("--frame\r\n");
        server.sendContent("Content-Type: image/jpeg\r\n\r\n");
        client.write(fb->buf, fb->len);
        server.sendContent("\r\n");

        esp_camera_fb_return(fb);

        delay(50); // adjust FPS (lower = faster, but heavier)
    }
}

// 🌐 Simple web page
void handle_root() {
    server.send(200, "text/html",
        "<html><body>"
        "<h2>ESP32-S3 Camera Stream</h2>"
        "<img src='/stream' />"
        "</body></html>");
}

void setup() {
    Serial.begin(115200);
    delay(1000);

    Serial.println("\n===== ESP32-S3 AP CAMERA =====");

    // 📷 Init camera
    if (!init_camera()) {
        Serial.println("⛔ Camera failed");
        return;
    }

    // 📡 Start Access Point
    WiFi.mode(WIFI_AP);

    if (!WiFi.softAP(ap_ssid, ap_pass)) {
        Serial.println("❌ AP start failed");
        return;
    }

    Serial.println("✅ Access Point started");
    Serial.print("📡 SSID: ");
    Serial.println(ap_ssid);
    Serial.print("🌐 IP: ");
    Serial.println(WiFi.softAPIP()); // usually 192.168.4.1

    // 🌍 Start web server
    server.on("/", handle_root);
    server.on("/stream", HTTP_GET, handle_stream);

    server.begin();
    Serial.println("🚀 Server started");
}

void loop() {
    server.handleClient();
}