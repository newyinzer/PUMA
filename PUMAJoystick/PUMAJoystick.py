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

# Keeps a history of buttons pressed so that one press does
# not send multiple presses to the Arduino Board
button_history = [0,0,0,0,0,0,0,0,0,0,0,0]

try:
    while True:
        pygame.event.pump()

        for i in range(0, j.get_numbuttons()):
            if j.get_button(i) != 0:
                if not button_history[i]:
                    print 'Button %i reads %i' % (i, j.get_button(i))
                    button_history[i] = 1
            else:
                button_history[i] = 0

except KeyboardInterrupt:
    j.quit()
