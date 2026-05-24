/*
 * Smart Pen — Seeed XIAO ESP32-S3 Sense
 *
 * - Power: physical switch on battery (not in firmware)
 * - Pressure foil on A1 (GPIO2): writing = above threshold
 * - Capture every 10 s while session active → /sess/f_NNNN.jpg
 * - 30 s idle → burst 5 JPEGs @ 5 Hz, still same session
 * - Still idle 10 s → merge session → one PDF in /photos/, then deep sleep
 * - Wake: D7 (GPIO44) button
 * - Hold D7 3 s → WiFi AP, list/download PDFs, GET /stop to exit
 *
 * SD (Sense expansion): CS=21, SCK=7, MISO=8, MOSI=9
*/

#include <Arduino.h>
#include "esp_camera.h"
#include "esp_sleep.h"
#include "driver/rtc_io.h"
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <AsyncTCP.h>
#include <SPI.h>
#include <SD.h>
#include <vector>
#include <algorithm>

// ─── Pins (XIAO ESP32-S3 Sense) ───────────────────────────────────────────
#define BUTTON_PIN   D6 // D6 — RTC wake + 3 s hold for WiFi
// #define PRESSURE_PIN D8 // D8 — foil paper as touch pad

#define SD_CS_PIN 21
#define SD_SCK_PIN 7
#define SD_MISO_PIN 8
#define SD_MOSI_PIN 9
 
// ─── Timing ───────────────────────────────────────────────────────────────
#define CAPTURE_INTERVAL_MS 10000
#define INACTIVITY_MS 30000
#define POST_BURST_SLEEP_MS 10000
#define BURST_COUNT 5
#define BURST_INTERVAL_MS 1000
#define WAKE_HOLD_MS 3000

#define AP_SSID "SmartPen"
#define AP_PASS "smartpen123"

#define SESS_DIR "/sess"
#define PHOTOS_DIR "/photos"

// ─── Camera (OV2640 on Sense) ─────────────────────────────────────────────
#define PWDN_GPIO_NUM -1
#define RESET_GPIO_NUM -1
#define XCLK_GPIO_NUM 10
#define SIOD_GPIO_NUM 40
#define SIOC_GPIO_NUM 39
#define Y9_GPIO_NUM 48
#define Y8_GPIO_NUM 11
#define Y7_GPIO_NUM 12
#define Y6_GPIO_NUM 14
#define Y5_GPIO_NUM 16
#define Y4_GPIO_NUM 18
#define Y3_GPIO_NUM 17
#define Y2_GPIO_NUM 15
#define VSYNC_GPIO_NUM 38
#define HREF_GPIO_NUM 47
#define PCLK_GPIO_NUM 13

// ─── State ────────────────────────────────────────────────────────────────
enum AppState {
    STATE_ACTIVE,
    STATE_BURST_DONE,
    STATE_WIFI
};

AsyncWebServer server(80);

unsigned long lastActivityMs = 0;
unsigned long lastCaptureMs = 0;
unsigned long burstDoneAtMs = 0;
bool burstDone = false;
bool stopWifiRequested = false;
uint16_t frameCounter = 0;
uint16_t imgWidth = 800;
uint16_t imgHeight = 600;

unsigned long wakeBtnDownMs = 0;
bool wakeBtnWasDown = false;

// ─── Forward ──────────────────────────────────────────────────────────────
bool initCamera();
bool initSD();
bool isWriting();
bool captureJpegFrame();
bool mergeSessionToPdf(char *outPath, size_t outPathLen);
void clearSessionDir();
void startWiFiPortal();
void enterDeepSleep();
String nextPdfName();
void nextPdfName(char *buf, size_t len);

// ═══════════════════════════════════════════════════════════════════════════
//  Multi-page PDF: embed multiple JPEGs (DCTDecode), one page each
// ═══════════════════════════════════════════════════════════════════════════
bool writePdfHeader(File &out){
    return out.print("%PDF-1.4\n") > 0;
}

bool writePdfCatalogAndPages(File &out, int numPages, const std::vector<int> &pageObjNums){
    if (!out.print("1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n"))
        return false;
    if (!out.print("2 0 obj\n<< /Type /Pages /Kids ["))
        return false;
    for (int i = 0; i < numPages; i++)
    {
        char buf[24];
        snprintf(buf, sizeof(buf), "%d 0 R ", pageObjNums[i]);
        out.print(buf);
    }
    out.printf("] /Count %d >>\nendobj\n", numPages);
    return true;
}

