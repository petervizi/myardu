##
# @namespace myardu::pachube
#
# Some applications interracting with the http://www.pachube.com
# website.
#

from datetime import datetime, timedelta
from optparse import OptionParser
from serial import Serial
from math import log
from math import exp
from myardu.daemon import Daemon
from eeml import *

##
# This is a Daemon reading values via the usb port from the Arduino,
# running the pachube program.
#
# Sends the readings to http://www.pachube.com.
#
class PachuDaemon(Daemon):

    ##
    # Create a new Daemon.
    #
    # @param self mandatory
    # @param api the address of the api, eg. <tt>/api/1275.xml</tt>
    # @param key the personal api key
    # @param src the device name where the Arduino sends data
    # @param interval how often send data to the server, in minutes
    #
    def __init__(self, api, key, src, interval):
        Daemon.__init__(self, '/tmp/pachudaemon.pid', stdout='/tmp/pachudaemon.out', stderr='/tmp/pachudaemon.out')
        self._api = api
        self._key = key
        self._src = Serial(src, 9600)
        self._tempnum = self._humnum = self._temp =  self._hum = 0.0
        self._lastput = datetime.now()
        self._updateinterval = timedelta(minutes=interval)
        self._pachube = Pachube(self._api, self._key)

    def run(self):
        while True:
            values = self._src.readline().strip().split(' ')
            self._temp += float(values[0])
            self._hum += float(values[1])
            self._tempnum += 1.0
            self._humnum += 1.0
            print '.'
            if (datetime.now() - self._lastput) > self._updateinterval:
                temp = self._temp/self._tempnum
                hum = self._hum/self._humnum
                dp = self.getDP()
                hi = self.getHI()
                print datetime.now(), 'now updating', temp, hum, dp, 
                self._pachube.update([Data(0, round(temp, 2), unit=Celsius()),
                                      Data(1, round(hum, 2), unit=RH()),
                                      Data(2, round(dp, 2), unit=Celsius()),
                                      Data(3, round(hi, 2), unit=Celsius())])
                try:
                    self._pachube.put()
                    self._tempnum = self._humnum = self._temp =  self._hum = 0.0
                    self._lastput = datetime.now()
                except Exception, e:
                    print 'Exception during put:', e

    def getDP(self):
        temp = self._temp/self._tempnum
        hum = self._hum/self._humnum
        H = (log(hum, 10)-2.0)/0.4343 + (17.62*temp)/(243.12+temp)
        Dp = 243.12*H/(17.62-H)
        return Dp

    def getHI(self):
        t = self._temp/self._tempnum
        r = self._hum/self._humnum
        w = 0
        e = r/100.0*6.105*exp(17.27*t/(237.7+t))
        return t+0.33*e-0.70*w-4.0

##
# For reading command line agruments.
#
# Run <tt>pachube --help</tt> for information.
#
class PachuLog(object):

    USAGE = """usage: %prog [options] start/stop
Start/stop the pachube daemon."""

    ##
    # Parse the command line arguments and act.
    #
    # @param self mandatory
    # @param argv command line arguments
    #
    def __init__(self, argv):
        parser = OptionParser(usage=PachuLog.USAGE)
        parser.add_option('-a', dest='api', type='string',
                          help='the api address, /api/1275.xml')
        parser.add_option('-k', dest='key', type='string',
                          help='personal api key')
        parser.add_option('-i', dest='interval', type='float', default=5,
                          help='update interval in minutes')
        parser.add_option('--src', dest='src', type='string', default='/dev/ttyUSB0',
                          help='the source of data')
        (options, args) = parser.parse_args(argv)        
        if len(args) != 1:
            parser.error('Exactly one argument required')
        if args[0] not in ['start', 'stop']:
            parser.error('Argument must be start/stop')
        if not options.api:
            parser.error('Api address required')
        if not options.key:
            parser.error('Api key required')
        parser.destroy()

        daemon = PachuDaemon(options.api, options.key, options.src, options.interval)
        if args[0] == 'start':
            print 'starting'
            daemon.start()
        elif args[0] == 'stop':
            print 'stopping'
            daemon.stop()
