#!/usr/bin/env python3
"""View JPEG frames streamed over USB CDC from main_usb_stream.cpp."""

from __future__ import annotations

import argparse
import os
import struct
import sys
import time
from pathlib import Path
from datetime import datetime

import cv2
import numpy as np
import serial
from serial.tools import list_ports

FRAME_MAGIC = b"\xCA\xFE"

RESOLUTION_KEYS = {
    ord("1"): "qqvga",
    ord("2"): "qvga",
    ord("3"): "vga",
    ord("4"): "svga",
    ord("5"): "xga",
    ord("6"): "hd",
    ord("7"): "sxga",
    ord("8"): "uxga",
}


def list_candidate_ports() -> list[str]:
    ports: list[str] = []
    for port in list_ports.comports():
        text = f"{port.device} {port.description} {port.manufacturer}".lower()
        if any(h in text for h in ("xiao", "esp32", "usb", "serial", "jtag", "acm")):
            ports.append(port.device)
    return ports


def read_text_responses(ser: serial.Serial, timeout: float = 0.4) -> list[str]:
    """Read printable ASCII lines only. Never decode binary frame data."""
    lines: list[str] = []
    buf = bytearray()
    deadline = time.time() + timeout

    while time.time() < deadline:
        waiting = ser.in_waiting
        if waiting:
            chunk = ser.read(waiting)
            for byte in chunk:
                if byte in (0x0A, 0x0D):
                    if buf:
                        try:
                            line = buf.decode("ascii")
                        except UnicodeDecodeError:
                            buf.clear()
                            continue
                        if line.strip():
                            lines.append(line.strip())
                        buf.clear()
                elif 0x20 <= byte <= 0x7E:
                    buf.append(byte)
                else:
                    buf.clear()
            deadline = time.time() + 0.05
        else:
            time.sleep(0.01)

    if buf:
        try:
            line = buf.decode("ascii")
            if line.strip():
                lines.append(line.strip())
        except UnicodeDecodeError:
            pass

    return lines


def send_cmd(ser: serial.Serial, cmd: str, wait: float = 0.15) -> list[str]:
    ser.write((cmd.strip() + "\n").encode("ascii"))
    ser.flush()
    time.sleep(wait)
    return read_text_responses(ser, timeout=0.35)


def probe_port(port: str, baud: int) -> bool:
    try:
        with serial.Serial(port, baud, timeout=0.5) as ser:
            time.sleep(0.4)
            ser.reset_input_buffer()
            replies = send_cmd(ser, "status", wait=0.2)
            joined = "\n".join(replies)
            return "OK status" in joined or "OK waiting for start" in joined
    except (OSError, serial.SerialException):
        return False


def find_board_port(baud: int) -> str | None:
    candidates = list_candidate_ports()
    for port in candidates:
        if probe_port(port, baud):
            return port

    # Fallback: try common Linux device names if list_ports missed one.
    for port in ("/dev/ttyACM0", "/dev/ttyACM1", "/dev/ttyUSB0"):
        if os.path.exists(port) and port not in candidates and probe_port(port, baud):
            return port
    return None


def check_gui_available() -> None:
    if sys.platform.startswith("linux") and not os.environ.get("DISPLAY"):
        raise RuntimeError(
            "No DISPLAY set. Run from a desktop session, or use SSH with X forwarding."
        )

    try:
        cv2.namedWindow("__gui_test__", cv2.WINDOW_NORMAL)
        cv2.destroyWindow("__gui_test__")
    except cv2.error as exc:
        raise RuntimeError(
            "OpenCV window support is missing. "
            "Install the full package: pip install opencv-python"
        ) from exc


def read_exact(ser: serial.Serial, size: int) -> bytes:
    buf = bytearray()
    while len(buf) < size:
        chunk = ser.read(size - len(buf))
        if not chunk:
            raise TimeoutError("serial read timeout")
        buf.extend(chunk)
    return bytes(buf)


def sync_header(ser: serial.Serial) -> None:
    window = bytearray()
    while True:
        byte = ser.read(1)
        if not byte:
            raise TimeoutError("serial read timeout while syncing frame")
        window.append(byte[0])
        if len(window) > 2:
            window.pop(0)
        if bytes(window) == FRAME_MAGIC:
            return


def read_frame(ser: serial.Serial) -> tuple[np.ndarray, int, int]:
    sync_header(ser)
    length, width, height, _reserved = struct.unpack("<IHHH", read_exact(ser, 10))
    if length < 2 or length > 2_000_000:
        raise ValueError(f"implausible frame length: {length}")
    jpeg = read_exact(ser, length)
    img = cv2.imdecode(np.frombuffer(jpeg, dtype=np.uint8), cv2.IMREAD_COLOR)
    if img is None:
        raise ValueError("jpeg decode failed")
    return img, width, height


def print_device_lines(lines: list[str]) -> None:
    for line in lines:
        if line.startswith(("OK", "ERR", "CMD")):
            print(f"[device] {line}")


