# Data Logger for PUMA Project
# This module is based off of the ``openxc-dashboard`` command line program.

from __future__ import absolute_import
from __future__ import division

import argparse
import math
from datetime import datetime
from threading import Lock

from .common import device_options, configure_logging, select_device
from openxc.vehicle import Vehicle
from openxc.measurements import EventedMeasurement, Measurement

try:
    unicode
except NameError:
    # Python 3
    basestring = unicode = str

class Dashboard(object):
    def __init__(self, vehicle):
        vehicle.listen(Measurement, self.receive)
        self.started_time = datetime.now()
        self.messages_received = 0

    def receive(self, measurement, **kwargs):
        if self.messages_received == 0:
            self.started_time = datetime.now()
        self.messages_received += 1
        
        if measurement.name == 'steering_wheel_angle':
            print datetime.now()
            print ',steering_wheel_angle,'
            print measurement.value
            print '\n'
        elif measurement.name == 'vehicle_speed':
            print datetime.now()
            print ',vehicle_speed,'
            print vehicle_speed
            print '\n'

def run_dashboard(source_class, source_kwargs):
    vehicle = Vehicle()
    dashboard = Dashboard(vehicle)
    dashboard.source = source_class(**source_kwargs)
    vehicle.add_source(dashboard.source)
    
def parse_options():
    parser = argparse.ArgumentParser(
            description="View a real-time dashboard of all OpenXC measurements",
            parents=[device_options()])
    arguments = parser.parse_args()
    return arguments


def main():
    configure_logging()
    arguments = parse_options()
    source_class, source_kwargs = select_device(arguments)
    run_dashboard(source_class, source_kwargs)
