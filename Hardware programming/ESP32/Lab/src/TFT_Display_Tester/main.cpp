#include <Arduino.h>
#include <TFT_eSPI.h>

TFT_eSPI tft = TFT_eSPI();

#define TFT_W 240
#define TFT_H 320

// -----------------------------------------------------------------------------
// Colors
// -----------------------------------------------------------------------------
#define C_BLACK   TFT_BLACK
#define C_WHITE   TFT_WHITE
#define C_RED     TFT_RED
#define C_GREEN   TFT_GREEN
#define C_BLUE    TFT_BLUE
#define C_CYAN    TFT_CYAN
#define C_MAGENTA TFT_MAGENTA
#define C_YELLOW  TFT_YELLOW
#define C_ORANGE  0xFD20
#define C_PURPLE  0x780F
#define C_GRAY    0x8410

// -----------------------------------------------------------------------------
// Helpers
// -----------------------------------------------------------------------------

void title(const char *text)
{
    tft.fillScreen(TFT_BLACK);

    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.setTextSize(2);
    tft.setTextDatum(MC_DATUM);

    tft.drawString(text, TFT_W / 2, 12);

    tft.setTextDatum(TL_DATUM);
}

void waitTest(uint32_t ms = 1200)
{
    delay(ms);
}

// -----------------------------------------------------------------------------
// TEST 1 - Solid colors
// -----------------------------------------------------------------------------

void testSolidColors()
{
    title("SOLID COLORS");

    uint16_t colors[] = {
        TFT_BLACK,
        TFT_WHITE,
        TFT_RED,
        TFT_GREEN,
        TFT_BLUE,
        TFT_CYAN,
        TFT_MAGENTA,
        TFT_YELLOW,
        C_ORANGE,
        C_PURPLE,
        C_GRAY
    };

    const char *names[] = {
        "BLACK",
        "WHITE",
        "RED",
        "GREEN",
        "BLUE",
        "CYAN",
        "MAGENTA",
        "YELLOW",
        "ORANGE",
        "PURPLE",
        "GRAY"
    };

    for (int i = 0; i < 11; i++)
    {
        tft.fillScreen(colors[i]);

        tft.setTextDatum(MC_DATUM);
        tft.setTextColor(
            (i == 0 || i == 2 || i == 3 || i == 4 || i == 5 ||
             i == 6 || i == 8 || i == 9)
                ? TFT_WHITE
                : TFT_BLACK);

        tft.setTextSize(3);
        tft.drawString(names[i], TFT_W / 2, TFT_H / 2);

        delay(500);
    }

    tft.setTextDatum(TL_DATUM);
}

// -----------------------------------------------------------------------------
// TEST 2 - RGB color bars
// -----------------------------------------------------------------------------

void testColorBars()
{
    title("COLOR BARS");

    int h = (TFT_H - 25) / 8;

    uint16_t colors[] = {
        TFT_RED,
        TFT_GREEN,
        TFT_BLUE,
        TFT_CYAN,
        TFT_MAGENTA,
        TFT_YELLOW,
        TFT_WHITE,
        TFT_BLACK
    };

    for (int i = 0; i < 8; i++)
    {
        tft.fillRect(0, 25 + i * h, TFT_W, h, colors[i]);
    }

    delay(1500);
}

// -----------------------------------------------------------------------------
// TEST 3 - Grayscale
// -----------------------------------------------------------------------------

void testGrayscale()
{
    title("GRAYSCALE");

    int barWidth = TFT_W / 16;

    for (int i = 0; i < 16; i++)
    {
        uint8_t v = i * 17;

        uint16_t color = tft.color565(v, v, v);

        tft.fillRect(
            i * barWidth,
            30,
            barWidth + 1,
            TFT_H - 30,
            color);
    }

    delay(1500);
}

// -----------------------------------------------------------------------------
// TEST 4 - RGB gradients
// -----------------------------------------------------------------------------

void testGradients()
{
    title("RGB GRADIENTS");

    // Red gradient
    for (int x = 0; x < TFT_W; x++)
    {
        uint8_t r = map(x, 0, TFT_W - 1, 0, 255);
        uint16_t c = tft.color565(r, 0, 0);

        tft.drawFastVLine(x, 30, 90, c);
    }

    // Green gradient
    for (int x = 0; x < TFT_W; x++)
    {
        uint8_t g = map(x, 0, TFT_W - 1, 0, 255);
        uint16_t c = tft.color565(0, g, 0);

        tft.drawFastVLine(x, 120, 90, c);
    }

    // Blue gradient
    for (int x = 0; x < TFT_W; x++)
    {
        uint8_t b = map(x, 0, TFT_W - 1, 0, 255);
        uint16_t c = tft.color565(0, 0, b);

        tft.drawFastVLine(x, 210, 110, c);
    }

    delay(1500);
}