bool writePdfPageWithJpeg(File &out, int pageObj, int contentObj, int imageObj, const uint8_t *jpeg, size_t jpegLen, uint16_t w, uint16_t h){
    float scaleW = 595.0f / w;
    float scaleH = 842.0f / h;
    float scale = (scaleW < scaleH) ? scaleW : scaleH;
    int pw = (int)(w * scale);
    int ph = (int)(h * scale);
    int ox = (595 - pw) / 2;
    int oy = (842 - ph) / 2;

    char stream[96];
    int slen = snprintf(stream, sizeof(stream),
                        "q %d 0 0 %d %d %d cm /Im1 Do Q\n", pw, ph, ox, oy);

    out.printf("%d 0 obj\n<< /Type /Page /Parent 2 0 R\n", pageObj);
    out.printf("   /MediaBox [0 0 595 842]\n");
    out.printf("   /Contents %d 0 R\n", contentObj);
    out.printf("   /Resources << /XObject << /Im1 %d 0 R >> >>\n", imageObj);
    out.printf(">>\nendobj\n");

    out.printf("%d 0 obj\n<< /Length %d >>\nstream\n", contentObj, slen);
    out.write((uint8_t *)stream, slen);
    out.print("endstream\nendobj\n");

    out.printf("%d 0 obj\n<< /Type /XObject /Subtype /Image\n", imageObj);
    out.printf("   /Width %u /Height %u\n", w, h);
    out.printf("   /ColorSpace /DeviceRGB\n");
    out.printf("   /BitsPerComponent 8\n");
    out.printf("   /Filter /DCTDecode\n");
    out.printf("   /Length %u\n", (unsigned)jpegLen);
    out.printf(">>\nstream\n");
    out.write(jpeg, jpegLen);
    out.print("\nendstream\nendobj\n");
    return true;
}

bool mergeSessionToPdf(char *outPath, size_t outPathLen){
    std::vector<String> frames;
    File root = SD.open(SESS_DIR);
    if (!root || !root.isDirectory())
    {
        Serial.println("[PDF] No session folder");
        return false;
    }
    File f = root.openNextFile();
    while (f)
    {
        if (!f.isDirectory())
        {
            String n = f.name();
            if (n.endsWith(".jpg") || n.endsWith(".jpeg"))
            {
                frames.push_back(String(SESS_DIR) + "/" + n);
            }
        }
        f.close();
        f = root.openNextFile();
    }
    root.close();

    if (frames.empty())
    {
        Serial.println("[PDF] No frames to merge");
        return false;
    }
    std::sort(frames.begin(), frames.end());

    int n = frames.size();
    std::vector<int> pageObjNums(n);
    int nextObj = 3;
    for (int i = 0; i < n; i++)
    {
        pageObjNums[i] = nextObj;
        nextObj += 3;
    }
    int totalObjs = 2 + n * 3;

    nextPdfName(outPath, outPathLen);
    File out = SD.open(outPath, FILE_WRITE);
    if (!out)
    {
        Serial.println("[PDF] Cannot create output");
        return false;
    }

    std::vector<int> xref(totalObjs + 1, 0);
    writePdfHeader(out);
    xref[1] = out.position();
    writePdfCatalogAndPages(out, n, pageObjNums);

    for (int i = 0; i < n; i++)
    {
        File jf = SD.open(frames[i], FILE_READ);
        if (!jf)
            continue;
        size_t len = jf.size();
        uint8_t *buf = (uint8_t *)malloc(len);
        if (!buf)
        {
            jf.close();
            continue;
        }
        jf.read(buf, len);
        jf.close();

        int pageObj = pageObjNums[i];
        int contentObj = pageObj + 1;
        int imageObj = pageObj + 2;

        xref[pageObj] = out.position();
        writePdfPageWithJpeg(out, pageObj, contentObj, imageObj,
                             buf, len, imgWidth, imgHeight);
        free(buf);
    }

    int xrefPos = out.position();
    out.print("xref\n");
    out.printf("0 %d\n", totalObjs + 1);
    out.print("0000000000 65535 f \n");
    for (int i = 1; i <= totalObjs; i++)
    {
        char line[32];
        snprintf(line, sizeof(line), "%010d 00000 n \n", xref[i]);
        out.print(line);
    }
    out.printf("trailer\n<< /Size %d /Root 1 0 R >>\nstartxref\n%d\n%%%%EOF\n",
               totalObjs + 1, xrefPos);
    out.close();

    Serial.printf("[PDF] Wrote %s (%d pages)\n", outPath, n);
    return true;
}

// ═══════════════════════════════════════════════════════════════════════════
String nextPdfName(){
    char name[48];
    uint32_t t = millis();
    snprintf(name, sizeof(name), PHOTOS_DIR "/note_%lu.pdf", (unsigned long)t);
    return String(name);
}

