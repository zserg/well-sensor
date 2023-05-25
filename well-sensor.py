import serial
import time
from flask import Flask, json, request
import re

ser = serial.Serial('/dev/ttyUSB0', 57600)  # open serial port
print(ser.name)         # check which port was really used

api = Flask(__name__)

@api.route('/status', methods=['GET'])
def get_status():
    led = request.args.get('led')
    return status(led)

def status(d):
    if d == '0' or d == '1':
        ser.write(bytes(d, 'utf-8'))
    else:
        ser.write(b'x')
    r = ser.read_until()
    return r.rstrip()


if __name__ == '__main__':
  api.run(host="0.0.0.0")

