#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <TFT_eSPI.h>
#include <Adafruit_ADS1X15.h>

// --- Added for cloud push ---
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>   // Install "ArduinoJson" by Benoit Blanchon via Library Manager

TFT_eSPI tft = TFT_eSPI();
Adafruit_ADS1115 ads;

// --- Physical Hardware Pins ---
#define PUMP_PIN 15 // ESP32 GPIO connected to your relay module

// --- WiFi + Backend Config (EDIT THESE) ---
const char* WIFI_SSID     = "MFC";
const char* WIFI_PASSWORD = "12345678";

// Your deployed backend URL from Render/Railway (see README), e.g.:
// "https://pmfc-neon-bridge.onrender.com/api/readings"
const char* SERVER_URL   = "https://YOUR-BACKEND-URL.onrender.com/api/readings";
const char* DEVICE_API_KEY = "pick-a-long-random-secret"; // must match server's DEVICE_API_KEY

const uint32_t SERVER_PUSH_INTERVAL_MS = 5000; // push every 5s (don't hammer the free tier)
uint32_t lastServerPush = 0;

// --- Apple System Design Tokens (RGB565) ---
#define COLOR_BG          0xFFFF // #FFFFFF Pure White
#define COLOR_CARD        0xF7F7 // #F2F2F7 System Gray 6
#define COLOR_BORDER      0xE5E5 // #E5E5EA System Gray 5
#define COLOR_TEXT_MAIN   0x1C9C // #1C1C1E System Primary Dark
#define COLOR_TEXT_MUTED  0x8E38 // #8E8E93 System Secondary Gray
#define COLOR_TEXT_DARK   0x29E9 // #2C3E50 Dark slate for cell numbers

// Apple iOS App Tint Colors
#define TINT_POWER   0xFD20 // #FF9500 iOS Orange / Greenish Accent 0x256C
#define TINT_GRAPH   0x03FF // #007AFF iOS Blue
#define TINT_SOIL    0x3640 // #34C759 iOS Green
#define TINT_PUMP    0x35BF // #30B0C7 iOS Teal
#define TINT_CTRL    0x5ADF // #5856D6 iOS Indigo
#define TINT_SETT    0x8E38 // #8E8E93 iOS Gray

// --- System State ---
enum AppState { STATE_BOOT, STATE_HOME, STATE_APP_POWER, STATE_APP_CONTROL, STATE_APP_GENERIC };
AppState currentState = STATE_BOOT;
int activeAppIndex = 0;

// --- Home Screen Grid Geometry ---
const int iconSize = 58;
const int cornerRadius = 14;
const int spacingX = 32;
const int spacingY = 22;
const int startX = 35;
const int startY = 44;

struct AppMeta {
  String name;
  uint16_t color;
};

AppMeta apps[6] = {
  {"Power",    TINT_POWER},
  {"Analytics",TINT_GRAPH},
  {"Soil/Bio",  TINT_SOIL},
  {"Irrigate",  TINT_PUMP},
  {"Control",   TINT_CTRL},
  {"Settings",  TINT_SETT}
};

// --- Power App Card Layout Variables ---
const int cardWidth = 145;
const int cardHeight = 85;
const int cardMarginX = 10;
const int cardMarginY = 45;
const int cardSpacing = 10;

int cardX[4] = {cardMarginX, cardMarginX + cardWidth + cardSpacing, cardMarginX, cardMarginX + cardWidth + cardSpacing};
int cardY[4] = {cardMarginY, cardMarginY, cardMarginY + cardHeight + cardSpacing, cardMarginY + cardHeight + cardSpacing};

// Data telemetry variables
float cellVoltage[4];
float cellPower[4]   = {1.20, 1.85, 0.95, 2.10};
uint32_t lastDataUpdate = 0;

// Water Pump State
bool pumpState = false;

// --- Function Prototypes ---
void runPSPBootAnimation();
void drawAppleHomeScreen();
void drawAppIcon(int index, int x, int y);
void drawVectorGlyph(int index, int cx, int cy, uint16_t theme);
void renderHeaderBar();
void calibrateTouchScreen();
void handleTouch();
int getTouchedApp(uint16_t tx, uint16_t ty);
bool isBackButtonPressed(uint16_t tx, uint16_t ty);

