#include <Arduino.h>

void setup() {
  pinMode(PB0, OUTPUT);
  pinMode(PB1, OUTPUT);
  digitalWrite(PB0, LOW);
  digitalWrite(PB1, LOW);
}

void loop() {
  digitalWrite(PB1, LOW);
  digitalWrite(PB0, HIGH);
  delay(500);
  digitalWrite(PB0, LOW);
  digitalWrite(PB1, HIGH);
  delay(500);
}
