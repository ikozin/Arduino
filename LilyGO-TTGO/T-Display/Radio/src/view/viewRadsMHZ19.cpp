#include "view/viewRadsMHZ19.h"
#include "fonts/CalibriBold12.h"
#include "fonts/Roboto33.h"

ViewRadsMHZ19::ViewRadsMHZ19(const char* name, ViewSettig* setting,  ControllerRadSens* radSens, ControllerMHZ19* mhz19, SemaphoreHandle_t updateEvent):
                View(name, setting, updateEvent) {
    _radSens = radSens;
    _mhz19 = mhz19;
}

void ViewRadsMHZ19::Start(uint16_t stackDepth){
        if (_radSens != nullptr) {
            _radSens->AddUpdateEvent(GetEvent());
        }
        if (_mhz19 != nullptr) {
            _mhz19->AddUpdateEvent(GetEvent());
        }
        xTaskCreate(ViewHandler, this->_name, stackDepth, this, 100, &this->_task);
}


void ViewRadsMHZ19::OnDrawHandle() {
    // LOGN("%s::OnDrawHandle", typeid(this).name);

    char text[8];

    float rad = 0;
    if (_radSens) {
        rad = _radSens->getStatic();
    }
    int co2 = 400;
    if (_mhz19) {
        co2 = _mhz19->getCO2();
    }

    // uint32_t backColor = TFT_DARKGREY; //TFT_DARKGREEN;
    // if (rad > 30) {
    //     backColor = TFT_RED;
    // } else if (rad > 20) {
    //     backColor = TFT_YELLOW;
    // }

    uint32_t backColor = TFT_DARKCYAN;
    getSetting()->getSprite()->fillSprite(TFT_BLACK);
    // getSetting()->getSprite()->drawSmoothRoundRect(5, 5, 15, 10, 112, 125, TFT_RED, backColor);


    getSetting()->getSprite()->fillSmoothRoundRect(5, 5, 112, 125, 15, TFT_RED, backColor);
    getSetting()->getSprite()->fillSmoothRoundRect(123, 5, 112, 125, 15, TFT_YELLOW, backColor);

    // getSetting()->getSprite()->fillSmoothRoundRect(5, 5, 112, 125, 15, backColor);
    // getSetting()->getSprite()->fillSmoothRoundRect(123, 5, 112, 125, 15, backColor);

    uint16_t y2 = 67;
    uint16_t x2 = 120;

    //_sprite->drawFastVLine(x2, 0, TFT_WIDTH, TFT_WHITE);

    getSetting()->getSprite()->setTextColor(TFT_WHITE);
    getSetting()->getSprite()->setTextDatum(CC_DATUM);
    getSetting()->getSprite()->loadFont(Roboto_33);

    sprintf(text, "%d", co2);
    getSetting()->getSprite()->drawString(text, 60, 67);

    sprintf(text, "%.0f", rad);    //μR/h
    getSetting()->getSprite()->drawString(text, 180, 67);


    // _sprite->unloadFont();

    // _sprite->drawFloat(_bme280->getTemperature(), 0, x4, y4 + 7, 7);
    // _sprite->drawFloat(_bme280->getHumidity(), 0, x4 + x2, y4 + 7, 7);
    // _sprite->drawFloat(_bme280->getPressure(), 0, x4, y4 + y2 + 7, 7);
    // _sprite->drawFloat(rad, 0, x4 + x2, y4 + y2 + 7, 7);

    // _sprite->drawFastHLine(0, 0,             TFT_HEIGHT, TFT_WHITE);
    // _sprite->drawFastHLine(0, y2,            TFT_HEIGHT, TFT_WHITE);
    // _sprite->drawFastHLine(0, TFT_WIDTH - 1, TFT_HEIGHT, TFT_WHITE);


    // _sprite->setTextDatum(TL_DATUM);    
    // _sprite->fillRect(0,  0,  x2 - 36, 12, TFT_WHITE);
    // _sprite->fillRect(x2, 0,  x2 - 36, 12, TFT_WHITE);
    // _sprite->fillRect(0,  y2, x2 - 36, 12, TFT_WHITE);
    // _sprite->fillRect(x2, y2, x2 - 36, 12, TFT_WHITE);

    getSetting()->getSprite()->unloadFont();
}
