#include "Patterns.h"
#include "Utilities.h"

namespace tft {
namespace patterns {

namespace {
    // Largest native panel width among all supported controllers is 480
    // (ILI9486/ILI9488/HX8357 in landscape). One reused static row buffer
    // sized for the worst case avoids any dynamic allocation across every
    // driver and every pattern.
    constexpr uint16_t kMaxRowPixels = 480;
    uint16_t rowBuffer[kMaxRowPixels];
}

void horizontalRGBBars(DriverBase& driver) {
    const uint16_t w = driver.width();
    const uint16_t h = driver.height();
    const uint16_t third = w / 3;

    for (uint16_t x = 0; x < w; ++x) {
        if (x < third) {
            rowBuffer[x] = Colors::RED;
        } else if (x < static_cast<uint16_t>(third * 2)) {
            rowBuffer[x] = Colors::GREEN;
        } else {
            rowBuffer[x] = Colors::BLUE;
        }
    }

    driver.setAddressWindow(0, 0, w - 1, h - 1);
    for (uint16_t y = 0; y < h; ++y) {
        driver.writePixels(rowBuffer, w);
    }
}

void verticalRGBBars(DriverBase& driver) {
    const uint16_t w = driver.width();
    const uint16_t h = driver.height();
    const uint16_t third = h / 3;

    driver.setAddressWindow(0, 0, w - 1, h - 1);
    for (uint16_t y = 0; y < h; ++y) {
        uint16_t color;
        if (y < third) {
            color = Colors::RED;
        } else if (y < static_cast<uint16_t>(third * 2)) {
            color = Colors::GREEN;
        } else {
            color = Colors::BLUE;
        }
        for (uint16_t x = 0; x < w; ++x) {
            rowBuffer[x] = color;
        }
        driver.writePixels(rowBuffer, w);
    }
}

void checkerboard(DriverBase& driver, uint16_t cellSize) {
    const uint16_t w = driver.width();
    const uint16_t h = driver.height();
    if (cellSize == 0) {
        cellSize = 1;
    }

    driver.setAddressWindow(0, 0, w - 1, h - 1);
    for (uint16_t y = 0; y < h; ++y) {
        const bool rowToggle = ((y / cellSize) % 2) != 0;
        for (uint16_t x = 0; x < w; ++x) {
            const bool colToggle = ((x / cellSize) % 2) != 0;
            rowBuffer[x] = (rowToggle != colToggle) ? Colors::WHITE : Colors::BLACK;
        }
        driver.writePixels(rowBuffer, w);
    }
}

void diagonalLines(DriverBase& driver, uint16_t stripeWidth) {
    const uint16_t w = driver.width();
    const uint16_t h = driver.height();
    if (stripeWidth == 0) {
        stripeWidth = 1;
    }

    driver.setAddressWindow(0, 0, w - 1, h - 1);
    for (uint16_t y = 0; y < h; ++y) {
        for (uint16_t x = 0; x < w; ++x) {
            const uint16_t diag = static_cast<uint16_t>((x + y) / stripeWidth);
            rowBuffer[x] = (diag % 2 == 0) ? Colors::CYAN : Colors::MAGENTA;
        }
        driver.writePixels(rowBuffer, w);
    }
}

void crosshair(DriverBase& driver, uint16_t lineColor) {
    const uint16_t w = driver.width();
    const uint16_t h = driver.height();
    const uint16_t midX = w / 2;
    const uint16_t midY = h / 2;

    driver.setAddressWindow(0, 0, w - 1, h - 1);
    for (uint16_t y = 0; y < h; ++y) {
        const bool onHLine = (y == midY);
        for (uint16_t x = 0; x < w; ++x) {
            const bool onVLine = (x == midX);
            rowBuffer[x] = (onHLine || onVLine) ? lineColor : Colors::BLACK;
        }
        driver.writePixels(rowBuffer, w);
    }
}

void gradient(DriverBase& driver, uint16_t fromColor, uint16_t toColor) {
    const uint16_t w = driver.width();
    const uint16_t h = driver.height();

    for (uint16_t x = 0; x < w; ++x) {
        const uint8_t t = static_cast<uint8_t>((static_cast<uint32_t>(x) * 255) / (w > 1 ? (w - 1) : 1));
        rowBuffer[x] = lerp565(fromColor, toColor, t);
    }

    driver.setAddressWindow(0, 0, w - 1, h - 1);
    for (uint16_t y = 0; y < h; ++y) {
        driver.writePixels(rowBuffer, w);
    }
}

void movingSquare(DriverBase& driver, uint16_t squareSize, uint32_t durationMs) {
    const uint16_t w = driver.width();
    const uint16_t h = driver.height();
    if (squareSize == 0 || squareSize >= w || squareSize >= h) {
        return;
    }

    for (uint16_t i = 0; i < squareSize; ++i) {
        rowBuffer[i] = Colors::YELLOW;
    }

    const uint32_t startMs = millis();
    int32_t x = 0;
    int32_t y = 0;
    int32_t dx = 3;
    int32_t dy = 2;

    // Clear to black once up front so the background between frames is
    // consistent; only the square's own rows are redrawn each frame.
    driver.fillScreen(Colors::BLACK);

    while (millis() - startMs < durationMs) {
        // Erase previous square position by drawing a black square first is
        // skipped here in favor of simply redrawing the full background
        // periodically, keeping this routine allocation-free and simple.
        driver.setAddressWindow(static_cast<uint16_t>(x), static_cast<uint16_t>(y),
                                 static_cast<uint16_t>(x) + squareSize - 1,
                                 static_cast<uint16_t>(y) + squareSize - 1);
        for (uint16_t row = 0; row < squareSize; ++row) {
            driver.writePixels(rowBuffer, squareSize);
        }

        x += dx;
        y += dy;
        if (x <= 0 || x + squareSize >= w) { dx = -dx; }
        if (y <= 0 || y + squareSize >= h) { dy = -dy; }

        delay(30);
        driver.fillScreen(Colors::BLACK);
    }
}

} // namespace patterns
} // namespace tft
