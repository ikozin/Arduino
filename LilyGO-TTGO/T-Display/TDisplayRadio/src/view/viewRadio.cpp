#include "view/viewRadio.h"
#include "view/toolPng.h"
#include <string>

uint8_t unmuteBitmap[] = {
    0b00000000, 0b00000110, 0b00000000,
    0b00000000, 0b00000110, 0b00000000,
    0b00000000, 0b00011110, 0b00000000,
    0b00000000, 0b00011110, 0b01000000,
    0b00011111, 0b01111110, 0b00100000,
    0b00011111, 0b01111110, 0b00100000,
    0b00011111, 0b01111110, 0b00010000,
    0b00011111, 0b01111110, 0b00010000,
    0b00011111, 0b01111110, 0b00010000,
    0b00011111, 0b01111110, 0b00100000,
    0b00011111, 0b01111110, 0b00100000,
    0b00000000, 0b00011110, 0b01000000,
    0b00000000, 0b00011110, 0b00000000,
    0b00000000, 0b00000110, 0b00000000,
    0b00000000, 0b00000110, 0b00000000,
};

void ViewRadio::OnUpdate() {
    StorageRadio* storage = _controller->getStorage();
    uint16_t index = _controller->getRadioIndex();
    uint16_t band = storage->getItem(index)->band;
    float freq = band / 10.0;
    
    _tft->startWrite();

    _tft->fillSprite(COLOR_BLACK);
    _tft->setTextDatum(TC_DATUM);
    _tft->setTextColor(COLOR_WHITE, COLOR_BLACK);

    _tft->drawFloat(freq, 1, 130, 40, 7);

    // _tft->setFreeFont(&Orbitron_Light_24);
    // _tft->drawString("FM Radio", 140, 1);

    _tft->loadFont("Roboto Bold23", LittleFS);
    _tft->drawString(storage->getItem(index)->name.c_str(), 120, 1);
    _tft->unloadFont();

    int startList = (index > 2) ? index - 2 : 0;
    if (index + 3 >= storage->length()) startList = storage->length() - 5;
    // Serial.printf("RADIO index = %d, start = %d, max = %d\r\n", index, startList, storage->length());
    _tft->drawRoundRect(1, 24, 62, 77, 4, 0xAD55);
    _tft->setTextColor(0xBEDF, COLOR_BLACK);
    for (int i = 0; i < 5; i++) {
        freq = (float)storage->getItem(startList++)->band / 10;
        _tft->drawFloat(freq, 1, 34, 26 + (i * 14), 2);
        _tft->fillCircle(10, 33 + (i * 14), 2, 0xFBAE);
    }

    if (!_controller->getMute()) {
        _tft->drawBitmap(216, 10, unmuteBitmap, 24, 15, COLOR_WHITE);
    }

    _tft->drawRoundRect(216, 31, 24, 65, 4, COLOR_WHITE);
    uint16_t volume = _controller->getVolume();
    for(int i = 0; i < volume; i++) {
        uint32_t color = 0x3526;
        if (i > 5)  color = COLOR_YELLOW;
        if (i > 10) color = COLOR_RED;
        _tft->fillRect(220, 90 - (i * 4), 16, 2, color);
    }

    int temp = band - 15;
    for(int i = 0; i < 30; i++)
    {
        int32_t x = i * 8;
        if ((temp % 10) == 0) {
            _tft->drawLine(x, 135, x, 123, 0xC638);
            _tft->drawLine(x + 1, 135, x + 1, 123, 0xC638);
            _tft->drawFloat(temp / 10.0, 1, x, 107, 2);
        }
        else if ((temp % 5) == 0 && (temp % 10) !=0 ) {
            _tft->drawLine(x, 135, x, 127, 0xC638);
            _tft->drawLine(x + 1, 135, x + 1, 127, 0xC638);
        }
        else {
            _tft->drawLine(x, 135, x, 131, 0xC638);
        }
        temp = temp + 1;
    }
    _tft->fillTriangle(116, 98, 120, 108, 124, 98, COLOR_RED);
    _tft->drawLine(120, 108, 120, 135, COLOR_RED);

    _tft->endWrite();
}