// For Switch Control

// Analog In 0-13 on 54-67
// H-Bridge Control on 22-53

// State Enumeration
static const int S = 0; // Straight
static const int SD = 1; // Straight to Divering
static const int D = 2; // Diverging
static const int DS = 3; // Diverging to Straight
static const int divergingThreshold = 512; // HIGH is diverging, LOW is straight

int SPINS[] = {22,24,26,28,30,32,34,36,38,40, 42, 44, 46, 48, 50, 52}; // Straight Track Pins
int SPIND[] = {23,25,27,29,31,33,35,37,39,41, 43, 45, 47, 49, 51, 53}; // Diverging Track Pins
int SPINA[] = {A0,A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11,A12,A13,A14,A15}; // Switch Input Pins
int SPINB[] = {SD,SD,SD,SD,SD,SD,SD,SD,SD,SD, SD, SD, SD, SD, SD, SD}; // Switch States
int maxPins = 16;

void setup() {
  // Start Serial Communication
  Serial.begin(19200);
  Serial.println("Starting Panel");
  
  // Set Up H-Bridge Control Pins
  int i = 0;
  int switchInput = 0;
  for(i = 0; i < maxPins; i++) {
    pinMode(SPINS[i], OUTPUT);
    pinMode(SPIND[i], OUTPUT);
  }
  for(i = 0; i < maxPins; i++) {
    digitalWrite(SPINS[i], LOW);
    digitalWrite(SPIND[i], LOW);
  }
  Serial.println("Control Pin Setup Complete");
  
  // Read Initial States
  for(i = 0; i < maxPins; i++) {
    switchInput = analogRead(SPINA[i]);
    if(switchInput > divergingThreshold) { SPINB[i] = SD; }
    else { SPINB[i] = DS; }
  }
  Serial.println("Current Switch States Read");
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
