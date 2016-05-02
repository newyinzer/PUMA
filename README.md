# PUMA: Arduino-Raspberry Pi Development Project

## Folder Details

### GettingStarted
Example code for Arduino and RF24 module, not important

### PUMAJoystick
Test code for receiving joystick values for Raspberry Pi, not important

### PUMAMotorProveout
Test code to ensure that motors run correctly, not important

### PUMAMotorProveout2
More test code to ensure that motors run correctly, not important

### PUMAReceive
Arduino code responsible for managing motor 1 and motor 2, important

### PUMASend
Raspberry Pi code responsible for testing send capability, not important

### PUMASend2
Arduino code responsible for testing send capability from an Arduino, need to retest, important

### PUMASendJoystick
Raspberry Pi code responsible for sending joystick commands, important

### PUMAServo
Arduino code responsible for testing the cannon mount servo, important

### PUMAServo180
Arduino code responsible for testing 180 degree cannon mount servo, important

### PUMAcore
Arduino code responsible for receiving joystick commands as a test, not important

## Links

### Servo Trial: 
http://playground.arduino.cc/Learning/SingleServoExample

### Motor Shield:

https://github.com/adafruit/Adafruit-Motor-Shield-library

https://learn.adafruit.com/arduino-tips-tricks-and-techniques/arduino-libraries

http://osepp.com/products/shield-arduino-compatible/motor-servo-shield/

### New Motor Shield:

http://osepp.com/products/sensors-arduino-compatible/motor-driver/

### Transceiver:

https://www.arduino.cc/en/Reference/SPI

https://github.com/edoardoo/RF24

http://hack.lenotta.com/arduino-raspberry-pi-switching-light-with-nrf24l01/

http://www.addicore.com/2pcs-Addicore-nRF24L01-Wireless-Transceiver-p/112.htm

http://playground.arduino.cc/InterfacingWithHardware/Nrf24L01

## Arduino Pin Assignments:

2 = IN1 (Motor Shield, motor1, rev)

3 = IN2 (Motor Shield, motor1, fwd)

4 = IN3 (Motor Shield, motor2, rev)

5 = ENA (Motor Shield, motor1, pwm)

6 = ENB (Motor Shield, motor2, pwm)

7 = IN4 (Motor Shield, motor2, fwd)

8 = NDATA (No Data LED)

9 = CE (Transceiver, 3)

10 = CSN (Transceiver, 4)

11 = MOSI (Transceiver, 6)

12 = MISO (Transceiver, 7)

13 = SCK (Transceiver, 5)

## Motion Capture (KameraPanzer)

### Reference Documents

Instructable on RasPi WebCam: http://www.instructables.com/id/Raspberry-Pi-remote-webcam/?ALLSTEPS

How to Write a Daemon: http://www.netzmafia.de/skripten/unix/linux-daemon-howto.html

Intro to Video Surveillance with Motion: http://www.debian-administration.org/article/347/An_Introduction_to_Video_Surveillance_with_'Motion'

Motion Basic Features: http://www.lavrsen.dk/foswiki/bin/view/Motion/MotionGuideBasicFeatures

Operate Linux Spycams: https://www.linux.com/learn/how-operate-linux-spycams-motion

Autostart Processes: http://askubuntu.com/questions/9382/how-can-i-configure-a-service-to-run-at-startup

### motion.conf Modifications (sudo nano /etc/motion/motion.conf)

webcam_maxrate to 100

output_normal to off
