#include "viewRadio.h"

ViewRadio::ViewRadio(const char* name, View** currentView, ControllerRadio* radio) : View(name, currentView) {
    _radio = radio;
}

void ViewRadio::displayVolume() {
    const char* text;
    uint16_t volume = _radio->getVolume();
    if (volume < 1)       return;
    else if (volume < 3)  text = "▁";
    else if (volume < 5)  text = "▂";
    else if (volume < 7)  text = "▃";
    else if (volume < 9)  text = "▄";
    else if (volume < 11) text = "▅";
    else if (volume < 13) text = "▆";
    else if (volume < 15) text = "▇";
    else                  text = "█";
    _sprite->setTextDatum(MC_DATUM);
    _sprite->drawString(text, 149, 21);
}

void ViewRadio::displayMute() {
    const char* text;
    if (_radio->getMute()) text = "";
    else        text = "";
    _sprite->setTextDatum(MC_DATUM);
    _sprite->drawString(text, 185, 24);
}

void ViewRadio::displayLevel() {
    const char* text;
    uint8_t rssi = _radio->GetRssi();
    if (rssi < 20)      text = "";
    else if (rssi < 30) text = "";
    else if (rssi < 50) text = "";
    else if (rssi < 60) text = "";
    else                text = "";
    _sprite->setTextDatum(MC_DATUM);
    _sprite->drawString(text, 221, 24);
}

void ViewRadio::displayFreq() {
    String freq;
    freq.reserve(16);
    uint16_t index = _radio->getRadioIndex();
    uint16_t band = _radio->getStorage()->getItem(index)->band;
    freq.concat((uint16_t)(band / 10));
    freq.concat('.');
    freq.concat((uint16_t)(band % 10));
    _sprite->loadFont(FONT_DIGIT_56);
    _sprite->setTextDatum(MC_DATUM);
    _sprite->drawString(freq, 63, 26);
}

void ViewRadio::OnHandle() {
    LOGN("ViewRadio::OnHandle")
    
    _sprite->fillSprite(TFT_SKYBLUE);

    _sprite->setTextColor(TFT_MAGENTA);

    _sprite->loadFont(FONT_ICON_32);

    displayVolume();
    displayMute();
    displayLevel();

    displayFreq();

    _sprite->loadFont(FONT_TEXT_32);
    uint16_t index = _radio->getRadioIndex();
    String text = _radio->getStorage()->getItem(index)->name;
    if (_sprite->textWidth(text) >=  239) {
        _sprite->setTextDatum(TL_DATUM);
        _sprite->drawString(text, 0, 70);
    }
    else {
        _sprite->setTextDatum(TC_DATUM);
        _sprite->drawString(text, 119, 70);
    }
    _sprite->unloadFont();
    _sprite->pushSprite(0, 0);
}
