#!/usr/bin/python3

import sys
import serial
import keyboard

def parse(fn):
    left = ""
    right = ""
    with open(fn, "r") as fp:
        line = fp.readline()
        while line != "":
            if line.startswith("left"):
                left = line.split('=')[1]
            elif line.startswith("right"):
                right = line.split("=")[1]

            line = fp.readline()

    return (left[:-1], right[:-1])

def main(argc, argv):
    left = ""
    right = ""
    if argc < 2:
        (left, right) = parse("./default.cfg")
    else:
        (left, right) = parse(argv[1])

    ser = serial.Serial("/dev/ttyACM0", 9600)
    running = True
    while running:
        resp = ''
        if ser.in_waiting:
            resp = ser.read().decode()

        if resp == 'l':
            keyboard.send(left)
        elif resp == 'r':
            keyboard.send(right)

if __name__ == "__main__":
    main(len(sys.argv), sys.argv)