// -----------------------------------------------------------------------------
// TEST 5 - Checkerboard
// -----------------------------------------------------------------------------

void testCheckerboard()
{
    title("CHECKERBOARD");

    int size = 20;

    for (int y = 25; y < TFT_H; y += size)
    {
        for (int x = 0; x < TFT_W; x += size)
        {
            bool white = ((x / size) + (y / size)) & 1;

            tft.fillRect(
                x,
                y,
                size,
                size,
                white ? TFT_WHITE : TFT_BLACK);
        }
    }

    delay(1500);
}

// -----------------------------------------------------------------------------
// TEST 6 - Lines
// -----------------------------------------------------------------------------

void testLines()
{
    title("LINES");

    // Horizontal
    for (int y = 30; y < TFT_H; y += 10)
    {
        tft.drawFastHLine(0, y, TFT_W, TFT_GREEN);
    }

    // Vertical
    for (int x = 0; x < TFT_W; x += 10)
    {
        tft.drawFastVLine(x, 30, TFT_H - 30, TFT_BLUE);
    }

    // Diagonal
    for (int i = 0; i < 20; i++)
    {
        tft.drawLine(
            0,
            30,
            TFT_W - 1,
            TFT_H - 1,
            TFT_RED);

        tft.drawLine(
            0,
            TFT_H - 1,
            TFT_W - 1,
            30,
            TFT_RED);
    }

    delay(1500);
}

// -----------------------------------------------------------------------------
// TEST 7 - Rectangles
// -----------------------------------------------------------------------------

void testRectangles()
{
    title("RECTANGLES");

    int x = 0;
    int y = 30;
    int w = TFT_W;
    int h = TFT_H - 40;

    for (int i = 0; i < 12; i++)
    {
        tft.drawRect(x, y, w, h, TFT_GREEN);

        x += 8;
        y += 8;
        w -= 16;
        h -= 16;

        if (w <= 0 || h <= 0)
            break;
    }

    delay(1500);
}

// -----------------------------------------------------------------------------
// TEST 8 - Filled rectangles
// -----------------------------------------------------------------------------

void testFilledRectangles()
{
    title("FILLED RECTANGLES");

    for (int i = 0; i < 20; i++)
    {
        int x = random(0, TFT_W);
        int y = random(30, TFT_H);

        int w = random(5, 80);
        int h = random(5, 80);

        if (x + w >= TFT_W)
            w = TFT_W - x;

        if (y + h >= TFT_H)
            h = TFT_H - y;

        tft.fillRect(
            x,
            y,
            w,
            h,
            random(0xFFFF));
    }

    delay(1500);
}

// -----------------------------------------------------------------------------
// TEST 9 - Circles
// -----------------------------------------------------------------------------

void testCircles()
{
    title("CIRCLES");

    int cx = TFT_W / 2;
    int cy = TFT_H / 2 + 10;

    for (int r = 10; r < 115; r += 10)
    {
        tft.drawCircle(
            cx,
            cy,
            r,
            random(0xFFFF));
    }

    // Filled circles
    for (int r = 10; r <= 50; r += 10)
    {
        tft.fillCircle(
            random(20, TFT_W - 20),
            random(50, TFT_H - 20),
            r,
            random(0xFFFF));
    }

    delay(1500);
}

// -----------------------------------------------------------------------------
// TEST 10 - Triangles
// -----------------------------------------------------------------------------

void testTriangles()
{
    title("TRIANGLES");

    for (int i = 0; i < 15; i++)
    {
        int x1 = random(TFT_W);
        int y1 = random(30, TFT_H);

        int x2 = random(TFT_W);
        int y2 = random(30, TFT_H);

        int x3 = random(TFT_W);
        int y3 = random(30, TFT_H);

        tft.drawTriangle(
            x1, y1,
            x2, y2,
            x3, y3,
            random(0xFFFF));
    }

    delay(1500);
}

// -----------------------------------------------------------------------------
// TEST 11 - Text
// -----------------------------------------------------------------------------

