#include "view/viewBme280.h"
#include "fonts/CalibriBold12.h"
#include "fonts/Roboto33.h"

void ViewBME280::OnDrawHandle() {
    //LOGN("ViewBME280::OnHandle")
    ControllerBme280* bme280 = static_cast<ControllerBme280*>(_ctrl);

    char text[32];
    float temperature   = bme280->getTemperature();    //28.7;
    float humidity      = bme280->getHumidity();       //23.9;
    float pressure      = bme280->getPressure();       //758.0;
    getSetting()->getSprite()->fillSprite(TFT_DARKGREY);

    uint16_t y2 = TFT_WIDTH >> 1;
    uint16_t y4 = TFT_WIDTH >> 2;
    uint16_t x2 = TFT_HEIGHT >> 1;
    uint16_t x4 = TFT_HEIGHT >> 2;
    
    // dtostrf(temperature, 3, 1, text);
    getSetting()->getSprite()->setTextColor(TFT_WHITE);
    getSetting()->getSprite()->setTextDatum(CC_DATUM);
    getSetting()->getSprite()->loadFont(Roboto_33);
    //_sprite->setFreeFont(&Orbitron_Light_32);
    sprintf(text, "%+.1f°", temperature);
    getSetting()->getSprite()->drawString(text, 60, y4 + 7);
    sprintf(text, "%.1f%%", humidity);
    getSetting()->getSprite()->drawString(text, 180, y4 + 7);
    sprintf(text, "%.1f мм рт. ст.", pressure);
    getSetting()->getSprite()->drawString(text, x2, y2 + y4 + 7);
    getSetting()->getSprite()->unloadFont();

    getSetting()->getSprite()->drawFastHLine(0, y2,            TFT_HEIGHT, TFT_WHITE);
}
