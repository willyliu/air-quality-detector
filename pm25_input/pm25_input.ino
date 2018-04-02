#include <Arduino.h>

void setup() {
  Serial.begin(9600);
  Serial.println("setup()");  
}

void loop() {
  // put your main code here, to run repeatedly:
  bool dataLoaded = false;
  while (Serial.available()) {
    int value = Serial.read();
    Serial.print(value, DEC);
    Serial.print(" ");
    dataLoaded = true;
  }
  if (dataLoaded) {
    Serial.println("---");  
  }
  delay(100); // because pmsa003 sends data every 200ms~800ms, delay 100ms should be enough
}
