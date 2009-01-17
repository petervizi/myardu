import serial
import sys
# tx blue
# rx yellow
rf = '/dev/rfcomm0'
ub = '/dev/ttyUSB0'
b1 = 9600
b2 = 115200
port = serial.Serial(rf, b1)

for i in range(0, 256):
    print i, 
    port.write(chr(i))
    print ord(port.read())
