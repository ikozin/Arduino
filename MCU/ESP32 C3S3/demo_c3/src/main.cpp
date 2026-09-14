#include <Arduino.h>

/*
ESP32 C3 SuperMini
       ┌───┬──────────┬───┐
GPIO5  ┤   │ ESP32-C3 │   ├ 5V
GPIO6  ┤   │          │   ├ GND
GPIO7  ┤   │          │   ├ 3V3
GPIO8  ┤SDA│          │   ├ GPIO4
GPIO9  ┤SCL│          │   ├ GPIO3
GPIO10 ┤   │          │   ├ GPIO2
GPIO20 ┤RX │          │   ├ GPIO1
GPIO21 ┤TX │          │   ├ GPIO0
       └───┴──────────┴───┘

*/

int leds[] = { 5, 6, 7, 8, 9, 10 };
int size = sizeof(leds)/sizeof(leds[0]);
void setup() {
    for (int i = 0; i < size; i++) {
        pinMode(leds[i], OUTPUT);
    }
    Serial.begin(115200);
    Serial.println("Start");
}

void loop() {
    Serial.println("HIGH");
    for (int i = 0; i < size; i++) {
        digitalWrite(leds[i], HIGH);
    }
    delay(1000); // wait for a second
    
    Serial.println("LOW");
    for (int i = 0; i < size; i++) {
        digitalWrite(leds[i], LOW);
    }    
    delay(1000); // wait for a second
}
