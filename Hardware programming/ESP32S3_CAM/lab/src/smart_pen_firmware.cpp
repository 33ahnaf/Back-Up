/*
 * ============================================================
 *  SMART PEN PROTOTYPE FIRMWARE
 *  Platform : ESP32-CAM (AI Thinker)
 *  Features :
 *    - Power on via slide switch
 *    - Periodic photo capture → SD card as PDF
 *    - 30s inactivity → burst capture (5 photos/sec)
 *    - Extended inactivity → deep sleep
 *    - Wake from deep sleep via dedicated WAKE button
 *    - 3s hold on WAKE button → WiFi AP mode
 *    - AP mode: browse & download files from web UI
 *    - Stop WiFi via web command
 * ============================================================
 *
 *  HARDWARE WIRING
 *  ───────────────
 *  ESP32-CAM (AI Thinker module)
 *
 *  WAKE/MULTI-FUNCTION BUTTON  → GPIO 13  (INPUT_PULLUP, active LOW)
 *                                Also connected to RTC GPIO for wake-from-sleep
 *  MOTION / WRITING SENSOR     → GPIO 14  (INPUT_PULLUP, active LOW)
 *                                e.g. Reed switch on pen tip, IMU interrupt,
 *                                or IR-break beam under nib
 *  SD CARD                     → Built-in SPI on AI-Thinker board
 *                                (GPIO 2/4/12/13 — standard for AI-Thinker)
 *  CAMERA                      → Built-in OV2640 on AI-Thinker
 *  POWER LED (optional)        → GPIO 33 (onboard LED, active LOW)
 *
 *  POWER PATH
 *  ──────────
 *  Battery (+) → Slide Switch → VCC pin of ESP32-CAM
 *  Battery (−) → GND
 *  (Switch simply cuts power rail; deep sleep keeps μA quiescent current
 *   until WAKE button pulls GPIO 13 LOW which is wired to EXT0 wakeup)
 *
 *  DEPENDENCIES (install via Arduino Library Manager)
 *  ──────────────────────────────────────────────────
 *  - ESP32 Arduino core (≥ 2.0)
 *  - "ESP32 PDF" / custom PDF writer (included inline below as PDFWriter)
 *  - ESPAsyncWebServer  (me-no-dev)
 *  - AsyncTCP           (me-no-dev)
 * ============================================================
 */


