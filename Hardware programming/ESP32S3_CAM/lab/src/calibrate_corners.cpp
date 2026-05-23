/*
 * ============================================================
 *  calibrate_corners.ino
 *
 *  Run this ONCE after physically mounting the camera on the pen.
 *  It captures a photo, serves it over WiFi, and lets you click
 *  the 4 corners of the paper in your browser.
 *  It then prints the corner coordinates to Serial — copy those
 *  into smart_pen_firmware.ino as your fixed calibration values.
 * ============================================================
 */



/*
#include "esp_camera.h"
#include "SD_MMC.h"
#include <WiFi.h>
#include <ESPAsyncWebServer.h>

// Same camera pins as main firmware (AI Thinker)
#define PWDN_GPIO_NUM  32
#define RESET_GPIO_NUM -1
#define XCLK_GPIO_NUM   0
#define SIOD_GPIO_NUM  26
#define SIOC_GPIO_NUM  27
#define Y9_GPIO_NUM    35
#define Y8_GPIO_NUM    34
#define Y7_GPIO_NUM    39
#define Y6_GPIO_NUM    36
#define Y5_GPIO_NUM    21
#define Y4_GPIO_NUM    19
#define Y3_GPIO_NUM    18
#define Y2_GPIO_NUM     5
#define VSYNC_GPIO_NUM 25
#define HREF_GPIO_NUM  23
#define PCLK_GPIO_NUM  22

AsyncWebServer server(80);
static uint8_t* g_jpegBuf = nullptr;
static size_t   g_jpegLen = 0;

void setup() {
  Serial.begin(115200);

  // Camera init
  camera_config_t cfg;
  cfg.ledc_channel=LEDC_CHANNEL_0; cfg.ledc_timer=LEDC_TIMER_0;
  cfg.pin_d0=Y2_GPIO_NUM; cfg.pin_d1=Y3_GPIO_NUM; cfg.pin_d2=Y4_GPIO_NUM;
  cfg.pin_d3=Y5_GPIO_NUM; cfg.pin_d4=Y6_GPIO_NUM; cfg.pin_d5=Y7_GPIO_NUM;
  cfg.pin_d6=Y8_GPIO_NUM; cfg.pin_d7=Y9_GPIO_NUM;
  cfg.pin_xclk=XCLK_GPIO_NUM; cfg.pin_pclk=PCLK_GPIO_NUM;
  cfg.pin_vsync=VSYNC_GPIO_NUM; cfg.pin_href=HREF_GPIO_NUM;
  cfg.pin_sscb_sda=SIOD_GPIO_NUM; cfg.pin_sscb_scl=SIOC_GPIO_NUM;
  cfg.pin_pwdn=PWDN_GPIO_NUM; cfg.pin_reset=RESET_GPIO_NUM;
  cfg.xclk_freq_hz=20000000; cfg.pixel_format=PIXFORMAT_JPEG;
  cfg.frame_size=FRAMESIZE_SVGA;  // 800×600 for calibration
  cfg.jpeg_quality=10; cfg.fb_count=1;
  esp_camera_init(&cfg);

  // Capture one frame
  camera_fb_t* fb = esp_camera_fb_get();
  if (fb) {
    g_jpegBuf = (uint8_t*)malloc(fb->len);
    g_jpegLen = fb->len;
    memcpy(g_jpegBuf, fb->buf, fb->len);
    esp_camera_fb_return(fb);
  }

  // Start AP
  WiFi.softAP("PenCalibrate", "calibrate");
  Serial.printf("Connect to 'PenCalibrate' WiFi, then open http://%s\n",
                WiFi.softAPIP().toString().c_str());

  // Serve the captured image
  server.on("/image.jpg", HTTP_GET, [](AsyncWebServerRequest* req){
    req->send_P(200, "image/jpeg", g_jpegBuf, g_jpegLen);
  });

  // Serve calibration UI — click 4 corners on the image
  server.on("/", HTTP_GET, [](AsyncWebServerRequest* req){
    String html = R"(<!DOCTYPE html><html><head>
    <meta name='viewport' content='width=device-width,initial-scale=1'>
    <title>Pen Calibration</title>
    <style>
      body{background:#111;color:#eee;font-family:sans-serif;text-align:center;padding:10px}
      h2{color:#4fc3f7} #canvas{cursor:crosshair;border:2px solid #4fc3f7;max-width:100%}
      .dot{display:inline-block;width:14px;height:14px;border-radius:50%;margin:4px}
      #result{background:#1e1e1e;padding:16px;border-radius:8px;margin-top:10px;font-family:monospace;font-size:.85em;text-align:left}
      button{background:#4fc3f7;color:#000;border:none;padding:10px 20px;border-radius:6px;font-size:1em;cursor:pointer;margin-top:8px}
    </style></head><body>
    <h2>📐 Camera Calibration</h2>
    <p>Place a sheet of paper under the pen. Click the <b>4 corners</b> of the paper in this order:<br>
    <span style='color:#f44'>① Top-Left</span> &nbsp;
    <span style='color:#4f4'>② Top-Right</span> &nbsp;
    <span style='color:#44f'>③ Bottom-Left</span> &nbsp;
    <span style='color:#ff4'>④ Bottom-Right</span></p>
    <canvas id='canvas'></canvas>
    <div id='status'>Waiting for clicks... (0/4)</div>
    <div id='result'></div>
    <button onclick='reset()'>Reset</button>
    <script>
      const canvas = document.getElementById('canvas');
      const ctx    = canvas.getContext('2d');
      const img    = new Image();
      const colors = ['#f44','#4f4','#44f','#ff4'];
      const labels = ['TL','TR','BL','BR'];
      let pts = [], scaleX = 1, scaleY = 1;

      img.onload = () => {
        canvas.width  = img.width;
        canvas.height = img.height;
        ctx.drawImage(img, 0, 0);
        // Scale for display (max 600px wide)
        let disp = Math.min(600, img.width);
        canvas.style.width  = disp + 'px';
        scaleX = img.width  / disp;
        scaleY = img.height / (disp * img.height / img.width);
      };
      img.src = '/image.jpg';

      canvas.onclick = e => {
        if (pts.length >= 4) return;
        const rect = canvas.getBoundingClientRect();
        let cx = (e.clientX - rect.left) * scaleX;
        let cy = (e.clientY - rect.top)  * scaleY;
        pts.push({x: Math.round(cx), y: Math.round(cy)});
        // Draw dot
        ctx.beginPath();
        ctx.arc(cx, cy, 8, 0, 2*Math.PI);
        ctx.fillStyle = colors[pts.length-1];
        ctx.fill();
        ctx.fillStyle = '#000';
        ctx.font = 'bold 14px sans-serif';
        ctx.fillText(labels[pts.length-1], cx+10, cy-5);
        document.getElementById('status').textContent =
          `Clicked ${pts.length}/4 corners`;
        if (pts.length === 4) showResult();
      };

      function showResult() {
        const [tl,tr,bl,br] = pts;
        const code =
`// ── Paste these into smart_pen_firmware.ino ──
PaperCorners CAL_CORNERS = {
  .tlX=${tl.x}, .tlY=${tl.y},   // Top-Left
  .trX=${tr.x}, .trY=${tr.y},   // Top-Right
  .blX=${bl.x}, .blY=${bl.y},   // Bottom-Left
  .brX=${br.x}, .brY=${br.y}    // Bottom-Right
};`;
        document.getElementById('result').textContent = code;
        document.getElementById('status').innerHTML =
          '✅ Done! Copy the values above into your firmware.';
      }

      function reset() { pts=[]; ctx.drawImage(img,0,0);
        document.getElementById('status').textContent='Reset. Click 4 corners.';
        document.getElementById('result').textContent=''; }
    </script></body></html>)";
    req->send(200, "text/html", html);
  });

  server.begin();
}

void loop() { delay(100); }






*/