// Power App Functions
void openPowerAppView();
void updatePowerDataUI();

// Control/Pump App Functions
void openControlAppView();
void drawPumpToggleSwitch(bool state);

// Generic App View
void openGenericAppView(int index);

// --- Added: cloud push ---
void connectWiFi();
void sendDataToServer();

void setup() {
  Serial.begin(115200);

  pinMode(PUMP_PIN, OUTPUT);
  digitalWrite(PUMP_PIN, LOW); // Default relay OFF

  Wire.begin(32, 33);
  ads.begin(0x48);
  ads.setGain(GAIN_ONE);

  tft.init();
  tft.setRotation(3); // Landscape mode

  calibrateTouchScreen();

  connectWiFi(); // do this before/while the boot animation plays

  runPSPBootAnimation();

  currentState = STATE_HOME;
  drawAppleHomeScreen();
}

void loop() {
  handleTouch();

  int16_t adcValue[4];
  float calculatedVoltage[4];

  for(int i = 0; i < 4; i++){
    // Retrieve raw data from hardware pin A0
    adcValue[i] = ads.readADC_SingleEnded(i);

    // Use the library's function to compute the exact voltage
    calculatedVoltage[i] = ads.computeVolts(adcValue[i]);
  }

  // Always keep cellVoltage/cellPower fresh (not just while the Power screen is open),
  // so the cloud gets live data regardless of which app screen is showing.
  if (millis() - lastDataUpdate > 800) {
    for (int i = 0; i < 4; i++) {
      cellVoltage[i] = calculatedVoltage[i];
      if (cellVoltage[i] < 0.01) cellVoltage[i] = 0.01;
      // P = V^2 / R (assuming 100 ohm resistor)
      cellPower[i] = (cellVoltage[i] * cellVoltage[i]) / 100.0 * 1000.0;
    }
    if (currentState == STATE_APP_POWER) {
      updatePowerDataUI();
    }
    lastDataUpdate = millis();
  }

  // --- Push to Neon (via backend) every SERVER_PUSH_INTERVAL_MS ---
  if (millis() - lastServerPush > SERVER_PUSH_INTERVAL_MS) {
    sendDataToServer();
    lastServerPush = millis();
  }

  delay(20);
}

// ==========================================
// --- WIFI + CLOUD PUSH ---
// ==========================================
void connectWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  Serial.print("Connecting to WiFi");
  uint32_t start = millis();
  while (WiFi.status() != WL_CONNECTED && millis() - start < 15000) {
    delay(400);
    Serial.print(".");
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println();
    Serial.print("WiFi connected, IP: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println();
    Serial.println("WiFi connect failed - will keep retrying in background reads.");
  }
}

void sendDataToServer() {
  if (WiFi.status() != WL_CONNECTED) {
    connectWiFi(); // try to reconnect; skip this push if it fails
    if (WiFi.status() != WL_CONNECTED) return;
  }

  WiFiClientSecure client;
  client.setInsecure(); // skip TLS cert validation - fine for a hobby project,
                         // but note this does not verify the server's identity

  HTTPClient http;
  if (!http.begin(client, SERVER_URL)) {
    Serial.println("HTTP begin failed");
    return;
  }

  http.addHeader("Content-Type", "application/json");
  http.addHeader("x-api-key", DEVICE_API_KEY);

  StaticJsonDocument<256> doc;
  JsonArray cells = doc.createNestedArray("cells");
  for (int i = 0; i < 4; i++) {
    JsonObject c = cells.createNestedObject();
    c["v"] = cellVoltage[i];
    c["p"] = cellPower[i];
  }

  String payload;
  serializeJson(doc, payload);

  int httpCode = http.POST(payload);
  if (httpCode > 0) {
    Serial.printf("Push OK, server responded %d\n", httpCode);
  } else {
    Serial.printf("Push failed: %s\n", http.errorToString(httpCode).c_str());
  }

  http.end();
}

// --- Touch Handling Logic ---
void calibrateTouchScreen() {
  uint16_t calData[5] = { 398, 3521, 327, 3456, 1 };
  tft.setTouch(calData);
}

