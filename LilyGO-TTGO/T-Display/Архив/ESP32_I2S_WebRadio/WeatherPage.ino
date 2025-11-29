#include "WebRadio.h"
#include <FS.h>
#include <SPIFFS.h>

#define WeatherDelay   90000
long lastWeatherTime       = 0;

void displayWeatherPage() {
  tft.fillScreen(TFT_BLACK);
}
/*
void dumpImage(uint8_t *p, size_t len) {
  Serial.print("Size: ");
  Serial.println(len);
  for (int i = 0; i < len; i+=2) {
    if (i % 16 == 0)
      Serial.println();
    Serial.printf("%2X%2X ", p[i+1], p[i]);  
  }
  Serial.println();
}
*/
void loopWeatherPage() {
  long t = millis();
  if (t - lastWeatherTime < WeatherDelay) return;
  lastWeatherTime = t;
}
