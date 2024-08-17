#include <Arduino.h>
#include <FS.h>
#include <SPIFFS.h>
#include "view/viewWeather.h"

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
    //LOGN("ViewWeather::OnHandle")
    _sprite->fillSprite(0x4C7D); //ColorToRGB565(0x4D, 0x8D, 0xEE)
    if (!_weather->isValid) {
        return;
    }
    _sprite->loadFont(FONT_TEXT_32);
    _sprite->setTextColor(TFT_WHITE);
    _sprite->setTextDatum(TL_DATUM);

    int32_t posX = _sprite->textWidth(_weather->weatherDescription);
    posX = (posX < (TFT_HEIGHT - 2)) ? (TFT_HEIGHT - posX) >> 1 : 2;
    _sprite->setTextDatum(TC_DATUM);
    drawTextBlock(TFT_HEIGHT >> 1, 64, (TFT_HEIGHT - 2), _weather->weatherDescription);
    
    // Для шрифта Colibri56
    // Ширина: для срок от -40° до +40° максимальная = 101
    // Высота: 48
    _sprite->loadFont(FONT_DIGIT_56);
    _sprite->setTextColor(TFT_WHITE);
    _sprite->setTextDatum(TL_DATUM);

    posX = ((int32_t)91 - _sprite->textWidth(_weather->weatherTemperature)) >> 1;
    _sprite->drawString(_weather->weatherTemperature, 80, 10);
    _sprite->unloadFont();

    drawImageFile(_weather->iconFileName.c_str(), 3, 0, 64);
}

void ViewWeather::drawTextBlock(int32_t left, int32_t top, int32_t width, const String &text) {

    int pos, length, subItemLen;
    String buf(text), item, subItem;

    while (buf.length() > 0) {
        item.clear();
        pos = buf.indexOf(' ');
        pos = (pos == -1) ? buf.length() : (pos + 1); 
        item =  buf.substring(0, pos); 
        length = _sprite->textWidth(item);
        buf.remove(0, pos);

        while (buf.length() > 0 && length <=  width - 2) {
            pos = buf.indexOf(' ');
            pos = (pos == -1) ? buf.length() : (pos + 1);

            subItem = buf.substring(0, pos);
            subItemLen = _sprite->textWidth(subItem);

            if (length + subItemLen >= width - 2) {
                break;
            }
            buf.remove(0, pos);
            length += subItemLen;
            item.concat(subItem);
        }
        _sprite->drawString(item, left, top);
        top += _sprite->fontHeight() + 2;
    }
}