void nextPdfName(char *buf, size_t len){
    uint32_t sec = millis() / 1000;
    snprintf(buf, len, PHOTOS_DIR "/note_%lu.pdf", (unsigned long)sec);
}

// ═══════════════════════════════════════════════════════════════════════════
bool initSD(){
    SPI.begin(SD_SCK_PIN, SD_MISO_PIN, SD_MOSI_PIN, SD_CS_PIN);
    if(!SD.begin(SD_CS_PIN, SPI, 8000000)){
        Serial.println("[SD] Mount failed");
        return false;
    }
    
    if(!SD.exists(PHOTOS_DIR))
        SD.mkdir(PHOTOS_DIR);
    
    if(!SD.exists(SESS_DIR))
        SD.mkdir(SESS_DIR);
    
    Serial.println("[SD] OK");
    return true;
}

void clearSessionDir(){
    File root = SD.open(SESS_DIR);
    if (!root || !root.isDirectory())
        return;
    File f = root.openNextFile();
    while(f){
        if(!f.isDirectory()){
            String p = String(SESS_DIR) + "/" + f.name();
            SD.remove(p.c_str());
        }
        f.close();
        f = root.openNextFile();
    }
    root.close();
    frameCounter = 0;
}

bool initCamera(){
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
    config.grab_mode = CAMERA_GRAB_LATEST;

    if(psramFound()){
        config.frame_size = FRAMESIZE_SVGA; // 800x600
        config.jpeg_quality = 12;
        config.fb_count = 2;
    }else{
        config.frame_size = FRAMESIZE_VGA;
        config.jpeg_quality = 14;
        config.fb_count = 1;
    }

    esp_err_t err = esp_camera_init(&config);
    if(err != ESP_OK){
        Serial.printf("[CAM] Init failed 0x%x\n", err);
        return false;
    }
    sensor_t *s = esp_camera_sensor_get();
    if(s){
        s->set_vflip(s, 0);
        s->set_hmirror(s, 0);
    }
    Serial.println("[CAM] OK");
    return true;
}

bool isWriting(){
    // static bool active = false;
    // int v = touchRead(PRESSURE_PIN) > 30000;
    // if(!active && v == 1)
    //     active = true;
    // return active;
    return 1;
}

bool captureJpegFrame(){
    camera_fb_t *fb = esp_camera_fb_get();
    if(!fb){
        Serial.println("[CAM] Capture failed");
        return false;
    }
    imgWidth = fb->width;
    imgHeight = fb->height;

    frameCounter++;
    char path[48];
    snprintf(path, sizeof(path), SESS_DIR "/f_%04u.jpg", frameCounter);

    File out = SD.open(path, FILE_WRITE);
    if(!out){
        esp_camera_fb_return(fb);
        Serial.println("[SD] Frame write failed");
        return false;
    }
    out.write(fb->buf, fb->len);
    out.close();
    esp_camera_fb_return(fb);
    Serial.printf("[CAP] %s (%ux%u)\n", path, imgWidth, imgHeight);
    return true;
}

void runBurst(){
    Serial.println("[CAP] 30s idle → burst");
    for (int i = 0; i < BURST_COUNT; i++){
        captureJpegFrame();
        delay(BURST_INTERVAL_MS);
    }
    burstDone = true;
    burstDoneAtMs = millis();
}

void endSessionAndSleep(int wannaSleep){
    char pdfPath[64];
    if(frameCounter > 0){
        if(mergeSessionToPdf(pdfPath, sizeof(pdfPath)))
            clearSessionDir();
        else
            Serial.println("[PDF] Merge failed — JPEGs kept in /sess");
    }else
        Serial.println("[PWR] No frames, sleep without PDF");
    if(wannaSleep)
        enterDeepSleep();
}

void enterDeepSleep(){
    Serial.println("[PWR] Deep sleep — press D7 to wake");
    Serial.flush();
    esp_camera_deinit();
    SD.end();

    pinMode(BUTTON_PIN, INPUT_PULLUP);
    esp_sleep_enable_ext0_wakeup((gpio_num_t)BUTTON_PIN, 0);
    esp_deep_sleep_start();
}