/*
#include "esp_camera.h"
#include "esp_sleep.h"
#include "driver/rtc_io.h"
#include "FS.h"
#include "SD_MMC.h"
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <AsyncTCP.h>

// ─── PIN DEFINITIONS ─────────────────────────────────────────
#define WAKE_BTN_PIN      13   // RTC-capable GPIO
#define ACTIVITY_PIN      14   // Pen-tip sensor (active LOW)
#define LED_PIN           33   // Onboard LED (active LOW)

// ─── AI-THINKER CAMERA PINS ──────────────────────────────────
#define PWDN_GPIO_NUM     32
#define RESET_GPIO_NUM    -1
#define XCLK_GPIO_NUM      0
#define SIOD_GPIO_NUM     26
#define SIOC_GPIO_NUM     27
#define Y9_GPIO_NUM       35
#define Y8_GPIO_NUM       34
#define Y7_GPIO_NUM       39
#define Y6_GPIO_NUM       36
#define Y5_GPIO_NUM       21
#define Y4_GPIO_NUM       19
#define Y3_GPIO_NUM       18
#define Y2_GPIO_NUM        5
#define VSYNC_GPIO_NUM    25
#define HREF_GPIO_NUM     23
#define PCLK_GPIO_NUM     22

// ─── TIMING CONSTANTS ────────────────────────────────────────
#define INACTIVITY_THRESHOLD_MS   30000   // 30 sec → burst mode
#define BURST_AFTER_INACTIVITY_MS 10000   // 10 sec after burst → deep sleep
#define ROUTINE_CAPTURE_INTERVAL_MS 5000  // Normal capture every 5 sec
#define BURST_COUNT               5       // photos in burst
#define BURST_INTERVAL_MS         200     // 1 photo per 200ms = 5/sec
#define WAKE_BTN_HOLD_MS          3000    // 3 sec hold → WiFi mode

// ─── WIFI AP CREDENTIALS ─────────────────────────────────────
#define AP_SSID   "SmartPen"
#define AP_PASS   "smartpen123"

// ─── GLOBALS ─────────────────────────────────────────────────
AsyncWebServer server(80);

unsigned long lastActivityTime   = 0;
unsigned long lastCaptureTime    = 0;
unsigned long burstTriggerTime   = 0;
bool          burstDone          = false;
bool          wifiModeActive     = false;
bool          stopWifiRequested  = false;
int           sessionPhotoCount  = 0;

// ─────────────────────────────────────────────────────────────
//  MINIMAL SINGLE-IMAGE PDF WRITER
//  Wraps one JPEG into a valid PDF byte stream.
//  Written inline to avoid large library dependencies.
// ─────────────────────────────────────────────────────────────
bool writeJpegAsPdf(fs::FS &fs, const char* pdfPath,
                    const uint8_t* jpegData, size_t jpegLen,
                    int imgW = 1600, int imgH = 1200) {

  File f = fs.open(pdfPath, FILE_WRITE);
  if (!f) return false;

  // Helper: write formatted string
  auto w = [&](const char* s){ f.print(s); };
  auto wf = [&](const char* fmt, ...) {
    char buf[128]; va_list a; va_start(a,fmt);
    vsnprintf(buf,sizeof(buf),fmt,a); va_end(a);
    f.print(buf);
  };

  // Track byte offsets for xref
  int offsets[6] = {};
  int pos = 0;

  // Macro to record current position (approximated via f.size())
  #define MARK(i) offsets[i] = f.size()

  // ── Header ──
  w("%PDF-1.4\n");

  // ── Object 1 – Catalog ──
  MARK(1);
  w("1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n");

  // ── Object 2 – Pages ──
  MARK(2);
  w("2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n");

  // ── Object 3 – Page ──
  MARK(3);
  // A4 ≈ 595×842 pt; we scale image to fit
  float scaleW = 595.0f / imgW;
  float scaleH = 842.0f / imgH;
  float scale  = (scaleW < scaleH) ? scaleW : scaleH;
  int   pw     = (int)(imgW * scale);
  int   ph     = (int)(imgH * scale);
  int   ox     = (595 - pw) / 2;
  int   oy     = (842 - ph) / 2;

  wf("3 0 obj\n<< /Type /Page /Parent 2 0 R\n"
     "   /MediaBox [0 0 595 842]\n"
     "   /Contents 4 0 R\n"
     "   /Resources << /XObject << /Im1 5 0 R >> >>\n"
     ">>\nendobj\n");

  // ── Object 4 – Content stream ──
  MARK(4);
  char stream[128];
  int slen = snprintf(stream, sizeof(stream),
    "q %d 0 0 %d %d %d cm /Im1 Do Q\n", pw, ph, ox, oy);
  wf("4 0 obj\n<< /Length %d >>\nstream\n", slen);
  f.write((uint8_t*)stream, slen);
  w("endstream\nendobj\n");

  // ── Object 5 – Image XObject (JPEG) ──
  MARK(5);
  wf("5 0 obj\n<< /Type /XObject /Subtype /Image\n"
     "   /Width %d /Height %d\n"
     "   /ColorSpace /DeviceRGB\n"
     "   /BitsPerComponent 8\n"
     "   /Filter /DCTDecode\n"
     "   /Length %u\n"
     ">>\nstream\n", imgW, imgH, (unsigned)jpegLen);
  f.write(jpegData, jpegLen);
  w("\nendstream\nendobj\n");

  // ── xref + trailer ──
  int xrefPos = f.size();
  w("xref\n0 6\n0000000000 65535 f \n");
  for (int i = 1; i <= 5; i++) {
    char line[25];
    snprintf(line, sizeof(line), "%010d 00000 n \n", offsets[i]);
    f.print(line);
  }
  wf("trailer\n<< /Size 6 /Root 1 0 R >>\nstartxref\n%d\n%%%%EOF\n", xrefPos);

  f.close();
  return true;
  #undef MARK
}

// ─────────────────────────────────────────────────────────────
//  CAMERA INIT
// ─────────────────────────────────────────────────────────────
bool initCamera() {
  camera_config_t config;
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer   = LEDC_TIMER_0;
  config.pin_d0       = Y2_GPIO_NUM;
  config.pin_d1       = Y3_GPIO_NUM;
  config.pin_d2       = Y4_GPIO_NUM;
  config.pin_d3       = Y5_GPIO_NUM;
  config.pin_d4       = Y6_GPIO_NUM;
  config.pin_d5       = Y7_GPIO_NUM;
  config.pin_d6       = Y8_GPIO_NUM;
  config.pin_d7       = Y9_GPIO_NUM;
  config.pin_xclk     = XCLK_GPIO_NUM;
  config.pin_pclk     = PCLK_GPIO_NUM;
  config.pin_vsync    = VSYNC_GPIO_NUM;
  config.pin_href     = HREF_GPIO_NUM;
  config.pin_sscb_sda = SIOD_GPIO_NUM;
  config.pin_sscb_scl = SIOC_GPIO_NUM;
  config.pin_pwdn     = PWDN_GPIO_NUM;
  config.pin_reset    = RESET_GPIO_NUM;
  config.xclk_freq_hz = 20000000;
  config.pixel_format = PIXFORMAT_JPEG;
  config.frame_size   = FRAMESIZE_UXGA;  // 1600×1200
  config.jpeg_quality = 10;
  config.fb_count     = 1;

  esp_err_t err = esp_camera_init(&config);
  return (err == ESP_OK);
}

// ─────────────────────────────────────────────────────────────
//  CAPTURE ONE PHOTO → PDF
//  Returns true on success
// ─────────────────────────────────────────────────────────────
bool captureAndSave(const char* label = nullptr) {
  camera_fb_t* fb = esp_camera_fb_get();
  if (!fb) { Serial.println("[CAM] Frame capture failed"); return false; }

  // Build filename  /photos/YYYYMMDD_HHMMSSxxx.pdf
  char path[64];
  if (label) {
    snprintf(path, sizeof(path), "/photos/%s.pdf", label);
  } else {
    snprintf(path, sizeof(path), "/photos/photo_%06d.pdf", sessionPhotoCount);
  }
  sessionPhotoCount++;

  Serial.printf("[CAM] Saving %s (%u bytes JPEG)\n", path, fb->len);
  bool ok = writeJpegAsPdf(SD_MMC, path, fb->buf, fb->len,
                            fb->width, fb->height);
  esp_camera_fb_return(fb);

  if (!ok) Serial.println("[SD]  PDF write failed");
  return ok;
}

// ─────────────────────────────────────────────────────────────
//  DEEP SLEEP
// ─────────────────────────────────────────────────────────────
void goDeepSleep() {
  Serial.println("[PWR] Entering deep sleep. Press WAKE button to wake.");
  Serial.flush();

  // Blink LED 3× to signal sleep
  for (int i = 0; i < 3; i++) {
    digitalWrite(LED_PIN, LOW);  delay(100);
    digitalWrite(LED_PIN, HIGH); delay(100);
  }

  esp_camera_deinit();

  // Wake on WAKE_BTN_PIN LOW  (button pulls GPIO 13 to GND)
  rtc_gpio_pullup_en((gpio_num_t)WAKE_BTN_PIN);
  rtc_gpio_pulldown_dis((gpio_num_t)WAKE_BTN_PIN);
  esp_sleep_enable_ext0_wakeup((gpio_num_t)WAKE_BTN_PIN, 0);

  esp_deep_sleep_start();
  // ── never returns ──
}

// ─────────────────────────────────────────────────────────────
//  WIFI AP MODE  –  simple file browser
// ─────────────────────────────────────────────────────────────
void startWiFiMode() {
  Serial.println("[WiFi] Starting AP...");
  wifiModeActive    = true;
  stopWifiRequested = false;

  WiFi.softAP(AP_SSID, AP_PASS);
  Serial.printf("[WiFi] AP: %s  IP: %s\n",
                AP_SSID, WiFi.softAPIP().toString().c_str());

  // ── Root: list all PDFs ──
  server.on("/", HTTP_GET, [](AsyncWebServerRequest* req) {
    File root = SD_MMC.open("/photos");
    String html = R"(<!DOCTYPE html><html><head>
      <meta name='viewport' content='width=device-width,initial-scale=1'>
      <title>SmartPen Files</title>
      <style>
        body{font-family:sans-serif;background:#111;color:#eee;padding:20px}
        h1{color:#4fc3f7}
        a{color:#80cbc4;display:block;margin:8px 0;font-size:1.1em}
        .stop{background:#e53935;color:#fff;border:none;padding:12px 24px;
              border-radius:8px;font-size:1em;cursor:pointer;margin-top:20px}
      </style></head><body>
      <h1>📷 SmartPen Captures</h1>)";

    if (root && root.isDirectory()) {
      File f = root.openNextFile();
      while (f) {
        if (!f.isDirectory()) {
          String name = String(f.name());
          html += "<a href='/download?f=" + name + "'>📄 " + name + "</a>";
        }
        f = root.openNextFile();
      }
    }
    html += R"(<br><button class='stop' onclick="fetch('/stop').then(()=>alert('WiFi stopping...'))">
               ⛔ Stop WiFi</button></body></html>)";
    req->send(200, "text/html", html);
  });

  // ── Download a file ──
  server.on("/download", HTTP_GET, [](AsyncWebServerRequest* req) {
    if (!req->hasParam("f")) { req->send(400, "text/plain", "Missing param"); return; }
    String fname = "/photos/" + req->getParam("f")->value();
    if (!SD_MMC.exists(fname)) { req->send(404, "text/plain", "Not found"); return; }
    req->send(SD_MMC, fname, "application/pdf", true);
  });

  // ── Stop WiFi command ──
  server.on("/stop", HTTP_GET, [](AsyncWebServerRequest* req) {
    req->send(200, "text/plain", "WiFi stopping");
    stopWifiRequested = true;
  });

  server.begin();
  Serial.println("[WiFi] Web server started.");

  // ── Spin here until stop requested ──
  while (!stopWifiRequested) {
    delay(200);
    // Also allow physical button hold to exit
    if (digitalRead(WAKE_BTN_PIN) == LOW) {
      unsigned long t = millis();
      while (digitalRead(WAKE_BTN_PIN) == LOW && millis()-t < 1000);
      if (millis()-t >= 800) stopWifiRequested = true;
    }
  }

  Serial.println("[WiFi] Stopping AP...");
  server.end();
  WiFi.softAPdisconnect(true);
  wifiModeActive = false;
  Serial.println("[WiFi] AP stopped. Resuming normal operation.");
}

// ─────────────────────────────────────────────────────────────
//  SETUP
// ─────────────────────────────────────────────────────────────
void setup() {
  Serial.begin(115200);
  Serial.println("\n[BOOT] Smart Pen starting...");

  // ── GPIO setup ──
  pinMode(LED_PIN,       OUTPUT); digitalWrite(LED_PIN, HIGH); // off
  pinMode(WAKE_BTN_PIN,  INPUT_PULLUP);
  pinMode(ACTIVITY_PIN,  INPUT_PULLUP);

  // ── SD card ──
  if (!SD_MMC.begin()) {
    Serial.println("[SD] Mount failed! Check card.");
    // Blink rapidly to signal error
    while (true) { digitalWrite(LED_PIN,LOW); delay(50); digitalWrite(LED_PIN,HIGH); delay(50); }
  }
  Serial.println("[SD] Mounted OK");

  // Create photos dir if absent
  if (!SD_MMC.exists("/photos")) SD_MMC.mkdir("/photos");

  // ── Camera ──
  if (!initCamera()) {
    Serial.println("[CAM] Init failed!");
    while (true) { digitalWrite(LED_PIN,LOW); delay(200); digitalWrite(LED_PIN,HIGH); delay(200); }
  }
  Serial.println("[CAM] Init OK");

  // ── Check wakeup reason ──
  esp_sleep_wakeup_cause_t cause = esp_sleep_get_wakeup_cause();
  if (cause == ESP_SLEEP_WAKEUP_EXT0) {
    Serial.println("[PWR] Woke from deep sleep via WAKE button.");
  } else {
    Serial.println("[PWR] Normal boot.");
  }

  lastActivityTime = millis();
  lastCaptureTime  = millis();

  // ── Signal ready ──
  digitalWrite(LED_PIN, LOW); delay(300); digitalWrite(LED_PIN, HIGH);
  Serial.println("[BOOT] Ready.");
}

// ─────────────────────────────────────────────────────────────
//  LOOP
// ─────────────────────────────────────────────────────────────
void loop() {
  unsigned long now = millis();

  // ════════════════════════════════════════════
  //  WAKE BUTTON STATE MACHINE
  //  Short press  → ignored (used for sleep wake)
  //  3 sec hold   → WiFi AP mode
  // ════════════════════════════════════════════
  if (digitalRead(WAKE_BTN_PIN) == LOW) {
    unsigned long pressStart = now;
    while (digitalRead(WAKE_BTN_PIN) == LOW) delay(10);
    unsigned long held = millis() - pressStart;

    if (held >= WAKE_BTN_HOLD_MS) {
      Serial.println("[BTN] 3s hold detected → WiFi mode");
      startWiFiMode();
      lastActivityTime = millis(); // reset timers after WiFi session
      lastCaptureTime  = millis();
      burstDone        = false;
    }
    // short press: do nothing (just woke from sleep or user tap)
    return;
  }

  // ════════════════════════════════════════════
  //  ACTIVITY DETECTION
  //  Pen-tip sensor pulled LOW = writing detected
  // ════════════════════════════════════════════
  bool writing = (digitalRead(ACTIVITY_PIN) == LOW);
  if (writing) {
    lastActivityTime = now;
    burstDone        = false;  // reset burst flag on new activity
  }

  unsigned long idleMs = now - lastActivityTime;

  // ════════════════════════════════════════════
  //  NORMAL CAPTURE  (writing or recently active)
  // ════════════════════════════════════════════
  if (idleMs < INACTIVITY_THRESHOLD_MS) {
    if (now - lastCaptureTime >= ROUTINE_CAPTURE_INTERVAL_MS) {
      Serial.println("[CAP] Routine capture");
      digitalWrite(LED_PIN, LOW);
      captureAndSave();
      digitalWrite(LED_PIN, HIGH);
      lastCaptureTime = now;
    }
    return;
  }

  // ════════════════════════════════════════════
  //  30s INACTIVITY → BURST (5 photos @ 5fps)
  // ════════════════════════════════════════════
  if (!burstDone) {
    Serial.println("[CAP] 30s idle → burst capture (5 photos)");
    for (int i = 0; i < BURST_COUNT; i++) {
      char label[32];
      snprintf(label, sizeof(label), "burst_%06d_%d", sessionPhotoCount, i);
      digitalWrite(LED_PIN, LOW);
      captureAndSave(label);
      digitalWrite(LED_PIN, HIGH);
      delay(BURST_INTERVAL_MS);
    }
    burstDone        = true;
    burstTriggerTime = millis();
    Serial.println("[CAP] Burst done. Waiting for activity or sleep...");
    return;
  }

  // ════════════════════════════════════════════
  //  STILL NO ACTIVITY after burst → DEEP SLEEP
  // ════════════════════════════════════════════
  if (burstDone && (millis() - burstTriggerTime >= BURST_AFTER_INACTIVITY_MS)) {
    Serial.println("[PWR] No activity after burst → deep sleep");
    goDeepSleep();
  }

  delay(50);
}


*/