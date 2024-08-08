#include "viewRadsMHZ19.h"
#include "fonts\CalibriBold12.h"
#include "fonts\Roboto33.h"

ViewRadsMHZ19::ViewRadsMHZ19(const char* name, View** currentView,  ControllerRadSens* radSens) : View(name, currentView) {
    assert(radSens);
    _radSens = radSens;
}

void ViewRadsMHZ19::OnHandle() {
    //LOGN("ViewRadsMHZ19::OnHandle")
    char text[32];
    float rad = _radSens->getStatic();
    // uint32_t backColor = TFT_DARKGREY; //TFT_DARKGREEN;
    // if (rad > 30) {
    //     backColor = TFT_RED;
    // } else if (rad > 20) {
    //     backColor = TFT_YELLOW;
    // }
    _sprite->fillSprite(TFT_DARKGREY);

    // uint16_t y2 = TFT_WIDTH >> 1;
    // uint16_t y4 = TFT_WIDTH >> 2;
    // uint16_t x2 = TFT_HEIGHT >> 1;
    // uint16_t x4 = TFT_HEIGHT >> 2;

    // _sprite->setTextColor(TFT_WHITE);
    // _sprite->setTextDatum(CC_DATUM);
    // _sprite->loadFont(Roboto_28);
    // sprintf(text, "%+.1f°", _bme280->getTemperature());
    // _sprite->drawString(text, 40, y4 + 7);

    // sprintf(text, "%.1f%%", _bme280->getHumidity());
    // _sprite->drawString(text, 120, y4 + 7);

    // sprintf(text, "%.1fм", _bme280->getPressure());
    // _sprite->drawString(text, 200, y4 + 7);

    // sprintf(text, "%.0f μR/h", rad);
    // _sprite->drawString(text, x4 + x2, y4 + y2 + 7);
    // _sprite->unloadFont();

    // _sprite->drawFloat(_bme280->getTemperature(), 0, x4, y4 + 7, 7);
    // _sprite->drawFloat(_bme280->getHumidity(), 0, x4 + x2, y4 + 7, 7);
    // _sprite->drawFloat(_bme280->getPressure(), 0, x4, y4 + y2 + 7, 7);
    // _sprite->drawFloat(rad, 0, x4 + x2, y4 + y2 + 7, 7);

    // _sprite->drawFastHLine(0, 0,             TFT_HEIGHT, TFT_WHITE);
    // _sprite->drawFastHLine(0, y2,            TFT_HEIGHT, TFT_WHITE);
    // _sprite->drawFastHLine(0, TFT_WIDTH - 1, TFT_HEIGHT, TFT_WHITE);

    // _sprite->drawFastVLine(0, 0,              TFT_WIDTH, TFT_WHITE);
    // _sprite->drawFastVLine(x2, 0,             TFT_WIDTH, TFT_WHITE);
    // _sprite->drawFastVLine(TFT_HEIGHT - 1, 0, TFT_WIDTH, TFT_WHITE);

    // _sprite->setTextDatum(TL_DATUM);    
    // _sprite->fillRect(0,  0,  x2 - 36, 12, TFT_WHITE);
    // _sprite->fillRect(x2, 0,  x2 - 36, 12, TFT_WHITE);
    // _sprite->fillRect(0,  y2, x2 - 36, 12, TFT_WHITE);
    // _sprite->fillRect(x2, y2, x2 - 36, 12, TFT_WHITE);

    // _sprite->setTextColor(TFT_BLUE);
    // _sprite->loadFont(calibri_bold_12);
    // _sprite->drawString("ТЕМПЕРАТУРА", 4,      2);
    // _sprite->drawString("ВЛАЖНОСТЬ",   x2 + 4, 2);
    // _sprite->drawString("ДАВЛЕНИЕ",    4,      y2 + 2);
    // _sprite->drawString("РАДИАЦИЯ",    x2 + 4, y2 + 2);
    // _sprite->unloadFont();
}