void handleTouch() {
  uint16_t t_x = 0, t_y = 0;
  bool touched = tft.getTouch(&t_x, &t_y, 400);

  if (!touched) return;

  // 1. Home Screen Taps
  if (currentState == STATE_HOME) {
    int appIndex = getTouchedApp(t_x, t_y);
    if (appIndex != -1) {
      activeAppIndex = appIndex;

      if (appIndex == 0) { // Power App
        currentState = STATE_APP_POWER;
        openPowerAppView();
      }
      else if (appIndex == 3 || appIndex == 4) { // Pump / Control App
        currentState = STATE_APP_CONTROL;
        openControlAppView();
      }
      else { // Other Apps
        currentState = STATE_APP_GENERIC;
        openGenericAppView(appIndex);
      }
      delay(300); // Touch debounce
    }
  }
  // 2. Power App Screen Taps
  else if (currentState == STATE_APP_POWER) {
    if (isBackButtonPressed(t_x, t_y)) {
      currentState = STATE_HOME;
      drawAppleHomeScreen();
      delay(300);
    }
  }
  // 3. Control App Screen Taps
  else if (currentState == STATE_APP_CONTROL) {
    if (isBackButtonPressed(t_x, t_y)) {
      currentState = STATE_HOME;
      drawAppleHomeScreen();
      delay(300);
    }
    // Toggle Switch Tap Hit-Box (X: 80..240, Y: 100..170)
    else if (t_x >= 80 && t_x <= 240 && t_y >= 100 && t_y <= 170) {
      pumpState = !pumpState;
      digitalWrite(PUMP_PIN, pumpState ? HIGH : LOW); // Hardware Relay Control
      drawPumpToggleSwitch(pumpState);
      delay(350); // Debounce toggle tap
    }
  }
  // 4. Generic Screen Taps
  else if (currentState == STATE_APP_GENERIC) {
    if (isBackButtonPressed(t_x, t_y)) {
      currentState = STATE_HOME;
      drawAppleHomeScreen();
      delay(300);
    }
  }
}

int getTouchedApp(uint16_t tx, uint16_t ty) {
  int index = 0;
  for (int row = 0; row < 2; row++) {
    for (int col = 0; col < 3; col++) {
      int x = startX + (col * (iconSize + spacingX));
      int y = startY + (row * (iconSize + spacingY));

      if (tx >= (x - 8) && tx <= (x + iconSize + 8) &&
          ty >= (y - 8) && ty <= (y + iconSize + 22)) {
        return index;
      }
      index++;
    }
  }
  return -1;
}

bool isBackButtonPressed(uint16_t tx, uint16_t ty) {
  // Back pill button region (Top Right)
  return (tx >= 220 && tx <= 315 && ty >= 2 && ty <= 42);
}

// ==========================================
// --- POWER APP: 4-CELL CARD DASHBOARD ---
// ==========================================
void openPowerAppView() {
  tft.fillScreen(COLOR_BG);

  // Top Navigation Bar
  tft.setTextColor(TINT_SOIL, COLOR_BG);
  tft.setTextDatum(TL_DATUM);
  tft.drawString("PMFC MONITOR", 12, 12, 4);

  // Back Button Pill
  tft.fillRoundRect(230, 8, 78, 28, 14, TINT_SOIL);
  tft.setTextColor(COLOR_BG);
  tft.setTextDatum(MC_DATUM);
  tft.drawString("< Back", 269, 22, 2);

  // Draw 4 Cell Cards
  for (int i = 0; i < 4; i++) {
    tft.fillRoundRect(cardX[i], cardY[i], cardWidth, cardHeight, 8, COLOR_CARD);
    tft.drawRoundRect(cardX[i], cardY[i], cardWidth, cardHeight, 8, TINT_SOIL);

    // Card Header Bar
    tft.fillRoundRect(cardX[i], cardY[i], cardWidth, 24, 8, TINT_SOIL);
    tft.fillRect(cardX[i], cardY[i] + 14, cardWidth, 10, TINT_SOIL);

    tft.setTextColor(COLOR_BG);
    tft.setTextDatum(TC_DATUM);
    String cellTitle = "CELL " + String(i + 1);
    tft.drawString(cellTitle, cardX[i] + (cardWidth / 2), cardY[i] + 4, 2);

    // Unit Labels
    tft.setTextColor(COLOR_TEXT_MUTED, COLOR_CARD);
    tft.setTextDatum(MR_DATUM);
    tft.drawString("V", cardX[i] + cardWidth - 12, cardY[i] + 45, 2);
    tft.drawString("mW", cardX[i] + cardWidth - 12, cardY[i] + 66, 2);
  }

  updatePowerDataUI();
}

