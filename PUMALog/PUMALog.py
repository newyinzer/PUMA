# Data Logger for PUMA Project
# This module is based off of the ``openxc-dashboard`` command line program.

from __future__ import absolute_import
from __future__ import division

import argparse
import curses
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
"""
        curses.use_default_colors()
        curses.init_pair(1, curses.COLOR_RED, -1)
        curses.init_pair(2, curses.COLOR_GREEN, -1)
        curses.init_pair(3, curses.COLOR_YELLOW, -1)
"""
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
    def _redraw(self):
        self.screen_lock.acquire()
        self.window.erase()
        max_rows = self.window.getmaxyx()[0] - 4
        for row, element in enumerate(sorted(self.elements.values(),
                key=lambda elt: elt.current_data.name)[self.scroll_position:]):
            if row > max_rows:
                break
            element.print_to_window(self.window, row, self.started_time)
        self.window.addstr(max_rows + 1, 0,
                "Message count: %d (%d corrupted)" % (self.messages_received,
                    self.source.corrupted_messages), curses.A_REVERSE)
        self.window.addstr(max_rows + 2, 0,
                "Total received: %s" %
                sizeof_fmt(self.source.bytes_received),
                curses.A_REVERSE)
        self.window.addstr(max_rows + 3, 0, "Data Rate: %s" %
            sizeof_fmt(self.source.bytes_received /
                (total_seconds(datetime.now() - self.started_time)
                    + 0.1)),
             curses.A_REVERSE)
        self.window.refresh()
        self.screen_lock.release()

    def scroll_down(self, lines):
        self.screen_lock.acquire()
        self.scroll_position = min(self.window.getmaxyx()[1],
                self.scroll_position + lines)
        self.screen_lock.release()

    def scroll_up(self, lines):
        self.screen_lock.acquire()
        self.scroll_position = max(0, self.scroll_position - lines)
        self.screen_lock.release()


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
    #curses.wrapper(run_dashboard, source_class, source_kwargs)
