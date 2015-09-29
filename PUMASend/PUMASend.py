#!/usr/bin/env python
# https://github.com/edoardoo/RF24
# http://arduino-for-beginners.blogspot.com/2013/02/setup-nordic-nrf24l01-rf-modules-to.html

import time
from RF24 import *

# Setup for GPIO 22 CE and CE0 CSN for RPi B+ with SPI Speed @ 8Mhz
radio = RF24(RPI_BPLUS_GPIO_J8_22, RPI_BPLUS_GPIO_J8_24, BCM2835_SPI_SPEED_8MHZ)

pipes = [0xF0F0F0F0E1, 0xF0F0F0F0D2]
payload_size = 4
send_payload = bytearray([0xDE, 0xAD, 0xBE, 0xEF])
string_payload = "dddd"

radio.begin()
radio.enableDynamicPayloads()
radio.setRetries(5,15)
radio.printDetails()

print ' ************ Role Setup *********** '
print 'Role: Ping Out, starting transmission'
radio.openWritingPipe(pipes[0])
radio.openReadingPipe(1,pipes[1])

# forever loop
while 1:
	# The payload will always be the same

        # Take the time, and send it.  This will block until complete
        print 'Now sending length ', payload_size, ' ... ',
	string_payload = "".join(map(chr,send_payload))
        radio.write(string_payload[:payload_size])

        time.sleep(5)
