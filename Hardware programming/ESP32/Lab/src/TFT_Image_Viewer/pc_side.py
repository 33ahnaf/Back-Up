import serial
import struct
import time
from PIL import Image

# ============================================================
# SETTINGS
# ============================================================

PORT = "/dev/ttyUSB0"
BAUD = 2000000

IMAGE_FILE = "image.jpg"

WIDTH = 240
HEIGHT = 320

# ============================================================
# CONNECT
# ============================================================

print(f"Opening {PORT}...")

ser = serial.Serial(
    PORT,
    BAUD,
    timeout=5
)

# Opening the serial port usually resets ESP32
print("Waiting for ESP32 to boot...")

time.sleep(2)

# Clear anything printed during boot
ser.reset_input_buffer()

print("ESP32 ready.")

# ============================================================
# LOAD IMAGE
# ============================================================

print(f"Loading {IMAGE_FILE}...")

image = Image.open(IMAGE_FILE)

image = image.convert("RGB")

image = image.resize(
    (WIDTH, HEIGHT)
)

print(
    f"Image size: {image.width}x{image.height}"
)

# ============================================================
# CONVERT RGB888 -> RGB565
# ============================================================

print("Converting to RGB565...")

data = bytearray()

# New Pillow API
for r, g, b in image.get_flattened_data():

    rgb565 = (
        ((r >> 3) << 11) |
        ((g >> 2) << 5) |
        (b >> 3)
    )

    data.append((rgb565 >> 8) & 0xFF)
    data.append(rgb565 & 0xFF)

print(
    f"RGB565 data: {len(data)} bytes"
)

# ============================================================
# SEND HEADER
# ============================================================

print("Sending image header...")

ser.write(b"\xAA\x55")

ser.write(
    struct.pack(
        ">HH",
        WIDTH,
        HEIGHT
    )
)

ser.flush()

# ============================================================
# WAIT FOR ACK
# ============================================================

print("Waiting for ESP32 ACK...")

ack = ser.read(1)

if ack != b"\x06":

    print(
        f"ERROR: Expected ACK, got: {ack!r}"
    )

    ser.close()

    raise RuntimeError(
        "ESP32 did not acknowledge image header"
    )

print("ESP32 accepted image.")

# ============================================================
# SEND IMAGE
# ============================================================

print("Sending image...")

start = time.perf_counter()

ser.write(data)

ser.flush()

elapsed = time.perf_counter() - start

print(
    f"Transfer finished in {elapsed:.3f} seconds"
)

print(
    f"Transfer speed: "
    f"{len(data) / elapsed / 1024:.1f} KiB/s"
)

# ============================================================
# WAIT FOR FINAL ACK
# ============================================================

print("Waiting for ESP32 to finish drawing...")

ack = ser.read(1)

if ack != b"\x06":

    print(
        f"WARNING: Expected final ACK, got {ack!r}"
    )

else:

    print("Image displayed successfully!")

ser.close()