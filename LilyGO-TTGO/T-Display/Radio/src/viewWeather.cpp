#include <Arduino.h>
#include <FS.h>
#include <SPIFFS.h>
#include "viewWeather.h"

const int32_t iconSize = 64;

ViewWeather::ViewWeather(const char* name, TFT_eSPI* tft, View** currentView, ControllerWeather* weather) : View(name, tft, currentView) {
  _weather = weather;
}

void ViewWeather::drawImageFile(const char* fileName, const int32_t x, const int32_t y, const int32_t size) {
  fs::File f = SPIFFS.open(fileName);
  if (f) {
    size_t len = f.size();
    if (len <= sizeof(fileData)) {
      f.read((uint8_t*)fileData, len);
      _tft->pushImage(x, y, size, size, fileData);
    }
    f.close();
  }
}

void ViewWeather::OnHandle() {
  // Serial.printf("%s\r\n", _name);
  _tft->fillScreen(0x4C7D); //ColorToRGB565(0x4D, 0x8D, 0xEE)
  _tft->setTextDatum(TL_DATUM);

  drawImageFile(_weather->iconFileName.c_str(), 107, 0, iconSize);
  drawImageFile(_weather->windFileName.c_str(), 192, 8, 32);
  
  _tft->loadFont(FONT_CALIBRI_32);
  _tft->setTextColor(TFT_WHITE);
  int32_t posX = _tft->textWidth(_weather->weatherDescription);
  posX = (posX < 240) ? (240 - posX) >> 1 : 0;
  _tft->setTextDatum(TL_DATUM);
  _tft->drawString(_weather->weatherDescription, posX + 2, 64);
  _tft->unloadFont();

  // Для шрифта Colibri56
  // Ширина: для срок от -40° до +40° максимальная = 101
  // Высота: 48
  _tft->loadFont(FONT_CALIBRI_56);
  _tft->setTextColor(TFT_WHITE);
  posX = ((int32_t)101 - _tft->textWidth(_weather->weatherTemperature)) >> 1;
  _tft->drawString(_weather->weatherTemperature, posX + 2, 10);
  _tft->unloadFont();
}
