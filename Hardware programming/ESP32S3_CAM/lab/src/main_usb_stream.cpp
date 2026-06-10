#include "esp_camera.h"
#include <Arduino.h>

// XIAO ESP32S3 Sense camera pins (OV2640)
#define PWDN_GPIO_NUM  -1
#define RESET_GPIO_NUM -1
#define XCLK_GPIO_NUM  10
#define SIOD_GPIO_NUM  40
#define SIOC_GPIO_NUM  39

#define Y9_GPIO_NUM 48
#define Y8_GPIO_NUM 11
#define Y7_GPIO_NUM 12
#define Y6_GPIO_NUM 14
#define Y5_GPIO_NUM 16
#define Y4_GPIO_NUM 18
#define Y3_GPIO_NUM 17
#define Y2_GPIO_NUM 15
#define VSYNC_GPIO_NUM 38
#define HREF_GPIO_NUM  47
#define PCLK_GPIO_NUM  13

static const uint8_t FRAME_MAGIC[2] = {0xCA, 0xFE};

static framesize_t current_framesize = FRAMESIZE_VGA;
static int jpeg_quality = 12;
static uint32_t frame_delay_ms = 50;
static bool streaming = false;

static const char *framesize_name(framesize_t size) {
    switch (size) {
    case FRAMESIZE_QQVGA: return "qqvga";
    case FRAMESIZE_QCIF: return "qcif";
    case FRAMESIZE_HQVGA: return "hqvga";
    case FRAMESIZE_240X240: return "240x240";
    case FRAMESIZE_QVGA: return "qvga";
    case FRAMESIZE_CIF: return "cif";
    case FRAMESIZE_HVGA: return "hvga";
    case FRAMESIZE_VGA: return "vga";
    case FRAMESIZE_SVGA: return "svga";
    case FRAMESIZE_XGA: return "xga";
    case FRAMESIZE_HD: return "hd";
    case FRAMESIZE_SXGA: return "sxga";
    case FRAMESIZE_UXGA: return "uxga";
    default: return "unknown";
    }
}

static bool parse_framesize(const String &name, framesize_t *out) {
    if (name.equalsIgnoreCase("qqvga") || name == "0") {
        *out = FRAMESIZE_QQVGA;
        return true;
    }
    if (name.equalsIgnoreCase("qcif") || name == "1") {
        *out = FRAMESIZE_QCIF;
        return true;
    }
    if (name.equalsIgnoreCase("hqvga") || name == "2") {
        *out = FRAMESIZE_HQVGA;
        return true;
    }
    if (name.equalsIgnoreCase("240x240") || name == "3") {
        *out = FRAMESIZE_240X240;
        return true;
    }
    if (name.equalsIgnoreCase("qvga") || name == "4") {
        *out = FRAMESIZE_QVGA;
        return true;
    }
    if (name.equalsIgnoreCase("cif") || name == "5") {
        *out = FRAMESIZE_CIF;
        return true;
    }
    if (name.equalsIgnoreCase("hvga") || name == "6") {
        *out = FRAMESIZE_HVGA;
        return true;
    }
    if (name.equalsIgnoreCase("vga") || name == "7") {
        *out = FRAMESIZE_VGA;
        return true;
    }
    if (name.equalsIgnoreCase("svga") || name == "8") {
        *out = FRAMESIZE_SVGA;
        return true;
    }
    if (name.equalsIgnoreCase("xga") || name == "9") {
        *out = FRAMESIZE_XGA;
        return true;
    }
    if (name.equalsIgnoreCase("hd") || name == "10") {
        *out = FRAMESIZE_HD;
        return true;
    }
    if (name.equalsIgnoreCase("sxga") || name == "11") {
        *out = FRAMESIZE_SXGA;
        return true;
    }
    if (name.equalsIgnoreCase("uxga") || name == "12") {
        *out = FRAMESIZE_UXGA;
        return true;
    }
    return false;
}

static bool init_camera() {
    camera_config_t config = {};

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
    config.pin_sccb_sda = SIOD_GPIO_NUM;
    config.pin_sccb_scl = SIOC_GPIO_NUM;
    config.pin_pwdn = PWDN_GPIO_NUM;
    config.pin_reset = RESET_GPIO_NUM;

    config.xclk_freq_hz = 20000000;
    config.pixel_format = PIXFORMAT_JPEG;

    if (psramFound()) {
        config.frame_size = FRAMESIZE_VGA;
        config.jpeg_quality = jpeg_quality;
        config.fb_count = 2;
        config.grab_mode = CAMERA_GRAB_LATEST;
    } else {
        config.frame_size = FRAMESIZE_QVGA;
        config.jpeg_quality = 16;
        config.fb_count = 1;
        config.grab_mode = CAMERA_GRAB_WHEN_EMPTY;
    }

    current_framesize = config.frame_size;

    esp_err_t err = esp_camera_init(&config);
    if (err != ESP_OK) {
        Serial.printf("ERR camera init 0x%x\n", err);
        return false;
    }

    sensor_t *sensor = esp_camera_sensor_get();
    if (sensor) {
        sensor->set_framesize(sensor, current_framesize);
        sensor->set_quality(sensor, jpeg_quality);
    }

    return true;
}

