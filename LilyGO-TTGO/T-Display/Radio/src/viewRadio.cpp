#include "viewRadio.h"


ViewRadio::ViewRadio(const char* name, View** currentView, ControllerRadio* radio) : View(name, currentView) {
    _radio = radio;
}

uint8_t unmuteBitmap[] = {
    B00000000, B00000110, B00000000,
    B00000000, B00000110, B00000000,
    B00000000, B00011110, B00000000,
    B00000000, B00011110, B01000000,
    B00011111, B01111110, B00100000,
    B00011111, B01111110, B00100000,
    B00011111, B01111110, B00010000,
    B00011111, B01111110, B00010000,
    B00011111, B01111110, B00010000,
    B00011111, B01111110, B00100000,
    B00011111, B01111110, B00100000,
    B00000000, B00011110, B01000000,
    B00000000, B00011110, B00000000,
    B00000000, B00000110, B00000000,
    B00000000, B00000110, B00000000,
};

void ViewRadio::OnHandle() {
    LOGN("ViewRadio::OnHandle")

    _sprite->fillSprite(TFT_BLACK);

    uint16_t index = _radio->getRadioIndex();
    uint16_t band = _radio->getStorage()->getItem(index)->band;
    float freq = band / 10.0;

    _sprite->fillSprite(TFT_BLACK);
    _sprite->setTextDatum(TC_DATUM);
    _sprite->setTextColor(TFT_WHITE,TFT_BLACK);

    _sprite->drawFloat(freq, 1, 130, 40, 7);

    _sprite->setFreeFont(&Orbitron_Light_24);
    _sprite->drawString("FM Radio", 140, 1);

    int startList = (index > 2) ? index - 2 : 0;
    if (index + 3 >= _radio->getStorage()->length()) startList = _radio->getStorage()->length() - 5;
    // Serial.printf("RADIO index = %d, start = %d, max = %d\r\n", index, startList, _radio->getStorage()->length());
    _sprite->drawRoundRect(1, 17, 62, 79, 4, 0xAD55);
    _sprite->setTextColor(0xBEDF, TFT_BLACK);
    for (int i = 0; i < 5; i++) {
        freq = (float)_radio->getStorage()->getItem(startList++)->band / 10;
        _sprite->drawFloat(freq, 1, 34, 20 + (i * 14), 2);
        _sprite->fillCircle(10, 28 + (i * 14), 2, 0xFBAE);
    }

    if (!_radio->getMute()) {
        _sprite->drawBitmap(216, 10, unmuteBitmap, 24, 15, TFT_WHITE);
    }

    _sprite->drawRoundRect(216, 31, 24, 65, 4, TFT_WHITE);
    uint16_t volume = _radio->getVolume();
    for(int i = 0; i < volume; i++) {
        uint32_t color = 0x3526;
        if (i > 5)  color = TFT_YELLOW;
        if (i > 10) color = TFT_RED;
        _sprite->fillRect(220, 90 - (i * 4), 16, 2, color);
    }

    int temp = band - 15;
    for(int i = 0; i < 30; i++)
    {
        int32_t x = i * 8;
        if ((temp % 10) == 0) {
            _sprite->drawLine(x, 135, x, 123, 0xC638);
            _sprite->drawLine(x + 1, 135, x + 1, 123, 0xC638);
            _sprite->drawFloat(temp / 10.0, 1, x, 107, 2);
        }
        else if ((temp % 5) == 0 && (temp % 10) !=0 ) {
            _sprite->drawLine(x, 135, x, 127, 0xC638);
            _sprite->drawLine(x + 1, 135, x + 1, 127, 0xC638);
        }
        else {
            _sprite->drawLine(x, 135, x, 131, 0xC638);
        }
        temp = temp + 1;
    }
    _sprite->fillTriangle(116, 98, 120, 108, 124, 98, TFT_RED);
    _sprite->drawLine(120, 108, 120, 135, TFT_RED);
}
