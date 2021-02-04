#include "WebRadio.h"

#define WeatherDelay   90000
long lastWeatherTime       = 0;

void displayWeatherPage() {
  tft.fillScreen(TFT_BLACK);
}

void loopWeatherPage() {
  long t = millis();
  if (t - lastWeatherTime < WeatherDelay) return;
  lastWeatherTime = t;
}
