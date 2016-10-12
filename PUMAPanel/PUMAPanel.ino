// For Switch Control

int SPINS[] = {22,24,26,28,30,32,34,36,38,40,42,44,46,48,50,52};
int SPIND[] = {23,25,27,29,31,33,35,37,39,41,43,45,47,49,51,53};
int maxPins = 16;

int PIN00D = 23;
int PIN01S = 24;
int PIN01D = 25;
int PIN02S = 26;
int PIN02D = 27;

void setup() {
  // Analog In 0-13 on 54-67
  // H-Bridge Control on 22-53
  
  // Set Up Output Pins
  int i = 0;
  for(i = 0; i < maxPins; i++) {
    pinMode(SPINS[i], OUTPUT);
    pinMode(SPIND[i], OUTPUT);
  }
  pinMode(PIN00S, INPUT);
  pinMode(PIN00D, INPUT);
  pinMode(PIN01S, INPUT);
  pinMode(PIN01D, INPUT);
  pinMode(PIN02S, INPUT);
  pinMode(PIN02D, INPUT);
  
  pinMode(1,OUTPUT);
  servo1.attach(9); //analog pin 0
  
  Serial.begin(19200);
  Serial.println("Ready");
  
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