def main() -> int:
    parser = argparse.ArgumentParser(description="ESP32-S3 USB camera viewer")
    parser.add_argument("-p", "--port", help="Serial port (auto-detect if omitted)")
    parser.add_argument("--baud", type=int, default=2000000)
    parser.add_argument("--res", default="vga", help="Initial resolution")
    parser.add_argument("--quality", type=int, default=12)
    parser.add_argument("--fps-delay", type=int, default=50, help="Frame delay in ms")
    parser.add_argument("--list-ports", action="store_true", help="List candidate ports")
    args = parser.parse_args()

    if args.list_ports:
        for port in list_candidate_ports():
            ok = probe_port(port, args.baud)
            print(f"{port}\t{'OK' if ok else 'no response'}")
        return 0

    try:
        check_gui_available()
    except RuntimeError as exc:
        print(exc, file=sys.stderr)
        return 1

    port = args.port
    if port and not probe_port(port, args.baud):
        print(
            f"Port {port} did not respond to status. "
            "Try --list-ports or the other /dev/ttyACM* device.",
            file=sys.stderr,
        )
        return 1

    if not port:
        port = find_board_port(args.baud)
    if not port:
        print(
            "Could not find the camera serial port.\n"
            "Run: python tools/usb_viewer.py --list-ports\n"
            "Then pass the working port with -p /dev/ttyACM0",
            file=sys.stderr,
        )
        return 1

    print(f"Using {port}")
    ser = serial.Serial(port, args.baud, timeout=2)
    time.sleep(0.5)
    ser.reset_input_buffer()

    print_device_lines(read_text_responses(ser, timeout=0.6))
    print_device_lines(send_cmd(ser, "stop"))
    print_device_lines(send_cmd(ser, f"res {args.res}"))
    print_device_lines(send_cmd(ser, f"quality {args.quality}"))
    print_device_lines(send_cmd(ser, f"fps {args.fps_delay}"))
    print_device_lines(send_cmd(ser, "start"))

    win = "ESP32-S3 USB Camera"
    cv2.namedWindow(win, cv2.WINDOW_NORMAL)
    print("Keys: 1-8 resolution, +/- quality, [/] fps delay, space pause, q quit")

    paused = False
    recording=False
    video_writer=None
    record_dir=Path("recordings")
    shot_dir=Path("screenshots")
    record_dir.mkdir(exist_ok=True)
    shot_dir.mkdir(exist_ok=True)
    fps=20.0
    last=time.time()

    try:
        while True:
            if not paused:
                try:
                    img, width, height = read_frame(ser)
                    now=time.time()
                    dt=now-last
                    last=now
                    if dt>0: fps=0.9*fps+0.1*(1.0/dt)
                    display=img.copy()
                    cv2.putText(display,f"{fps:.1f} FPS",(10,25),cv2.FONT_HERSHEY_SIMPLEX,0.7,(0,255,0),2)
                    if recording:
                        cv2.putText(display,"REC",(10,55),cv2.FONT_HERSHEY_SIMPLEX,0.7,(0,0,255),2)
                        video_writer.write(img)
                    cv2.setWindowTitle(win, f"{width}x{height} | {port}")
                    cv2.imshow(win, display)
                except (TimeoutError, ValueError) as exc:
                    print(f"Frame error: {exc}", file=sys.stderr)
                    ser.reset_input_buffer()
                    if not paused:
                        print_device_lines(send_cmd(ser, "start"))
                    continue

            key = cv2.waitKey(1) & 0xFF
            if key in (ord("q"), 27):
                break
            if key == ord(" "):
                paused = not paused
                print_device_lines(send_cmd(ser, "stop" if paused else "start"))
            elif key in RESOLUTION_KEYS:
                print_device_lines(send_cmd(ser, f"res {RESOLUTION_KEYS[key]}"))
            elif key in (ord("+"), ord("=")):
                print_device_lines(send_cmd(ser, "quality 8"))
            elif key == ord("-"):
                print_device_lines(send_cmd(ser, "quality 20"))
            elif key == ord("["):
                print_device_lines(send_cmd(ser, "fps 80"))
            elif key == ord("]"):
                print_device_lines(send_cmd(ser, "fps 20"))
            elif key in (ord("r"),ord("R")):
                if not recording:
                    fn=record_dir/f"{datetime.now():%Y-%m-%d_%H-%M-%S}.mp4"
                    vw=cv2.VideoWriter(str(fn),cv2.VideoWriter_fourcc(*"mp4v"),max(fps,1.0),(img.shape[1],img.shape[0]))
                    if vw.isOpened():
                        video_writer=vw
                        recording=True
                        print("Recording:",fn)
                else:
                    recording=False
                    if video_writer: video_writer.release(); video_writer=None
            elif key in (ord("s"),ord("S")):
                fn=shot_dir/f"{datetime.now():%Y-%m-%d_%H-%M-%S}.png"
                cv2.imwrite(str(fn),img)
                print("Saved",fn)
    finally:
        send_cmd(ser, "stop")
        
        if video_writer is not None:
            video_writer.release()
        ser.close()
        cv2.destroyAllWindows()

    return 0


if __name__ == "__main__":
    raise SystemExit(main())