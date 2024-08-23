#include "view/viewBme280.h"
#include "fonts/CalibriBold12.h"
#include "fonts/Roboto33.h"

void ViewBME280::OnDrawHandle() {
    //LOGN("ViewBME280::OnHandle")
    char text[32];
#ifdef STUB
    float temperature   = 28.7;
    float humidity      = 23.9;
    float pressure      = 758.0;
#else
    float temperature   = _ctrl->getTemperature();    //28.7;
    float humidity      = _ctrl->getHumidity();       //23.9;
    float pressure      = _ctrl->getPressure();       //758.0;
#endif
    _sprite->fillSprite(TFT_DARKGREY);

    uint16_t y2 = TFT_WIDTH >> 1;
    uint16_t y4 = TFT_WIDTH >> 2;
    uint16_t x2 = TFT_HEIGHT >> 1;
    uint16_t x4 = TFT_HEIGHT >> 2;

    _sprite->setTextColor(TFT_WHITE);
    _sprite->setTextDatum(CC_DATUM);
    _sprite->loadFont(Roboto_33);
    //_sprite->setFreeFont(&Orbitron_Light_32);
    sprintf(text, "%+.1f°", temperature);
    _sprite->drawString(text, 60, y4 + 7);
    sprintf(text, "%.1f%%", humidity);
    _sprite->drawString(text, 180, y4 + 7);
    sprintf(text, "%.1f мм рт. ст.", pressure);
    _sprite->drawString(text, x2, y2 + y4 + 7);
    _sprite->unloadFont();

    _sprite->drawFastHLine(0, y2,            TFT_HEIGHT, TFT_WHITE);
}
