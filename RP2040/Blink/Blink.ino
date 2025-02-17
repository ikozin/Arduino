/*
Для работы RGB посадочное место
для R68 необходимо замкнуть

│        ╔═════╗  │
│        ║ R68 ║  │
│        ╚═════╝  │
│ USR         RST │
│┌───┐┌─────┐┌───┐│
││ O ││ RGB ││ O ││
│└───┘└─────┘└───┘│
└─────────────────┘
*/
#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

// #define LED_BUILTIN 25
#define PIN_USR     24
#define PIN_RGB     23
#define NUMPIXELS   1

Adafruit_NeoPixel pixels(NUMPIXELS, PIN_RGB, NEO_GRB + NEO_KHZ800);

uint8_t   r;
uint8_t   g;
uint8_t   b;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(PIN_USR, INPUT_PULLUP);
  pixels.begin();
  pixels.show();
}

void loop() {

  if (digitalRead(PIN_USR) == LOW) {
    for (int i = 0; i < 5; i++) {
      digitalWrite(LED_BUILTIN, LOW);
      delay(200);
      digitalWrite(LED_BUILTIN, HIGH);
      delay(200);
    }
  }

  digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)

  r = random(256);
  g = random(256);
  b = random(256);
  pixels.setPixelColor(0, pixels.Color(r, g, b));
  pixels.show();

  delay(1000);

  digitalWrite(LED_BUILTIN, LOW);   // turn the LED off by making the voltage LOW

  r = random(256);
  g = random(256);
  b = random(256);
  pixels.setPixelColor(0, pixels.Color(r, g, b));
  pixels.show();
  
  delay(1000);                      // wait for a second
}
