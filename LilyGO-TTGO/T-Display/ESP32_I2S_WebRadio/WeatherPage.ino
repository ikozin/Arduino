#include "WebRadio.h"

#define WeatherDelay   90000
long lastWeatherTime       = 0;

void displayWeatherPage() {
  //tft.fillScreen(0xe1c6);
  //tft.setSwapBytes(true);
  //tft.pushImage(37, 2, 165, 70, logoNasheRadio);

  //tft.fillScreen(TFT_BLACK);
  //tft.setSwapBytes(true);
  //tft.pushImage(5, 0, 231, 47, logoVestiFm);
  
  tft.fillScreen(TFT_WHITE);
  tft.setSwapBytes(true);
  tft.pushImage(56, 0, 128, 76, logoRusRadio);
}

void loopWeatherPage() {
  long t = millis();
  if (t - lastWeatherTime < WeatherDelay) return;
  lastWeatherTime = t;
}
