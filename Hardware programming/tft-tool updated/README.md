# Universal SPI TFT Auto-Detection Tool

Diagnostic firmware for the ESP32-WROOM-32 that identifies an unknown SPI
TFT panel by cycling through initialization sequences for every commonly
used controller, rather than relying on a single compile-time driver
selection (as TFT_eSPI requires).

## Supported controllers

ILI9341, ILI9486, ILI9488, ST7735, ST7789, HX8357, GC9A01.

## Wiring

Only 5 signals are needed - **no MISO**:

| Signal | Default GPIO (edit in `src/main.cpp`) |
|--------|----------------------------------------|
| CS     | 5  |
| DC     | 2  |
| RST    | 4  (set to `-1` if RST is tied to 3V3/EN) |
| MOSI   | 23 |
| SCK    | 18 |

Edit the constants in the `pins` namespace at the top of `src/main.cpp` to
match your actual wiring.

### Not sure the wiring itself is right?

Enable `ENABLE_PIN_PERMUTATION_TEST` (see below) and the tool will also
cycle through every permutation of assigning those five GPIOs to the five
roles - 120 permutations if RST has a dedicated pin, or 24 if `pins::RST`
is `-1` (RST tied to 3V3/EN, so it's held fixed and only the remaining four
pins are shuffled). This finds a panel even if it's wired correctly but
*labelled* wrong - e.g. what you called `MOSI` is actually going into the
panel's `SCK` pin. The currently-active permutation (and its full pin
mapping) is always printed to Serial, numbered `k / total`, regardless of
whether `ENABLE_SERIAL_LOG` is also on.

## How it works

`SPIBus` is a thin, allocation-free wrapper over the ESP32 hardware SPI
peripheral (command/data byte writes, chip-select/DC control, a reusable
pixel-fill routine). Every controller driver (`src/drivers/*`) subclasses
`DriverBase` and supplies only its own register init sequence; address
window, rotation (MADCTL), color order, inversion, and fill logic are all
implemented once in `DriverBase` since that command set is shared across
essentially all SPI TFT controllers. `Display` then drives the test loop:

```
forever:
  for each pin permutation (just the one labelled config, unless
                             ENABLE_PIN_PERMUTATION_TEST is set):
    apply CS/DC/RST/MOSI/SCK to the bus, log "PERMUTATION k / total"
    for each driver:
      hardware reset -> initialize()
      for each enabled rotation (0-3):
        for each enabled color order (RGB, BGR):
          for each enabled inversion (OFF, ON):
            fill RED -> GREEN -> BLUE -> WHITE -> BLACK (200ms each)
            [optional pattern tests]
```

Whichever combination shows correct, non-garbled colors on your physical
panel tells you the pin assignment, controller, rotation, color order, and
inversion setting to use going forward.

## Build

```
pio run -e esp32dev -t upload
pio device monitor
```

## Compile-time flags (`platformio.ini` `build_flags`)

| Flag | Effect |
|------|--------|
| `ENABLE_SERIAL_LOG`    | Verbose serial banner + per-color logging |
| `ENABLE_ROTATION_TEST` | Sweep all 4 rotations (otherwise only rotation 0) |
| `ENABLE_BGR_TEST`      | Sweep RGB and BGR color order (otherwise only RGB) |
| `ENABLE_INVERT_TEST`   | Sweep inversion OFF/ON (otherwise only OFF) |
| `ENABLE_PATTERN_TESTS` | Also run bar/checkerboard/diagonal/crosshair/gradient/moving-square patterns after the solid-color sequence |
| `ENABLE_SLOW_SPI`      | Force 8 MHz SPI clock |
| `ENABLE_FAST_SPI`      | Force 40 MHz SPI clock |
| `ENABLE_PIN_PERMUTATION_TEST` | Also sweep all 120 (or 24, see above) permutations of the pin pool across CS/DC/RST/MOSI/SCK, logging which one is active on Serial. Forces Serial on even without `ENABLE_SERIAL_LOG` |

With no speed flag set, SPI defaults to 26 MHz - a safe middle ground for
auto-detection when wiring quality/length is unknown.

Note: with `ENABLE_PIN_PERMUTATION_TEST` on *and* every other sweep flag
also on, total coverage is 120 pin permutations x 7 drivers x 4 rotations x
2 color orders x 2 inversions - each taking a few seconds, so a full pass
can run for hours. Leave `ENABLE_ROTATION_TEST` / `ENABLE_BGR_TEST` /
`ENABLE_INVERT_TEST` off while pin-hunting to get through all 120
permutations quickly, then re-enable them once you've found the right
pins.

## Robustness

The loop never blocks on user input and never halts: there is no MISO line
to read status back from, so a missing/miswired panel simply results in
"nothing visibly happens" for that driver/combination rather than a hang or
crash, and the sweep moves on.
