import serial
import threading
import sys

class CommandReader(threading.Thread):
    def __init__(self, port, portreader):
        threading.Thread.__init__(self)
        self.port = port
        self.lineend = '\r'

    def run(self):
        while True:
            sys.stdout.write('>> ')
            line = sys.stdin.readline()
            if line == '\\quit\n':
                portreader.stop()
                sys.exit(0)
            elif line == '\ler\n':
                self.lineend = '\r'
            elif line == '\len':
                self.lineend = '\n'
            else:
                port.write(line[:-1] + self.lineend)

class PortReader(threading.Thread):
    def __init__(self, port):
        threading.Thread.__init__(self)
        self.port = port
        self.dojob = True

    def stop(self):
        self.dojob = False

    def run(self):
        while self.dojob:
            sys.stdout.write(port.read())
            
            
port = serial.Serial(sys.argv[1], 9600, timeout=1)
portreader = PortReader(port)
portreader.start()
CommandReader(port, portreader).start()
