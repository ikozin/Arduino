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

    uint16_t y2 = TFT_WIDTH >> 1;
    uint16_t y4 = TFT_WIDTH >> 2;
    uint16_t x2 = TFT_HEIGHT >> 1;
    uint16_t x4 = TFT_HEIGHT >> 2;

    uint32_t backColor = 0x024E;

    getSetting()->getSprite()->fillSprite(TFT_BLACK);
    getSetting()->getSprite()->fillSmoothRoundRect(5, 5, 112, 60, 15, backColor);
    getSetting()->getSprite()->fillSmoothRoundRect(123, 5, 112, 60, 15, backColor);
    getSetting()->getSprite()->fillSmoothRoundRect(5, 70, 230, 60, 15, backColor);
    
    // getSetting()->getSprite()->fillSmoothCircle(5+10,5+25,5,TFT_ORANGE);


    // // dtostrf(temperature, 3, 1, text);
    uint32_t colorTemp = TFT_BLUE;
    if (temperature > 15) {
        colorTemp = TFT_WHITE;
    }
    if (temperature > 20) {
        colorTemp = TFT_YELLOW;
    }
    if (temperature > 25) {
        colorTemp = TFT_RED;
    }

    getSetting()->getSprite()->loadFont(RobotoBold_33);
    getSetting()->getSprite()->setTextDatum(CC_DATUM);
    //_sprite->setFreeFont(&Orbitron_Light_32);

    getSetting()->getSprite()->setTextColor(colorTemp);
    sprintf(text, "%+.1f°", temperature);
    getSetting()->getSprite()->drawString(text, 60, 38);

    getSetting()->getSprite()->setTextColor(TFT_WHITE);
    sprintf(text, "%.1f%%", humidity);
    getSetting()->getSprite()->drawString(text, 180, 38);

    // getSetting()->getSprite()->unloadFont();
    // getSetting()->getSprite()->loadFont(calibri_bold_12);

    // sprintf(text, "мм рт. ст.", pressure);
    sprintf(text, "%.1f", pressure);
    getSetting()->getSprite()->drawString(text, x2, y2 + y4 + 7);
    getSetting()->getSprite()->unloadFont();
}
