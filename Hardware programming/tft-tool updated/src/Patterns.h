#pragma once
// ============================================================================
// Patterns
//
// Optional non-solid-color test patterns. Only compiled into the test loop
// when ENABLE_PATTERN_TESTS is defined (see platformio.ini / main.cpp) -
// by default the tool only cycles solid RED/GREEN/BLUE/WHITE/BLACK fills as
// specified. All patterns are drawn row-by-row through DriverBase::writePixels
// using a single reused static row buffer, so none of them allocate memory.
// ============================================================================

#include <Arduino.h>
#include "DriverBase.h"

namespace tft {
namespace patterns {

// Alternating vertical stripes of red/green/blue, one third of the screen
// width each.
void horizontalRGBBars(DriverBase& driver);

// Alternating horizontal stripes of red/green/blue, one third of the screen
// height each. (Named to mirror horizontalRGBBars: the bars themselves run
// horizontally across the panel.)
void verticalRGBBars(DriverBase& driver);

// Classic black/white checkerboard, cellSize pixels per square.
void checkerboard(DriverBase& driver, uint16_t cellSize = 20);

// Diagonal alternating-color stripes.
void diagonalLines(DriverBase& driver, uint16_t stripeWidth = 10);

// A centered crosshair (thin horizontal + vertical line) over a black
// background - useful for visually confirming address-window/offset
// correctness on a newly identified controller.
void crosshair(DriverBase& driver, uint16_t lineColor = 0xFFFF);

// Smooth left-to-right gradient between two colors.
void gradient(DriverBase& driver, uint16_t fromColor, uint16_t toColor);

// Animates a small filled square bouncing across the screen for
// `durationMs` milliseconds - a quick visual "is anything actually
// updating" sanity check.
void movingSquare(DriverBase& driver, uint16_t squareSize = 20, uint32_t durationMs = 2000);

} // namespace patterns
} // namespace tft
