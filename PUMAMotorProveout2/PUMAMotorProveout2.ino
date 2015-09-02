int ENA=5;//connected to Arduino's port 5(output pwm)
int IN1=2;//connected to Arduino's port 2
int IN2=3;//connected to Arduino's port 3
int ENB=6;//connected to Arduino's port 6(output pwm)
int IN3=4;//connected to Arduino's port 4
int IN4=7;//connected to Arduino's port 7
int CFG=0;//system on

void setup() {
  pinMode(ENA,OUTPUT);//output
  pinMode(ENB,OUTPUT);
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);
  digitalWrite(ENA,LOW);
  digitalWrite(ENB,LOW);//stop driving
  digitalWrite(IN1,LOW); 
  digitalWrite(IN2,HIGH);//setting motor1's directon
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);//setting motor2's directon
}

void loop() {
  if(CFG == 1) {
    digitalWrite(IN1,LOW); 
    digitalWrite(IN2,HIGH);//setting motor1's directon
    digitalWrite(IN3,HIGH);
    digitalWrite(IN4,LOW);//setting motor2's directon
    for(int i = 0; i <= 255; i++) {
      analogWrite(ENA,i);//start driving motor1
      analogWrite(ENB,i);//start driving motor2
      delay(10);
    }
    for(int j = 255; j >= 0; j--) {
      analogWrite(ENA,j);//start driving motor1
      analogWrite(ENB,j);//start driving motor2
      delay(10);
    }
    digitalWrite(IN1,HIGH); 
    digitalWrite(IN2,LOW);//setting motor1's directon
    digitalWrite(IN3,LOW);
    digitalWrite(IN4,HIGH);//setting motor2's directon
    for(int i = 0; i <= 255; i++) {
      analogWrite(ENA,i);//start driving motor1
      analogWrite(ENB,i);//start driving motor2
      delay(10);
    }
    for(int j = 255; j >= 0; j--) {
      analogWrite(ENA,j);//start driving motor1
      analogWrite(ENB,j);//start driving motor2
      delay(10);
    }
  } else {
    analogWrite(ENA,0);//start driving motor1
    analogWrite(ENB,0);//start driving motor2
    delay(10);
  }
}