void startWiFiPortal(){
    endSessionAndSleep(0);
    stopWifiRequested = false;
    WiFi.mode(WIFI_AP);
    WiFi.softAP(AP_SSID, AP_PASS);
    Serial.printf("[WiFi] %s → http://%s\n", AP_SSID, WiFi.softAPIP().toString().c_str());

    server.on("/", HTTP_GET, [](AsyncWebServerRequest *req)
              {
    String html = R"raw(<!DOCTYPE html><html><head>
<meta name='viewport' content='width=device-width,initial-scale=1'>
<title>SmartPen</title>
<style>
body{font-family:sans-serif;background:#111;color:#eee;padding:20px}
h1{color:#4fc3f7}a{color:#80cbc4;display:block;margin:8px 0}
button{background:#e53935;color:#fff;border:none;padding:12px 20px;
border-radius:8px;font-size:1em;margin-top:16px;cursor:pointer}
</style></head><body><h1>SmartPen PDFs</h1>)raw";

    File dir = SD.open(PHOTOS_DIR);
    if (dir && dir.isDirectory()) {
      File f = dir.openNextFile();
      while (f) {
        if (!f.isDirectory()) {
          String name = f.name();
          html += "<a href='/dl?f=" + name + "'>📄 " + name + "</a>";
        }
        f.close();
        f = dir.openNextFile();
      }
      dir.close();
    }
    html += R"raw(<button onclick="fetch('/stop').then(()=>alert('Stopping WiFi'))">
Stop WiFi</button></body></html>)raw";
    req->send(200, "text/html", html); });

    server.on("/dl", HTTP_GET, [](AsyncWebServerRequest *req)
              {
    if (!req->hasParam("f")) { req->send(400); return; }
    String path = String(PHOTOS_DIR) + "/" + req->getParam("f")->value();
    if (!SD.exists(path)) { req->send(404); return; }
    req->send(SD, path, "application/pdf", true); });

    server.on("/stop", HTTP_GET, [](AsyncWebServerRequest *req)
              {
    stopWifiRequested = true;
    req->send(200, "text/plain", "OK"); });

    server.begin();

    while (!stopWifiRequested)
    {
        delay(50);
        if (digitalRead(BUTTON_PIN) == LOW)
        {
            unsigned long t0 = millis();
            while (digitalRead(BUTTON_PIN) == LOW && millis() - t0 < 800)
                delay(10);
            if (millis() - t0 >= 800)
                stopWifiRequested = true;
        }
    }

    server.end();
    WiFi.softAPdisconnect(true);
    WiFi.mode(WIFI_OFF);
    Serial.println("[WiFi] Stopped");
}

// ═══════════════════════════════════════════════════════════════════════════
void setup(){
    delay(3000);
    Serial.begin(115200);
    Serial.println("\n=== Smart Pen (XIAO ESP32-S3 Sense) ===");

    pinMode(BUTTON_PIN, INPUT_PULLUP);

    if(!initSD())
        while(true)
            delay(1000);
    
    if(!initCamera())
        while(true)
            delay(1000);

    if(esp_sleep_get_wakeup_cause() == ESP_SLEEP_WAKEUP_EXT0){
        Serial.println("[PWR] Woke from deep sleep");
        clearSessionDir();
    }else{
        Serial.println("[PWR] Cold boot");
        clearSessionDir();
    }

    lastActivityMs = millis();
    lastCaptureMs = 0;
    burstDone = false;
}

void loop(){
    unsigned long now = millis();

    // ── D7 held 3 s → WiFi (non-blocking check) ─────────────────────────────
    if(digitalRead(BUTTON_PIN) == LOW){
        if(!wakeBtnWasDown){
            wakeBtnWasDown = true;
            wakeBtnDownMs = now;
        }else if(now - wakeBtnDownMs >= WAKE_HOLD_MS){
            Serial.println("[BTN] 3s → WiFi");
            while(digitalRead(BUTTON_PIN) == LOW)
                delay(10);
            wakeBtnWasDown = false;
            startWiFiPortal();
            lastActivityMs = millis();
            lastCaptureMs = 0;
            burstDone = false;
            return;
        }
    }else
        wakeBtnWasDown = false;

    // ── Activity (pressure foil) ────────────────────────────────────────────
    if(isWriting()){
        lastActivityMs = now;
        burstDone = false;
    }

    unsigned long idle = now - lastActivityMs;

    // ── Active: capture every 10 s ─────────────────────────────────────────
    if(idle < INACTIVITY_MS){
        if(now - lastCaptureMs >= CAPTURE_INTERVAL_MS){
            captureJpegFrame();
            lastCaptureMs = now;
        }
        return;
    }

    // ── 30 s idle: burst once ───────────────────────────────────────────────
    if(!burstDone){
        runBurst();
        return;
    }

    // ── Still idle after burst → merge PDF + sleep ──────────────────────────
    if(now - burstDoneAtMs >= POST_BURST_SLEEP_MS){
        endSessionAndSleep(1);
    }

    delay(20);
}