void testText()
{
    title("TEXT TEST");

    tft.setTextColor(TFT_WHITE);

    tft.setTextSize(1);
    tft.drawString("Size 1 - ABCDEFGHIJKLMNOP", 5, 35);

    tft.setTextSize(2);
    tft.drawString("Size 2", 5, 60);

    tft.setTextSize(3);
    tft.drawString("Size 3", 5, 95);

    tft.setTextSize(4);
    tft.drawString("SIZE 4", 5, 145);

    tft.setTextSize(2);

    tft.setTextColor(TFT_RED);
    tft.drawString("RED TEXT", 5, 200);

    tft.setTextColor(TFT_GREEN);
    tft.drawString("GREEN TEXT", 5, 225);

    tft.setTextColor(TFT_BLUE);
    tft.drawString("BLUE TEXT", 5, 250);

    tft.setTextColor(TFT_YELLOW);
    tft.drawString("0123456789", 5, 280);

    delay(2000);
}

// -----------------------------------------------------------------------------
// TEST 12 - Text on different backgrounds
// -----------------------------------------------------------------------------

void testTextBackground()
{
    title("TEXT BACKGROUND");

    const char *texts[] = {
        "BLACK",
        "RED",
        "GREEN",
        "BLUE",
        "WHITE"
    };

    uint16_t bg[] = {
        TFT_BLACK,
        TFT_RED,
        TFT_GREEN,
        TFT_BLUE,
        TFT_WHITE
    };

    uint16_t fg[] = {
        TFT_WHITE,
        TFT_WHITE,
        TFT_BLACK,
        TFT_WHITE,
        TFT_BLACK
    };

    for (int i = 0; i < 5; i++)
    {
        tft.fillScreen(bg[i]);

        tft.setTextDatum(MC_DATUM);
        tft.setTextColor(fg[i], bg[i]);
        tft.setTextSize(3);

        tft.drawString(
            texts[i],
            TFT_W / 2,
            TFT_H / 2);

        delay(500);
    }

    tft.setTextDatum(TL_DATUM);
}

// -----------------------------------------------------------------------------
// TEST 13 - Border
// -----------------------------------------------------------------------------

void testBorder()
{
    title("BORDER TEST");

    tft.drawRect(
        0,
        25,
        TFT_W,
        TFT_H - 25,
        TFT_RED);

    tft.drawRect(
        2,
        27,
        TFT_W - 4,
        TFT_H - 29,
        TFT_GREEN);

    tft.drawRect(
        4,
        29,
        TFT_W - 8,
        TFT_H - 33,
        TFT_BLUE);

    delay(1500);
}

// -----------------------------------------------------------------------------
// TEST 14 - Pixel test
// -----------------------------------------------------------------------------

void testPixels()
{
    title("PIXEL TEST");

    for (int i = 0; i < 5000; i++)
    {
        int x = random(TFT_W);
        int y = random(30, TFT_H);

        tft.drawPixel(
            x,
            y,
            random(0xFFFF));
    }

    delay(1500);
}

// -----------------------------------------------------------------------------
// TEST 15 - Fast fill benchmark
// -----------------------------------------------------------------------------

void testFillSpeed()
{
    title("FILL SPEED");

    uint32_t start = millis();

    const int frames = 20;

    for (int i = 0; i < frames; i++)
    {
        tft.fillScreen(
            random(0xFFFF));
    }

    uint32_t elapsed = millis() - start;

    float fps =
        (elapsed > 0)
            ? (frames * 1000.0f / elapsed)
            : 0;

    tft.fillScreen(TFT_BLACK);

    tft.setTextColor(TFT_WHITE);
    tft.setTextSize(2);

    tft.drawString(
        "Frames: " + String(frames),
        10,
        60);

    tft.drawString(
        "Time: " + String(elapsed) + " ms",
        10,
        90);

    tft.drawString(
        "FPS: " + String(fps, 2),
        10,
        120);

    delay(2500);
}

// -----------------------------------------------------------------------------
// TEST 16 - Screen inversion
// -----------------------------------------------------------------------------

void testInversion()
{
    title("INVERSION");

    tft.fillScreen(TFT_WHITE);

    delay(500);

    tft.invertDisplay(true);

    delay(800);

    tft.invertDisplay(false);

    delay(800);

    tft.fillScreen(TFT_BLACK);

    delay(500);

    tft.invertDisplay(true);

    delay(800);

    tft.invertDisplay(false);

    delay(800);
}

// -----------------------------------------------------------------------------
// TEST 17 - Grid / alignment
// -----------------------------------------------------------------------------

