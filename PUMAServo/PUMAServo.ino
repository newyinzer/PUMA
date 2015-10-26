#include <Servo.h>

Servo servo1; 


void setup() {

  pinMode(1,OUTPUT);
  servo1.attach(9); //analog pin 0
  Serial.begin(19200);
  Serial.println("Ready");

}

void loop() {

  static int v = 0;
/*
  if ( Serial.available()) {
    char ch = Serial.read();

    switch(ch) {
      case '0'...'9':
        v = v * 10 + ch - '0';
        break;
      case 's':
        servo1.write(v);
        v = 0;
        break;
    }
  }
*/
  //servo1.write(0);
  //delay(1000);
  /*
  servo1.write(10);
  delay(1000);
  servo1.write(20);
  delay(1000);
  servo1.write(30);
  delay(1000);
  servo1.write(40);
  delay(1000);
  servo1.write(50);
  delay(1000);
  servo1.write(60);
  delay(1000);
  servo1.write(70);
  delay(1000);
  servo1.write(80);
  delay(1000);
  */
  for(int i = 0; i <= 180; i++) {
    if(i % 2 == 0) {
      servo1.write(102);
    }
    else { // 94 to stop
      servo1.write(86);
    }
    delay(3000);
    Serial.println(i);
  }
}
