#include <Arduino.h>
#include <TFT_eSPI.h>

TFT_eSPI tft = TFT_eSPI();

#define BAUD_RATE 2000000

#define SYNC1 0xAA
#define SYNC2 0x55

#define ACK  0x06
#define NACK 0x15

uint8_t buffer[1024];

// ============================================================
// Read exactly N bytes
// ============================================================

bool readExact(uint8_t *buf, size_t len)
{
    size_t received = 0;

    while (received < len)
    {
        if (Serial.available())
        {
            size_t n = Serial.read(
                buf + received,
                len - received
            );

            received += n;
        }

        yield();
    }

    return true;
}

// ============================================================
// Read 16-bit big endian
// ============================================================

uint16_t read16()
{
    uint8_t b[2];

    readExact(b, 2);

    return ((uint16_t)b[0] << 8) | b[1];
}

// ============================================================
// Wait for AA 55
// ============================================================

void waitForSync()
{
    uint8_t state = 0;

    while (true)
    {
        if (!Serial.available())
        {
            yield();
            continue;
        }

        uint8_t b = Serial.read();

        if (state == 0)
        {
            if (b == SYNC1)
            {
                state = 1;
            }
        }
        else
        {
            if (b == SYNC2)
            {
                return;
            }

            if (b == SYNC1)
            {
                state = 1;
            }
            else
            {
                state = 0;
            }
        }
    }
}

// ============================================================
// Receive image
// ============================================================

void receiveImage()
{
    Serial.println("SYNC OK");

    // -------------------------
    // Read dimensions
    // -------------------------

    uint16_t width = read16();
    uint16_t height = read16();

    Serial.printf(
        "HEADER: %u x %u\n",
        width,
        height
    );

    // -------------------------
    // Validate
    // -------------------------

    if (width == 0 ||
        height == 0 ||
        width > 320 ||
        height > 320)
    {
        Serial.println("BAD HEADER");

        Serial.write(NACK);
        Serial.flush();

        return;
    }

    // -------------------------
    // ACK header
    // -------------------------

    Serial.println("SENDING ACK");

    Serial.write(ACK);
    Serial.flush();

    Serial.println("ACK SENT");

    // -------------------------
    // Receive pixels
    // -------------------------

    uint32_t totalPixels =
        (uint32_t)width * height;

    uint32_t receivedPixels = 0;

    Serial.printf(
        "EXPECTING %lu PIXELS\n",
        totalPixels
    );

    // Start TFT transaction
    tft.startWrite();

    tft.setAddrWindow(
        0,
        0,
        width,
        height
    );

    while (receivedPixels < totalPixels)
    {
        uint32_t remaining =
            totalPixels - receivedPixels;

        uint32_t pixels =
            min(
                remaining,
                (uint32_t)(sizeof(buffer) / 2)
            );

        size_t bytes =
            pixels * 2;

        readExact(
            buffer,
            bytes
        );

        tft.pushColors(
            (uint16_t *)buffer,
            pixels,
            true
        );

        receivedPixels += pixels;
    }

    tft.endWrite();

    Serial.println("IMAGE DONE");

    // Final ACK
    Serial.write(ACK);
    Serial.flush();

    Serial.println("DONE ACK SENT");
}

// ============================================================
// SETUP
// ============================================================

void setup()
{
    Serial.begin(BAUD_RATE);

    delay(1000);

    tft.init();
    tft.setRotation(0);

    tft.fillScreen(TFT_BLACK);

    Serial.println();
    Serial.println("==============================");
    Serial.println(" TFT IMAGE VIEWER");
    Serial.println("==============================");
    Serial.println("READY");
}

// ============================================================
// LOOP
// ============================================================

void loop()
{
    waitForSync();

    receiveImage();
}