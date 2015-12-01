// For 180 degree servo

#include <Servo.h>

Servo servo1; 
int servopos;

#define SERVOFWD 7 // Servo Forward
#define SERVOREV 8 // Servo Reverse
#define SERVOSTP 9 // Servo Stop
#define SERVORST 10 // Servo Reset to 90

void setup() {

  pinMode(1,OUTPUT);
  servo1.attach(9); //analog pin 0
  Serial.begin(19200);
  Serial.println("Ready");
  servopos = 90;
}

void writeservo(int dir) {
  if(dir == SERVOFWD) {
    if(servopos >= 179) {
      servopos = 179;
    }
    else {
      servopos++;
    }
  }
  else if(dir == SERVOREV) {
    if(servopos <= 0) {
      servopos = 0;
    }
    else {
      servopos--;
    }
  }
  else if(dir == SERVOSTP) {
    servopos = servopos;
  }
  else if(dir == SERVORST) {
    servopos = 90;
  }
  else {
    servopos = servopos;
  }
  servo1.write(servopos);
  delay(1000);
}

void loop() {
  int i;
  Serial.println("Forward");
  for(i = 0; i <= 100; i++) {
    writeservo(SERVOFWD);
  }
  Serial.println("Stop");
  for(i = 0; i <= 10; i++) {
    writeservo(SERVOSTP);
  }
  Serial.println("Backward");
  for(i = 0; i <= 190; i++) {
    writeservo(SERVOREV);
  }
  Serial.println("Stop Again");
  for(i = 0; i <= 10; i++) {
    writeservo(SERVOSTP);
  }
  Serial.println("Forward Again");
  for(i = 0; i <= 190; i++) {
    writeservo(SERVOFWD);
  }
  Serial.println("Reset");
  writeservo(SERVORST);
}
