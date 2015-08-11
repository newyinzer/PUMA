#include <AFMotor.h>

AF_DCMotor motor_l(2);
AF_DCMotor motor_r(4);

void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("Motor test!");

  // turn on motors
  motor_l.setSpeed(200);
  motor_r.setSpeed(200);
  motor_l.run(RELEASE);
  motor_r.run(RELEASE);
}

void loop() {
  uint8_t i;
  
  Serial.print("tick");
  
  motor_l.run(FORWARD);
  motor_r.run(FORWARD);
  
  for (i=0; i<255; i++) {
    motor_l.setSpeed(255);  
    motor_r.setSpeed(255);
    delay(10);
 }
 
  for (i=255; i!=0; i--) {
    motor_l.setSpeed(255);  
    motor_r.setSpeed(255);
    delay(10);
 }
  
  Serial.print("tock");

  motor_l.run(BACKWARD);
  motor_r.run(BACKWARD);
  for (i=0; i<255; i++) {
    motor_l.setSpeed(255);  
    motor_r.setSpeed(255); 
    delay(10);
 }
 
  for (i=255; i!=0; i--) {
    motor_l.setSpeed(255); 
    motor_r.setSpeed(255);
    delay(10);
 }
  

  Serial.print("tech");
  motor_l.run(RELEASE);
  motor_r.run(RELEASE);
  delay(1000);
}
