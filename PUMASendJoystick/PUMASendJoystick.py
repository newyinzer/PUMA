#!/usr/bin/env python
'''
PUMASendJoystick.py

Based off code from 
http://iamtherockstar.com/archive/making-hid-devices-easier-using-pygame-joysticks/
https://github.com/edoardoo/RF24
http://arduino-for-beginners.blogspot.com/2013/02/setup-nordic-nrf24l01-rf-modules-to.html

'''

import pygame
import time
import time
from RF24 import *

# Start joystick system
print 'Starting joystick system'
pygame.init()
j = pygame.joystick.Joystick(0)
j.init()
print 'Initialized Joystick : %s' % j.get_name()

# Setup for GPIO 22 CE and CE0 CSN for RPi B+ with SPI Speed @ 8Mhz
radio = RF24(RPI_BPLUS_GPIO_J8_22, RPI_BPLUS_GPIO_J8_24, BCM2835_SPI_SPEED_8MHZ)
print 'Starting radio system'
pipes = [0xF0F0F0F0E1, 0xF0F0F0F0D2]
payload_size = 4
send_payload = bytearray([0x41, 0x42, 0x43, 0x44])
string_payload = "eeee"
setval = radio.begin()
radio.enableDynamicPayloads()
radio.setRetries(5,15)
radio.printDetails()

print 'Opening writing pipe'
radio.openWritingPipe(pipes[0])
radio.openReadingPipe(1,pipes[1])

# Keeps a history of axes
axis_l = 0 #1
axis_r = 0 #3
axis_val = 0.0

try:
    while True:
    	print 'Fetching pygame axis values'
        pygame.event.pump()
	axis_val = j.get_axis(1)
	axis_val = axis_val * -127.0
	axis_l = int(axis_val)
	print 'L = %i' % axis_l
	send_payload[0] = axis_l & 0xFF
	axis_val = j.get_axis(3)
	axis_val = axis_val * -127.0
	axis_r = int(axis_val)
	print 'R = %i' % axis_r
	send_payload[1] = axis_r & 0xFF
	print 'Axis values are L = %i R = %i' % (send_payload[0],send_payload[1])
	
	# The payload will always be the same
	radio.stopListening()
        # Take the time, and send it.  This will block until complete
        print 'Now sending length ', payload_size, ' ... ',
	string_payload = "".join(map(chr,send_payload))
        setval = radio.write(string_payload[:payload_size])
	print 'writing result ',setval
        time.sleep(1)
	
except KeyboardInterrupt:
    j.quit()
