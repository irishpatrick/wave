#!/usr/bin/python3

import sys
import serial
import keyboard

    def main(argc, argv):
    ser = serial.Serial("/dev/ttyACM0", 9600)
    running = True
    while running:
        resp = ''
        if ser.in_waiting:
            resp = ser.read().decode()

        if resp == 'l':
            keyboard.send("ctrl+windows+left")
        elif resp == 'r':
            keyboard.send("ctrl+windows+right")

if __name__ == "__main__":
    main(len(sys.argv), sys.argv)