void updatePowerDataUI() {
  tft.setTextDatum(MR_DATUM);
  for (int i = 0; i < 4; i++) {
    tft.setTextColor(COLOR_TEXT_DARK, COLOR_CARD);
    tft.drawFloat(cellVoltage[i], 3, cardX[i] + cardWidth - 36, cardY[i] + 45, 4);
    tft.drawFloat(cellPower[i], 2, cardX[i] + cardWidth - 36, cardY[i] + 66, 4);
  }
}

// ==========================================
// --- CONTROL APP: PUMP SWITCH ---
// ==========================================
void openControlAppView() {
  tft.fillScreen(COLOR_BG);

  // Top Bar
  tft.setTextColor(COLOR_TEXT_MAIN, COLOR_BG);
  tft.setTextDatum(TL_DATUM);
  tft.drawString("Control", 12, 12, 4);

  // Back Button
  tft.fillRoundRect(230, 8, 78, 28, 14, TINT_CTRL);
  tft.setTextColor(COLOR_BG);
  tft.setTextDatum(MC_DATUM);
  tft.drawString("< Back", 269, 22, 2);

  // Main Content Card
  tft.fillRoundRect(12, 48, 296, 180, 14, COLOR_CARD);
  tft.drawRoundRect(12, 48, 296, 180, 14, COLOR_BORDER);

  tft.setTextColor(COLOR_TEXT_MAIN, COLOR_CARD);
  tft.setTextDatum(TC_DATUM);
  tft.drawString("Water Pump Relay", 160, 64, 4);

  drawPumpToggleSwitch(pumpState);
}

void drawPumpToggleSwitch(bool state) {
  int swX = 110;
  int swY = 108;
  int swW = 100;
  int swH = 50;

  uint16_t switchBg = state ? TINT_SOIL : COLOR_BORDER;

  // Draw Switch Track
  tft.fillRoundRect(swX, swY, swW, swH, 25, switchBg);

  // Draw Switch Circular Knob
  int knobX = state ? (swX + swW - 25) : (swX + 25);
  tft.fillCircle(knobX, swY + 25, 20, COLOR_BG);

  // Draw Status Text underneath
  tft.fillRoundRect(50, 172, 220, 30, 6, COLOR_CARD); // Clear old text background
  tft.setTextDatum(TC_DATUM);

  if (state) {
    tft.setTextColor(TINT_SOIL, COLOR_CARD);
    tft.drawString("STATUS: PUMP RUNNING", 160, 178, 2);
  } else {
    tft.setTextColor(COLOR_TEXT_MUTED, COLOR_CARD);
    tft.drawString("STATUS: PUMP OFF", 160, 178, 2);
  }
}

// ==========================================
// --- GENERIC APP VIEW ---
// ==========================================
void openGenericAppView(int index) {
  tft.fillScreen(COLOR_BG);

  tft.setTextColor(COLOR_TEXT_MAIN, COLOR_BG);
  tft.setTextDatum(TL_DATUM);
  tft.drawString(apps[index].name, 12, 12, 4);

  tft.fillRoundRect(230, 8, 78, 28, 14, apps[index].color);
  tft.setTextColor(COLOR_BG);
  tft.setTextDatum(MC_DATUM);
  tft.drawString("< Back", 269, 22, 2);

  tft.fillRoundRect(12, 48, 296, 180, 14, COLOR_CARD);
  tft.drawRoundRect(12, 48, 296, 180, 14, COLOR_BORDER);

  tft.setTextColor(COLOR_TEXT_MUTED, COLOR_CARD);
  tft.drawString("Module Telemetry Active", 160, 130, 2);
}

