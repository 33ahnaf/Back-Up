# SmartPen — IMU-Only Handwriting Tracker (ESP32-S3)

A standalone smart pen built on a Seeed Studio **XIAO ESP32-S3** and an
**MPU6050** 6-axis IMU. It reconstructs 2D pen motion from raw accelerometer
and gyroscope data alone (no camera, no digitizer tablet, no magnetometer),
streams it over its own Wi-Fi access point, and draws it live on an HTML5
canvas in any browser — entirely offline.

> **On accuracy:** IMU-only handwriting reconstruction is fundamentally
> limited by double-integration drift — this project pushes every
> reasonable software technique (calibration, sensor fusion, filtering,
> ZUPT, damping) to make a few seconds of legible motion reconstruction
> possible, not to defeat physics. Expect drift to accumulate over longer
> sessions; that's the nature of the sensor, not a bug in the pipeline.

---

## 1. Hardware

| Part | Notes |
|---|---|
| Seeed Studio XIAO ESP32-S3 | Main MCU, runs the whole pipeline + Wi-Fi AP |
| MPU6050 | 6-axis IMU (accel + gyro), connected over I2C |

### Wiring

```
MPU6050        XIAO ESP32-S3
-------        -------------
VCC     ---->  3V3
GND     ---->  GND
SCL     ---->  GPIO6  (D5)
SDA     ---->  GPIO5  (D4)
AD0     ---->  GND     (sets I2C address to 0x68)
```

Add 4.7kΩ pull-up resistors on SDA/SCL to 3.3V if your particular MPU6050
breakout board doesn't already have them on-board (most common breakout
boards do).

---

## 2. Building & flashing

This is a standard PlatformIO project.

```bash
# from the SmartPen/ directory
pio run                 # compile
pio run -t upload       # flash firmware
pio run -t uploadfs     # upload the web UI (data/) to LittleFS
pio device monitor      # open serial monitor (115200 baud)
```

Both `upload` and `uploadfs` are required the first time — `uploadfs` only
needs to be repeated if you change files under `data/`.

---

## 3. First run

1. Power the board. On boot it will ask you to hold the pen still for
   calibration (~2 seconds) — watch the Serial monitor for
   `Calibrating... hold the pen still and flat.`
2. Once calibration finishes, the device starts its Wi-Fi access point:
   - **SSID:** `SmartPen`
   - **Password:** `12345678`
3. Connect your phone/laptop to that network, then browse to the IP printed
   on Serial (typically `http://192.168.4.1`).
4. Start writing in the air. Hold the pen still for the "pen up"
   proxy to kick in between strokes (see §5.3).

### Serial commands (while connected via `pio device monitor`)

| Key | Action |
|---|---|
| `c` | Force a fresh calibration (hold the pen still first) |
| `r` | Reset integrated position back to canvas center |
| `d` | Toggle verbose per-sample debug printing |

---

## 4. Project structure

```
SmartPen/
├── platformio.ini
├── src/
│   ├── main.cpp        # setup()/loop(), serial commands, wiring modules together
│   ├── MPU6050.cpp      # register-level I2C driver
│   ├── Madgwick.cpp     # hand-written Madgwick AHRS orientation filter
│   ├── Filters.cpp      # (header-only; see include/Filters.h)
│   ├── Tracker.cpp      # the full sensor -> position pipeline
│   └── WiFiServer.cpp   # AP mode + LittleFS + WebSocket streaming
├── include/
│   ├── Config.h         # every tunable constant, in one place
│   ├── MPU6050.h
│   ├── Madgwick.h
│   ├── Filters.h
│   ├── Tracker.h
│   └── WiFiServer.h
├── data/                # served from LittleFS, this is the browser UI
│   ├── index.html
│   ├── style.css
│   └── app.js
└── README.md
```

(`Filters.h` is header-only — all filters are small enough as templated /
inline functions that a matching `.cpp` would just add link overhead for no
benefit. Every other module keeps a clean header/implementation split.)

---

## 5. How the pipeline works

The full chain, matching the project's original spec exactly:

```
Raw MPU6050 → Calibration → Bias Removal → Madgwick Filter → Orientation →
Gravity Compensation → Low-Pass Filter → High-Pass Filter → Dead-Zone Filter →
Velocity Integration → Velocity Damping → Position Integration → ZUPT →
Scaling → WebSocket → Browser Canvas
```

### 5.1 Calibration (`Tracker::calibrate`)

At startup (and on-demand via the `c` serial command), the firmware
averages ~400 samples (~2s at 200Hz) while the pen is held still:

- **Gyro bias** — averaged directly. A stationary gyro should read exactly
  0°/s on every axis; whatever it actually reads is pure bias, subtracted
  from every future sample.
- **Accelerometer** — the averaged vector is **not** treated as a bias to
  subtract. At rest it's overwhelmingly the gravity vector, and gravity is
  exactly the reference signal the Madgwick filter needs to correct gyro
  drift. Instead, it's used once to fast-forward the orientation filter's
  convergence (a short "warm-up burst" of updates using that gravity vector
  with zero gyro input), so the pen starts already knowing which way is
  "down" instead of drifting into the right orientation over its first few
  real seconds of use.

