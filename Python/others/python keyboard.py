import serial
import threading
import time
import pyautogui

COM_PORT = 'COM4'  # Change this to your COM port
BAUD_RATE = 9600  # Change this to your baud rate




def simulate_keyboard_w_down():
    pyautogui.keyDown("w")


def simulate_keyboard_a_down():
    pyautogui.keyDown("a")


def simulate_keyboard_s_down():
    pyautogui.keyDown("s")


def simulate_keyboard_d_down():
    pyautogui.keyDown("d")


def simulate_keyboard_w_up():
    pyautogui.keyUp("w")


def simulate_keyboard_a_up():
    pyautogui.keyUp("a")


def simulate_keyboard_s_up():
    pyautogui.keyUp("s")


def simulate_keyboard_d_up():
    pyautogui.keyUp("d")


def simulate_keyboard_space_down():
    pyautogui.keyDown("space")


def simulate_keyboard_space_up():
    pyautogui.keyUp("space")


def simulate_keyboard_shift_down():
    pyautogui.keyDown("shift")


def simulate_keyboard_shift_up():
    pyautogui.keyUp("shift")


def simulate_keyboard_ctrl_down():
    pyautogui.keyDown("ctrl")


def simulate_keyboard_ctrl_up():
    pyautogui.keyUp("ctrl")


def listen_serial():
    with serial.Serial(COM_PORT, BAUD_RATE) as ser:
        while True:
            data = ser.readline().decode().strip()
            if data == "w_key_on":
                threading.Thread(target=simulate_keyboard_w_down).start()

            if data == "a_key_on":
                threading.Thread(target=simulate_keyboard_a_down).start()

            if data == "s_key_on":
                threading.Thread(target=simulate_keyboard_s_down).start()

            if data == "d_key_on":
                threading.Thread(target=simulate_keyboard_d_down).start()

            if data == "w_key_off":
                threading.Thread(target=simulate_keyboard_w_up).start()

            if data == "a_key_off":
                threading.Thread(target=simulate_keyboard_a_up).start()

            if data == "s_key_off":
                threading.Thread(target=simulate_keyboard_s_up).start()

            if data == "d_key_off":
                threading.Thread(target=simulate_keyboard_d_up).start()

            if data == "space_key_on":
                threading.Thread(target=simulate_keyboard_space_down).start()

            if data == "space_key_off":
                threading.Thread(target=simulate_keyboard_space_up).start()

            if data == "shift_key_on":
                threading.Thread(target=simulate_keyboard_shift_down).start()

            if data == "shift_key_off":
                threading.Thread(target=simulate_keyboard_shift_up).start()

            if data == "ctrl_key_on":
                threading.Thread(target=simulate_keyboard_ctrl_down).start()

            if data == "ctrl_key_off":
                threading.Thread(target=simulate_keyboard_ctrl_up).start()



if __name__ == "__main__":
    listen_serial()
