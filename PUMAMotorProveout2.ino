int ENA=5;//connected to Arduino's port 5(output pwm)
int IN1=2;//connected to Arduino's port 2
int IN2=3;//connected to Arduino's port 3
int ENB=6;//connected to Arduino's port 6(output pwm)
int IN3=4;//connected to Arduino's port 4
int IN4=7;//connected to Arduino's port 7

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
  analogWrite(ENA,255);//start driving motor1
  analogWrite(ENB,255);//start driving motor2
}
