'''
PUMAJoystick.py

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
axis_history = [0,0,0,0,0]
axis_val = 0

try:
    while True:
        pygame.event.pump()
	print '%i %i' % (axis_history[2],axis_history[3])
        for i in range(0, j.get_numaxes()):
		axis_val = j.get_axis(i)
		axis_val = axis_val * 32767.0
		axis_history[i] = int(axis_val)
		#print '%f' % axis_val
		#axis_history[i] = j.get_axis(i)
except KeyboardInterrupt:
    j.quit()