Gyro bias is also persisted to flash (ESP32 NVS/Preferences), so a quick
power cycle doesn't force a full recalibration — though recalibrating after
any temperature change or bump is still recommended.

### 5.2 Sensor fusion (`Madgwick.cpp`)

A hand-implemented version of Sebastian Madgwick's gradient-descent
orientation filter (IMU-only variant, no magnetometer). Each update:

1. Integrates the gyroscope to predict the new orientation quaternion
   (accurate over milliseconds, drifts over seconds).
2. Computes the gradient of the error between "gravity direction implied by
   the current orientation estimate" and "gravity direction actually
   measured by the accelerometer", and nudges the quaternion against that
   gradient. This is what continuously corrects gyro drift using gravity as
   a reference.
3. Re-normalizes the quaternion (floating-point integration drifts off the
   unit sphere every step otherwise).

The correction strength is `Config::MADGWICK_BETA` — higher trusts the
accelerometer more (faster correction, noisier), lower trusts the gyro more
(smoother, slower to correct).

### 5.3 Gravity compensation & filtering (`Tracker::update`)

Measured acceleration is rotated from the sensor's body frame into the
world frame using the current orientation quaternion, then the world "up"
gravity component (+1g) is subtracted — what's left is the linear
acceleration the pen actually experienced.

That signal then passes through:
- **Outlier rejection** — holds the last good value if a sample jumps
  implausibly (I2C glitch protection).
- **Low-pass filter** (8Hz cutoff) — removes noise/vibration above the
  frequency range real handwriting motion lives in.
- **Dead-zone** — snaps small residual values to exactly zero, which is
  what stops a resting pen from slowly "creeping" across the canvas.

### 5.4 Integration & drift reduction

- **Velocity integration**: `v += a·dt` every sample, using the *actual*
  measured `dt` (not an assumed constant), since real loop timing jitters.
- **Velocity damping**: every step, velocity is multiplied by `0.985`. This
  is the single biggest lever against runaway drift — without it, any tiny
  residual bias integrates into a velocity that never returns to zero on
  its own.
- **Velocity clamping**: hard ceiling on velocity magnitude, guarding
  against a single bad sample spiking the integrator.
- **High-pass filter on velocity** (0.3Hz cutoff): bleeds off slow,
  near-constant drift that survives damping, without fighting genuine
  slower strokes.
- **Zero-Velocity Update (ZUPT)**: a rolling window classifies the pen as
  "stationary" once acceleration deviation and gyro magnitude both stay
  below threshold for ~60ms straight. While stationary, velocity is forced
  to exactly zero. This is what keeps position from wandering during
  pauses between strokes/words.
- **Position integration**: `p += v·dt`.

### 5.5 Pen up/down proxy

There's no physical tip-contact switch on IMU-only hardware, so
"stationary" doubles as the pen-lift signal: while the ZUPT detector says
the pen isn't moving, the browser treats it as "pen up" and starts a new
stroke on the next motion, instead of drawing one continuous scribble
connecting every pause. It's an approximation, not a real button — but the
best proxy available without extra hardware.

### 5.6 Scaling & transport

Position (in meters) is multiplied by `Config::POSITION_TO_PIXELS` to get
canvas pixels, then streamed as compact JSON over a WebSocket at 60Hz
(decoupled from the 200Hz IMU sampling rate — the browser only needs
updates as fast as it can render, the integrator needs the full rate to
keep `dt` small).

```json
{"x":120.4,"y":-88.1,"pen":1,"vx":0.021,"vy":-0.004,"stationary":0,"dt":5012}
```

---

## 6. Tuning

Every constant that affects tracking behavior lives in `include/Config.h`
with a comment explaining what it does and why its default was chosen.
Reasonable things to try tweaking:

- `POSITION_TO_PIXELS` — bigger for larger on-screen strokes from smaller
  real-world hand motion.
- `MADGWICK_BETA` — raise if orientation feels laggy correcting drift,
  lower if it feels jittery.
- `VELOCITY_DAMPING` — closer to `1.0` lets strokes travel further before
  snapping back; further from `1.0` fights drift more aggressively at the
  cost of shorter/smaller apparent strokes.
- `STATIONARY_*` thresholds — loosen if ZUPT is falsely triggering during
  genuine slow, careful writing; tighten if the pen keeps "creeping" at
  rest.

---

## 7. Known limitations (by design, not oversights)

- **Yaw is unobservable.** Without a magnetometer, absolute heading can't
  be determined — only relative orientation from the calibration reference
  point. This doesn't affect the pen-tip trajectory reconstruction, since
  we only need relative motion, not absolute compass heading.
- **Drift accumulates over time.** Every mitigation here (ZUPT, damping,
  high-pass, dead-zone) reduces drift, none eliminate it — that's a
  fundamental limit of double-integrating noisy acceleration, not something
  more filtering can fully solve.
- **"Pen up/down" is inferred, not sensed.** See §5.5.
