#include <Arduino.h>
#include <FS.h>
#include <SPIFFS.h>
#include "viewWeather.h"

const int32_t iconSize = 64;

ViewWeather::ViewWeather(const char* name, View** currentView, ControllerWeather* weather) : View(name, currentView) {
    _weather = weather;
}

void ViewWeather::drawImageFile(const char* fileName, const int32_t x, const int32_t y, const int32_t size) {
    fs::File f = SPIFFS.open(fileName);
    if (f) {
        size_t len = f.size();
        if (len <= sizeof(fileData)) {
            f.read((uint8_t*)fileData, len);
            _sprite->pushImage(x, y, size, size, fileData);
        }
        f.close();
    }
}

void ViewWeather::OnHandle() {
    LOGN("ViewWeather::OnHandle")
    _sprite->fillSprite(0x4C7D); //ColorToRGB565(0x4D, 0x8D, 0xEE)
    if (!_weather->isValid) {
        return;
    }
    _sprite->setTextDatum(TL_DATUM);
    _sprite->loadFont(FONT_TEXT_32);
    _sprite->setTextColor(TFT_WHITE);
    int32_t posX = _sprite->textWidth(_weather->weatherDescription);
    posX = (posX < 240) ? (240 - posX) >> 1 : 0;
    _sprite->setTextDatum(TL_DATUM);
    _sprite->drawString(_weather->weatherDescription, posX + 2, 64);
    //_sprite->unloadFont();

    // Для шрифта Colibri56
    // Ширина: для срок от -40° до +40° максимальная = 101
    // Высота: 48
    _sprite->loadFont(FONT_DIGIT_56);
    _sprite->setTextColor(TFT_WHITE);
    posX = ((int32_t)101 - _sprite->textWidth(_weather->weatherTemperature)) >> 1;
    _sprite->drawString(_weather->weatherTemperature, 122, 10);
    _sprite->unloadFont();

    drawImageFile(_weather->iconFileName.c_str(), 10, 10, 64);
    // drawImageFile(_weather->windFileName.c_str(), 192, 8, 32);
}
