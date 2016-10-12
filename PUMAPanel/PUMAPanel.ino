// For 180 degree servo

#include <Servo.h>

Servo servo1; 
int servopos;
int maxint;

void setup() {

  pinMode(1,OUTPUT);
  servo1.attach(9); //analog pin 0
  Serial.begin(19200);
  Serial.println("Ready");
  servopos = 0;
  maxint = 50;
}

void loop() {
  for(int i = maxint; i >= 0; i = i - 10) {
    servo1.write(i);
    Serial.println(i);
    delay(25);
  }
  for(int i = 0; i < maxint; i = i + 10) {
    servo1.write(i);
    Serial.println(i);
    delay(50);
  }
  delay(2000);
}
