#include <FastLED.h>
#define NUM_LEDS 8
CRGB leds[NUM_LEDS];
 
void setup() { 
  FastLED.addLeds<WS2812, 8, GRB>(leds, NUM_LEDS); 
}
 
void loop() {
  leds[0] = CRGB::Red; 
  leds[1] = CRGB::Green;
  leds[2] = CRGB::Blue;
  FastLED.show();
  delay(500);

  leds[0] = CRGB::Green; 
  leds[1] = CRGB::Blue;
  leds[2] = CRGB::Red;
  FastLED.show();
  delay(500);

  leds[0] = CRGB::Blue; 
  leds[1] = CRGB::Red;
  leds[2] = CRGB::Green;
  FastLED.show();
  delay(500);
}