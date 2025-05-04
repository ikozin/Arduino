#include <Arduino.h>
#include <FS.h>
#include <SPIFFS.h>
#include "view/viewWeather.h"

const int32_t iconSize = 64;

void ViewWeather::drawImageFile(const char* fileName, const int32_t x, const int32_t y, const int32_t size) {
    fs::File f = SPIFFS.open(fileName);
    if (f) {
        size_t len = f.size();
        if (len <= sizeof(fileData)) {
            f.read((uint8_t*)fileData, len);
            getSetting()->getSprite()->pushImage(x, y, size, size, fileData);
        }
        f.close();
    }
}

void ViewWeather::OnDrawHandle() {
    // LOGN("%s::OnDrawHandle", _name);
    ControllerWeather* weather  = static_cast<ControllerWeather*>(_ctrl);

    getSetting()->getSprite()->fillSprite(0x4C7D); //ColorToRGB565(0x4D, 0x8D, 0xEE)
    if (!weather->isValid) {
        return;
    }
    getSetting()->getSprite()->loadFont(FONT_TEXT_32);
    getSetting()->getSprite()->setTextColor(TFT_WHITE);
    getSetting()->getSprite()->setTextDatum(TL_DATUM);

    int32_t posX = getSetting()->getSprite()->textWidth(weather->weatherDescription);
    posX = (posX < (TFT_HEIGHT - 2)) ? (TFT_HEIGHT - posX) >> 1 : 2;
    getSetting()->getSprite()->setTextDatum(TC_DATUM);
    drawTextBlock(TFT_HEIGHT >> 1, 64, (TFT_HEIGHT - 2), weather->weatherDescription);
    
    // Для шрифта Colibri56
    // Ширина: для срок от -40° до +40° максимальная = 101
    // Высота: 48
    getSetting()->getSprite()->loadFont(FONT_DIGIT_56);
    getSetting()->getSprite()->setTextColor(TFT_WHITE);
    getSetting()->getSprite()->setTextDatum(TL_DATUM);

    posX = ((int32_t)91 - getSetting()->getSprite()->textWidth(weather->weatherTemperature)) >> 1;
    getSetting()->getSprite()->drawString(weather->weatherTemperature, 80, 10);
    getSetting()->getSprite()->unloadFont();

    drawImageFile(weather->iconFileName.c_str(), 3, 0, 64);
}

void ViewWeather::drawTextBlock(int32_t left, int32_t top, int32_t width, const String &text) {

    int pos, length, subItemLen;
    String buf(text), item, subItem;

    while (buf.length() > 0) {
        item.clear();
        pos = buf.indexOf(' ');
        pos = (pos == -1) ? buf.length() : (pos + 1); 
        item =  buf.substring(0, pos); 
        length = getSetting()->getSprite()->textWidth(item);
        buf.remove(0, pos);

        while (buf.length() > 0 && length <=  width - 2) {
            pos = buf.indexOf(' ');
            pos = (pos == -1) ? buf.length() : (pos + 1);

            subItem = buf.substring(0, pos);
            subItemLen = getSetting()->getSprite()->textWidth(subItem);

            if (length + subItemLen >= width - 2) {
                break;
            }
            buf.remove(0, pos);
            length += subItemLen;
            item.concat(subItem);
        }
        getSetting()->getSprite()->drawString(item, left, top);
        top += getSetting()->getSprite()->fontHeight() + 2;
    }
}
