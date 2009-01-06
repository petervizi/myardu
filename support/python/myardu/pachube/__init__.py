##
# @namespace myardu::pachube
#
# Some applications interracting with the http://www.pachube.com
# website.
#

from datetime import datetime, timedelta
from optparse import OptionParser
from serial import Serial
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
            print 'temp', self._temp/self._tempnum, 'hum', self._hum/self._humnum
            if (datetime.now() - self._lastput) > self._updateinterval:
                print 'now updating'
                self._pachube.update([Data(0, self._temp/self._tempnum, unit=Celsius()),
                                      Data(1, self._hum/self._humnum, unit=RH())])
                try:
                    self._pachube.put()
                    self._tempnum = self._humnum = self._temp =  self._hum = 0.0
                    self._lastput = datetime.now()
                except Exception, e:
                    print 'Exception during put:', e

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
