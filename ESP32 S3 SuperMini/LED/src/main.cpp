#include <Arduino.h>
#include <FastLED.h>

#define NUM_LEDS 1
#define DATA_PIN 48

CRGB leds[NUM_LEDS];
int colors[] = { CRGB::Red, CRGB::Green, CRGB::Blue };
uint8_t c = 0;

uint8_t pins[] = { 1, 2, 3, 4, 5, 6, 7 };
uint8_t n = 0;

void setup() {
    FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
    for (int i = 0; i < sizeof(pins)/sizeof(pins[0]); i++) {
        pinMode(pins[i], OUTPUT);
    }
}

void loop() {
    for (int i = 0; i < sizeof(pins)/sizeof(pins[0]); i++) {
        digitalWrite(pins[i], LOW);
    }
    digitalWrite(pins[n++], HIGH);
    if (n >= sizeof(pins)/sizeof(pins[0])) n = 0;

    leds[0] = colors[c++];
    FastLED.show();
    if (c >= sizeof(colors)/sizeof(colors[0])) c = 0;
    
    delay(500);
}
