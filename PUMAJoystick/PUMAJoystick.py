'''
basic_control.py
@author: Garrett Owen
@date: January 26, 2012

Based off code from 
http://iamtherockstar.com/archive/making-hid-devices-easier-using-pygame-joysticks/
'''

import serial
import pygame
import time

#serialPort = '/dev/tty.usbserial-A7004Jg4' # Arduino Mega
serialPort = '/dev/tty.usbmodemfd121'       # Arduino Uno
baudRate = 9600

# Open Serial Connection to Arduino Board
ser = serial.Serial(serialPort, baudRate, timeout=1);

'''
Gets joystick data and prints it
'''
pygame.init()
#joystick.init()
j = pygame.joystick.Joystick(0)
j.init()
print 'Initialized Joystick : %s' % j.get_name()

# Keeps a history of buttons pressed so that one press does
# not send multiple presses to the Arduino Board
button_history = [0,0,0,0,0,0,0,0,0,0,0,0]

try:
    while True:
        pygame.event.pump()

#        # Used to read input from the two joysticks       
#        for i in range(0, j.get_numaxes()):
#            if j.get_axis(i) != 0.00:
#                print 'Axis %i reads %.2f' % (i, j.get_axis(i))
#        
#        time.sleep(1)

        for i in range(0, j.get_numbuttons()):
            if j.get_button(i) != 0:
                if not button_history[i]:
                    print 'Button %i reads %i' % (i, j.get_button(i))
                    button_history[i] = 1
                    ser.write(str(i))
            else:
                button_history[i] = 0

except KeyboardInterrupt:
    j.quit()