void testGrid()
{
    title("GRID ALIGNMENT");

    for (int x = 0; x < TFT_W; x += 20)
    {
        tft.drawFastVLine(
            x,
            30,
            TFT_H - 30,
            TFT_DARKGREY);
    }

    for (int y = 30; y < TFT_H; y += 20)
    {
        tft.drawFastHLine(
            0,
            y,
            TFT_W,
            TFT_DARKGREY);
    }

    tft.setTextColor(TFT_YELLOW);
    tft.setTextSize(1);

    for (int x = 0; x < TFT_W; x += 20)
    {
        tft.drawNumber(x, x + 2, 35);
    }

    for (int y = 40; y < TFT_H; y += 20)
    {
        tft.drawNumber(y, 2, y);
    }

    delay(2000);
}

// -----------------------------------------------------------------------------
// TEST 18 - Full screen random noise
// -----------------------------------------------------------------------------

void testNoise()
{
    title("RANDOM NOISE");

    for (int y = 30; y < TFT_H; y++)
    {
        for (int x = 0; x < TFT_W; x++)
        {
            tft.drawPixel(
                x,
                y,
                random(0xFFFF));
        }
    }

    delay(1000);
}

// -----------------------------------------------------------------------------
// TEST 19 - Color mixing
// -----------------------------------------------------------------------------

void testColorMix()
{
    title("COLOR MIX");

    for (int y = 30; y < TFT_H; y++)
    {
        uint8_t r = map(y, 30, TFT_H - 1, 0, 255);
        uint8_t g = 255 - r;

        for (int x = 0; x < TFT_W; x++)
        {
            uint8_t b =
                map(x, 0, TFT_W - 1, 0, 255);

            tft.drawPixel(
                x,
                y,
                tft.color565(r, g, b));
        }
    }

    delay(2000);
}

// -----------------------------------------------------------------------------
// TEST 20 - Rotation test
// -----------------------------------------------------------------------------

void testRotation()
{
    for (int rotation = 0; rotation < 4; rotation++)
    {
        tft.setRotation(rotation);

        tft.fillScreen(TFT_BLACK);

        tft.setTextColor(TFT_WHITE);
        tft.setTextSize(2);

        tft.drawString(
            "ROTATION " + String(rotation),
            10,
            10);

        tft.drawRect(
            0,
            0,
            tft.width(),
            tft.height(),
            TFT_RED);

        tft.drawLine(
            0,
            0,
            tft.width() - 1,
            tft.height() - 1,
            TFT_GREEN);

        tft.drawLine(
            0,
            tft.height() - 1,
            tft.width() - 1,
            0,
            TFT_BLUE);

        tft.fillCircle(
            tft.width() / 2,
            tft.height() / 2,
            30,
            TFT_YELLOW);

        delay(1200);
    }

    // Return to portrait
    tft.setRotation(0);
}

// -----------------------------------------------------------------------------
// TEST 21 - Moving objects / refresh test
// -----------------------------------------------------------------------------

void testAnimation()
{
    title("ANIMATION");

    for (int frame = 0; frame < 120; frame++)
    {
        tft.fillScreen(TFT_BLACK);

        int x =
            map(frame, 0, 119, 10, TFT_W - 11);

        int y =
            TFT_H / 2 +
            sin(frame * 0.15) * 80;

        tft.fillCircle(
            x,
            y,
            15,
            TFT_CYAN);

        tft.drawCircle(
            x,
            y,
            20,
            TFT_WHITE);

        delay(16);
    }
}

// -----------------------------------------------------------------------------
// SETUP
// -----------------------------------------------------------------------------

void setup()
{
    Serial.begin(115200);

    randomSeed(analogRead(0));

    tft.init();

    tft.setRotation(0);

    tft.fillScreen(TFT_BLACK);

    Serial.println();
    Serial.println("==============================");
    Serial.println("   TFT_eSPI DISPLAY TEST");
    Serial.println("==============================");
    Serial.println("Resolution: 240 x 320");
    Serial.println();
}

// -----------------------------------------------------------------------------
// LOOP
// -----------------------------------------------------------------------------

void loop()
{
    testSolidColors();

    testColorBars();

    testGrayscale();

    testGradients();

    testCheckerboard();

    testLines();

    testRectangles();

    testFilledRectangles();

    testCircles();

    testTriangles();

    testText();

    testTextBackground();

    testBorder();

    testPixels();

    testFillSpeed();

    testInversion();

    testGrid();

    testColorMix();

    testRotation();

    testAnimation();

    testNoise();

    Serial.println("Full TFT test cycle completed.");
}