static bool apply_framesize(framesize_t size) {
    sensor_t *sensor = esp_camera_sensor_get();
    if (!sensor) {
        Serial.println("ERR no sensor");
        return false;
    }

    if (sensor->set_framesize(sensor, size) != 0) {
        Serial.println("ERR set_framesize failed");
        return false;
    }

    current_framesize = size;
    Serial.printf("OK res %s\n", framesize_name(size));
    return true;
}

static bool apply_quality(int quality) {
    quality = constrain(quality, 4, 63);
    sensor_t *sensor = esp_camera_sensor_get();
    if (!sensor) {
        Serial.println("ERR no sensor");
        return false;
    }

    if (sensor->set_quality(sensor, quality) != 0) {
        Serial.println("ERR set_quality failed");
        return false;
    }

    jpeg_quality = quality;
    Serial.printf("OK quality %d\n", jpeg_quality);
    return true;
}

static void print_help() {
    Serial.println("CMD help");
    Serial.println("CMD res <qqvga|qvga|vga|svga|xga|hd|sxga|uxga|0-12>");
    Serial.println("CMD quality <4-63>");
    Serial.println("CMD fps <delay_ms>");
    Serial.println("CMD start");
    Serial.println("CMD stop");
    Serial.println("CMD status");
}

static void handle_command(const String &line) {
    String cmd = line;
    cmd.trim();
    if (cmd.length() == 0) {
        return;
    }

    int space = cmd.indexOf(' ');
    String verb = (space < 0) ? cmd : cmd.substring(0, space);
    String arg = (space < 0) ? "" : cmd.substring(space + 1);
    verb.toLowerCase();

    if (verb == "help" || verb == "?") {
        print_help();
        return;
    }

    if (verb == "res" || verb == "r") {
        framesize_t size;
        if (!parse_framesize(arg, &size)) {
            Serial.println("ERR unknown resolution");
            return;
        }
        apply_framesize(size);
        return;
    }

    if (verb == "quality" || verb == "q") {
        apply_quality(arg.toInt());
        return;
    }

    if (verb == "fps") {
        frame_delay_ms = (uint32_t)max(0, (int)arg.toInt());
        Serial.printf("OK fps delay %lu ms\n", (unsigned long)frame_delay_ms);
        return;
    }

    if (verb == "start") {
        streaming = true;
        Serial.println("OK stream start");
        return;
    }

    if (verb == "stop") {
        streaming = false;
        Serial.println("OK stream stop");
        return;
    }

    if (verb == "status") {
        Serial.printf("OK status res=%s quality=%d delay=%lu streaming=%d\n",
                      framesize_name(current_framesize),
                      jpeg_quality,
                      (unsigned long)frame_delay_ms,
                      streaming ? 1 : 0);
        return;
    }

    Serial.println("ERR unknown command (type help)");
}

static void poll_commands() {
    static String line;

    while (Serial.available() > 0) {
        char c = Serial.read();
        if (c == '\r') {
            continue;
        }
        if (c == '\n') {
            handle_command(line);
            line = "";
            continue;
        }
        if (line.length() < 96) {
            line += c;
        }
    }
}

static bool write_all(const uint8_t *data, size_t len) {
    size_t sent = 0;
    while (sent < len) {
        size_t chunk = Serial.write(data + sent, len - sent);
        if (chunk == 0) {
            delay(1);
            continue;
        }
        sent += chunk;
    }
    return true;
}

static bool send_frame(const camera_fb_t *fb) {
    uint8_t header[12];
    header[0] = FRAME_MAGIC[0];
    header[1] = FRAME_MAGIC[1];
    header[2] = (uint8_t)(fb->len);
    header[3] = (uint8_t)(fb->len >> 8);
    header[4] = (uint8_t)(fb->len >> 16);
    header[5] = (uint8_t)(fb->len >> 24);
    header[6] = (uint8_t)(fb->width);
    header[7] = (uint8_t)(fb->width >> 8);
    header[8] = (uint8_t)(fb->height);
    header[9] = (uint8_t)(fb->height >> 8);
    header[10] = 0;
    header[11] = 0;

    if (!write_all(header, sizeof(header))) {
        return false;
    }
    if (!write_all(fb->buf, fb->len)) {
        return false;
    }
    return true;
}

void setup() {
    Serial.begin(2000000);
    delay(500);

    Serial.println("\n===== ESP32-S3 USB CAMERA =====");

    if (!init_camera()) {
        Serial.println("ERR camera failed");
        return;
    }

    Serial.printf("OK camera %s PSRAM=%d\n",
                  framesize_name(current_framesize),
                  psramFound() ? 1 : 0);
    Serial.println("OK usb stream ready");
    Serial.println("OK waiting for start");
    print_help();
}

void loop() {
    poll_commands();

    if (!streaming) {
        delay(10);
        return;
    }

    camera_fb_t *fb = esp_camera_fb_get();
    if (!fb) {
        Serial.println("ERR capture failed");
        delay(100);
        return;
    }

    if (!send_frame(fb)) {
        esp_camera_fb_return(fb);
        Serial.println("ERR usb write failed");
        delay(100);
        return;
    }

    esp_camera_fb_return(fb);

    if (frame_delay_ms > 0) {
        delay(frame_delay_ms);
    }
}
