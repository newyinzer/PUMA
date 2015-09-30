'''
PUMASendJoystick.py

Based off code from 
http://iamtherockstar.com/archive/making-hid-devices-easier-using-pygame-joysticks/
'''

import pygame
import time

pygame.init()
j = pygame.joystick.Joystick(0)
j.init()
print 'Initialized Joystick : %s' % j.get_name()

# Keeps a history of axes
axis_l = 0 #1
axis_r = 0 #3
axis_val = 0.0

try:
    while True:
        pygame.event.pump()
	axis_val = j.get_axis(1)
	axis_val = axis_val * -32767.0
	axis_l = int(axis_val)
	axis_val = j.get_axis(3)
	axis_val = axis_val * -32767.0
	axis_r = int(axis_val)
	print '%i %i' % (axis_l,axis_r)
	time.sleep(0.1) # one sheep, two sheep, it's time to sleep
except KeyboardInterrupt:
    j.quit()
