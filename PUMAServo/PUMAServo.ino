// for continuous rotation

#include <Servo.h>

#define delay 5000
#define CW 97
#define CCW 92

Servo servo1; 
unsigned long curtime;
unsigned long lastime;
int servospeed;

void setup() {

  pinMode(1,OUTPUT);
  servo1.attach(9); //analog pin 0
  Serial.begin(19200);
  Serial.println("Ready");
  curtime = millis();
  lastime = curtime;
  servospeed = CW;
  
}

void loop() {
  
  curtime = millis();
  
  if(curtime >= (lastime + delay)) {
    if(servospeed == CW) {
      Serial.println("Switching to CCW");
      servospeed = CCW;
    }
    else {
      Serial.println("Switching to CW");
      servospeed = CW;
    }
    lastime = curtime;
  }
  else {
    servospeed = servospeed;
    lastime = lastime;
  }
  
  servo1.write(servospeed);
}

/*
void loop() {
  // CCW
  servo1.write(92);
  delay(10000);
  
  // CW
  servo1.write(97);
  delay(10000);
  
}
*/
