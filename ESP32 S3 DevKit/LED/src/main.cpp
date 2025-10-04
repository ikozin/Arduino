#include <Arduino.h>
//#include <FastLED.h>
#define RGB_PIN 38

void setup() {
    pinMode(RGB_PIN, OUTPUT);
    Serial.begin(115200);
    Serial.println("Start");
}

void loop() {
    digitalWrite(RGB_PIN, HIGH);
    delay(1000);
    digitalWrite(RGB_PIN, LOW);
    delay(1000);
}
