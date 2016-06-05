// for battery test

#define delay1 1000

unsigned long curtime, lastime;

int analogPin, voltageLevel;

void setup() {
  Serial.begin(19200);
  Serial.println("Ready");
  curtime = millis();
  lastime = curtime;
  analogPin = 0;
  voltageLevel = 0;
}

void loop() {
  curtime = millis();
  voltageLevel = analogRead(analogPin);
  if(curtime >= (lastime + delay1)) {
    Serial.print(curtime);
    Serial.print("\t");
    Serial.print(voltageLevel);
    Serial.print("\n");
    lastime = curtime;
  }
  else {
    lastime = lastime;
  }
}

