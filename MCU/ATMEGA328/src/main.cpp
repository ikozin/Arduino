#include <Arduino.h>

void setup() {
    pinMode(2, OUTPUT);
    pinMode(3, OUTPUT);
    pinMode(4, OUTPUT);
}

void blink(uint8_t pin, uint32_t time) {
    digitalWrite(pin, HIGH);
    delay(time);
    digitalWrite(pin, LOW);
    delay(time);
}

void loop() {
    blink(2, 200);
    blink(3, 200);
    blink(4, 200);
}
