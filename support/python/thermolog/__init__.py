# -*- coding: utf-8 -*-

from optparse import OptionParser
import rrdtool
import sys
import time

from ThermoDaemon import ThermoDaemon

class Thermolog(object):
    def __init__(self, argv):
        parser = OptionParser()
        parser.add_option("-c", "--create", dest='create',
                          help="create new RRD database", action="store_true", default=False)
        parser.add_option("--step", dest="step", 
                          help="base interval in seconds with which data will be fed into the RRD",
                          type='string', default='10')
        parser.add_option('-d', dest='daemon', action='store_true',
                          help='start daemon for reading values', default=False)
        parser.add_option('--stop', dest='stop', action='store_true',
                          help='start daemon for reading values', default=False)
        parser.add_option('--graph', dest='graph',
                          help='create graph')


        (options, args) = parser.parse_args(argv)
        parser.destroy()

        if options.create:
            print "creating ... "
            rrdtool.create('/tmp/temperature.rrd',
                           'DS:temperature:GAUGE:'+ str(options.step*4) +':-40:124',
                           'RRA:AVERAGE:0.5:1:1200',
                           'RRA:MIN:0.5:12:2400',
                           'RRA:MAX:0.5:12:2400',
                           'RRA:AVERAGE:0.5:12:2400',
                           '--step', options.step)
            print 'done'
            sys.exit(0)

        if options.daemon:
            print 'starting daemon'
            daemon = ThermoDaemon('/tmp/thermolog.pid', stdout='/tmp/thermolog.out')            
            daemon.start()
            sys.exit(0)
        if options.stop:
            print 'stopping daemon'
            daemon = ThermoDaemon('/tmp/thermolog.pid', stdout='/tmp/thermolog.out')            
            daemon.stop()
            sys.exit(0)
        if options.graph:
            print 'creating graph'
            now = int(time.time())
            start = now - 60*60
            rrdtool.graph(options.graph,
                          '--imgformat', 'PNG',
                          '--width', '540',
                          '--height', '100',
                          '--start', str(start),
                          '--end', str(now),
                          '--vertical-label', '°C',
                          '--title', 'Temperature',
                          'DEF:temp=/tmp/temperature.rrd:temperature:AVERAGE',
                          'AREA:temp#990033:Temperature')
                          
