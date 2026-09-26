import serial
import time

PORT = "/dev/ttyUSB0"      # Change if needed
BAUD = 250000

FLASH_SIZE = 16 * 1024 * 1024
BLOCK_SIZE = 256

print("Opening serial...")

ser = serial.Serial(PORT, BAUD, timeout=10)

time.sleep(2)

print("Starting dump...")

ser.reset_input_buffer()
ser.write(b'x')

received = 0
start = time.time()

with open("flash.bin", "wb") as f:

    while received < FLASH_SIZE:

        data = ser.read(BLOCK_SIZE)

        if len(data) != BLOCK_SIZE:
            print("\nERROR")
            print("Expected:", BLOCK_SIZE)
            print("Received:", len(data))
            break

        f.write(data)

        received += BLOCK_SIZE

        if received % (64 * 1024) == 0:
            elapsed = time.time() - start
            speed = received / elapsed / 1024

            print(
                f"\r{received}/{FLASH_SIZE} "
                f"({received*100/FLASH_SIZE:.1f}%) "
                f"{speed:.1f} KiB/s",
                end=""
            )

print()

ser.close()

print("Finished.")