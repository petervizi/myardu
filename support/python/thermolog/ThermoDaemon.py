from myardu.daemon import Daemon
import serial
import rrdtool
import time

class ThermoDaemon(Daemon):
    def __init__(self, pidfile, stdout):
        Daemon.__init__(self, pidfile, stdout=stdout, stderr=stdout)
        self._source = serial.Serial('/dev/ttyUSB0', 9600)
        self._temperature = '/tmp/temperature.rrd'

    def run(self):
        while True:
            values = self._source.readline().strip().split(' ')
            temp = values[0]
            print temp, time.time()
            rrdtool.update(self._temperature, str(time.time()) + ':' + str(temp))
        
