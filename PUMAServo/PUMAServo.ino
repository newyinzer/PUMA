// for continuous rotation

#include <Servo.h>

Servo servo1; 


void setup() {

  pinMode(1,OUTPUT);
  servo1.attach(9); //analog pin 0
  Serial.begin(19200);
  Serial.println("Ready");

}

void loop() {
  // CCW
  servo1.write(92);
  delay(10000);
  
  // CW
  servo1.write(97);
  delay(10000);
  
}
