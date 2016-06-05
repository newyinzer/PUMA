// for battery test

#define delay1 5000

unsigned long curtime, lastime, sectime;

int analogPin, voltageLevel;
float voltage;

void setup() {
  Serial.begin(19200);
  Serial.println("Ready");
  curtime = millis();
  lastime = curtime;
  analogPin = 0;
  voltageLevel = 0;
  voltage = 0.0;
  sectime = 0;
}

void loop() {
  curtime = millis();
  voltageLevel = analogRead(analogPin);
  voltage = (voltageLevel * (5.0 / 1024.0)) * 2.0;
  sectime = curtime / 1000;
  if(curtime >= (lastime + delay1)) {
    Serial.print(sectime);
    Serial.print("\t");
    Serial.print(voltage);
    Serial.print("\n");
    lastime = curtime;
  }
  else {
    lastime = lastime;
  }
}

