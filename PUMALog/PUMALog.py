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


# timedelta.total_seconds() is only in 2.7, so we backport it here for 2.6
def total_seconds(delta):
    return (delta.microseconds + (delta.seconds
        + delta.days * 24 * 3600) * 10**6) / 10**6


# Thanks, SO: http://stackoverflow.com/questions/1094841/reusable-library-to-get-human-readable-version-of-file-size
def sizeof_fmt(num):
    for unit in ['bytes', 'KB', 'MB', 'GB', 'TB']:
        if num < 1024.0:
            return "%3.1f%s" % (num, unit)
        num /= 1024.0

class Dashboard(object):
    def __init__(self, vehicle):
        #self.window = window
        self.elements = {}
        self.scroll_position = 0
        self.screen_lock = Lock()
        vehicle.listen(Measurement, self.receive)

        self.started_time = datetime.now()
        self.messages_received = 0

    def receive(self, measurement, **kwargs):
        if self.messages_received == 0:
            self.started_time = datetime.now()
        self.messages_received += 1
        # add to this to update message
"""
        if measurement.name not in self.elements:
            self.elements[measurement.name] = DataPoint(measurement.__class__)
        self.elements[measurement.name].update(measurement)
        self._redraw()
"""

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