// ==========================================
// --- HOME SCREEN & BOOT ANIMATION ---
// ==========================================
void runPSPBootAnimation() {
  tft.fillScreen(COLOR_BG);

  for (int x = -40; x <= 360; x += 12) {
    tft.fillScreen(COLOR_BG);

    for (int i = 0; i < 320; i += 2) {
      int y = 120 + sin((i + x) * 0.03) * 18;
      tft.drawPixel(i, y, TINT_GRAPH);
      tft.drawPixel(i, y + 1, TINT_PUMP);
    }

    if (x > 60 && x < 260) {
      int w = map(x, 60, 260, 20, 220);
      int h = map(x, 60, 260, 10, 80);
      tft.fillRoundRect(160 - (w/2), 120 - (h/2), w, h, 16, COLOR_TEXT_MAIN);
    }
    delay(8);
  }

  tft.fillRoundRect(50, 80, 220, 80, 16, COLOR_TEXT_MAIN);
  tft.setTextColor(COLOR_BG);
  tft.setTextDatum(MC_DATUM);
  tft.drawString("PMFC OS", 160, 108, 4);
  tft.setTextColor(TINT_SOIL);
  tft.drawString("SYSTEM READY", 160, 134, 2);

  delay(800);
}

void drawAppleHomeScreen() {
  tft.fillScreen(COLOR_BG);
  renderHeaderBar();

  int index = 0;
  for (int row = 0; row < 2; row++) {
    for (int col = 0; col < 3; col++) {
      int x = startX + (col * (iconSize + spacingX));
      int y = startY + (row * (iconSize + spacingY));

      drawAppIcon(index, x, y);
      index++;
      delay(40);
    }
  }
}

void drawAppIcon(int index, int x, int y) {
  uint16_t theme = apps[index].color;

  tft.fillRoundRect(x, y, iconSize, iconSize, cornerRadius, theme);
  tft.drawFastHLine(x + 5, y + 1, iconSize - 10, COLOR_BG);

  drawVectorGlyph(index, x + (iconSize / 2), y + (iconSize / 2), theme);

  tft.setTextColor(COLOR_TEXT_MAIN);
  tft.setTextDatum(TC_DATUM);
  tft.drawString(apps[index].name, x + (iconSize / 2), y + iconSize + 5, 2);
}

void drawVectorGlyph(int index, int cx, int cy, uint16_t theme) {
  switch(index) {
    case 0: // Power
      tft.fillTriangle(cx + 2, cy - 12, cx - 6, cy + 1, cx + 1, cy + 1, COLOR_BG);
      tft.fillTriangle(cx - 2, cy + 12, cx + 6, cy - 1, cx - 1, cy - 1, COLOR_BG);
      break;

    case 1: // Analytics
      tft.fillRect(cx - 10, cy + 2, 5, 10, COLOR_BG);
      tft.fillRect(cx - 2,  cy - 4, 5, 16, COLOR_BG);
      tft.fillRect(cx + 6,  cy - 10, 5, 22, COLOR_BG);
      break;

    case 2: // Soil/Bio
      tft.fillCircle(cx - 4, cy - 2, 6, COLOR_BG);
      tft.fillCircle(cx + 4, cy + 2, 6, COLOR_BG);
      tft.fillRect(cx - 1, cy, 3, 12, COLOR_BG);
      break;

    case 3: // Irrigate
      tft.fillCircle(cx, cy + 4, 7, COLOR_BG);
      tft.fillTriangle(cx - 6, cy + 4, cx + 6, cy + 4, cx, cy - 10, COLOR_BG);
      break;

    case 4: // Control
      tft.fillRect(cx - 12, cy - 6, 24, 3, COLOR_BG);
      tft.fillRect(cx - 12, cy + 4, 24, 3, COLOR_BG);
      tft.fillCircle(cx - 4, cy - 5, 4, COLOR_TEXT_MAIN);
      tft.fillCircle(cx + 4, cy + 5, 4, COLOR_TEXT_MAIN);
      break;

    case 5: // Settings
      tft.fillCircle(cx, cy, 9, COLOR_BG);
      tft.fillCircle(cx, cy, 4, theme);
      break;
  }
}

void renderHeaderBar() {
  tft.setTextColor(COLOR_TEXT_MAIN);
  tft.setTextDatum(TL_DATUM);
  tft.drawString("9:41", 14, 8, 2);

  tft.setTextColor(COLOR_TEXT_MUTED);
  tft.setTextDatum(TR_DATUM);
  tft.drawString("PMFC Node 01", 306, 8, 2);

  tft.drawFastHLine(10, 26, 300, COLOR_BORDER);
}
