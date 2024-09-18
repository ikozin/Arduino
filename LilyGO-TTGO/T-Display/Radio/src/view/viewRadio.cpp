#include "view/viewRadio.h"
#include "fonts/NotoSansSemiBold24.h"

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

void ViewRadio::OnDrawHandle() {
    // LOGN("%s::OnDrawHandle", typeid(this).name);
    ControllerRadio* radio = static_cast<ControllerRadio*>(_ctrl);

    getSetting()->getSprite()->fillSprite(TFT_BLACK);

    RadioStorage* storage = radio->getStorage();
    uint16_t index = radio->getRadioIndex();
    uint16_t band = storage->getItem(index)->band;
    float freq = band / 10.0;

    getSetting()->getSprite()->fillSprite(TFT_BLACK);
    getSetting()->getSprite()->setTextDatum(TC_DATUM);
    getSetting()->getSprite()->setTextColor(TFT_WHITE,TFT_BLACK);

    getSetting()->getSprite()->drawFloat(freq, 1, 130, 40, 7);

    // getSetting()->getSprite()->setFreeFont(&Orbitron_Light_24);
    // getSetting()->getSprite()->drawString("FM Radio", 140, 1);

    getSetting()->getSprite()->loadFont(NotoSansSemiBold24);
    getSetting()->getSprite()->drawString(storage->getItem(index)->name.c_str(), 120, 1);
    getSetting()->getSprite()->unloadFont();

    int startList = (index > 2) ? index - 2 : 0;
    if (index + 3 >= storage->length()) startList = storage->length() - 5;
    // Serial.printf("RADIO index = %d, start = %d, max = %d\r\n", index, startList, storage->length());
    getSetting()->getSprite()->drawRoundRect(1, 24, 62, 77, 4, 0xAD55);
    getSetting()->getSprite()->setTextColor(0xBEDF, TFT_BLACK);
    for (int i = 0; i < 5; i++) {
        freq = (float)storage->getItem(startList++)->band / 10;
        getSetting()->getSprite()->drawFloat(freq, 1, 34, 26 + (i * 14), 2);
        getSetting()->getSprite()->fillCircle(10, 33 + (i * 14), 2, 0xFBAE);
    }

    if (!radio->getMute()) {
        getSetting()->getSprite()->drawBitmap(216, 10, unmuteBitmap, 24, 15, TFT_WHITE);
    }

    getSetting()->getSprite()->drawRoundRect(216, 31, 24, 65, 4, TFT_WHITE);
    uint16_t volume = radio->getVolume();
    for(int i = 0; i < volume; i++) {
        uint32_t color = 0x3526;
        if (i > 5)  color = TFT_YELLOW;
        if (i > 10) color = TFT_RED;
        getSetting()->getSprite()->fillRect(220, 90 - (i * 4), 16, 2, color);
    }

    int temp = band - 15;
    for(int i = 0; i < 30; i++)
    {
        int32_t x = i * 8;
        if ((temp % 10) == 0) {
            getSetting()->getSprite()->drawLine(x, 135, x, 123, 0xC638);
            getSetting()->getSprite()->drawLine(x + 1, 135, x + 1, 123, 0xC638);
            getSetting()->getSprite()->drawFloat(temp / 10.0, 1, x, 107, 2);
        }
        else if ((temp % 5) == 0 && (temp % 10) !=0 ) {
            getSetting()->getSprite()->drawLine(x, 135, x, 127, 0xC638);
            getSetting()->getSprite()->drawLine(x + 1, 135, x + 1, 127, 0xC638);
        }
        else {
            getSetting()->getSprite()->drawLine(x, 135, x, 131, 0xC638);
        }
        temp = temp + 1;
    }
    getSetting()->getSprite()->fillTriangle(116, 98, 120, 108, 124, 98, TFT_RED);
    getSetting()->getSprite()->drawLine(120, 108, 120, 135, TFT_RED);
}
