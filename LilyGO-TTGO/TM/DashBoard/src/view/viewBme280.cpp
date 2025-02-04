#include "view/viewBme280.h"
#include "fonts/Roboto33.h"

void ViewBME280::OnDrawHandle() {
    LOG("%s::OnDrawHandle\r\n", _name);
    ControllerBme280* bme280 = static_cast<ControllerBme280*>(_ctrl);
    LGFX* tft = getSetting()->getDisplay();

    char text[8];
    float temperature   = bme280->getTemperature();
    float humidity      = bme280->getHumidity();
    float pressure      = bme280->getPressure();

    // uint32_t backColor = TFT_DARKCYAN;

    // tft->fillSprite(TFT_BLACK);

    // tft->fillSmoothRoundRect(5, 5, 230, 60, 15, backColor);
    // tft->fillSmoothRoundRect(5, 70, 112, 60, 15, backColor);
    // tft->fillSmoothRoundRect(123, 70, 112, 60, 15, backColor);
    
    // tft->fillSmoothRoundRect(190, 20, 6, 30, 3, TFT_RED, backColor);
    // tft->fillSmoothCircle(193, 44, 7, TFT_RED);

    // // dtostrf(temperature, 3, 1, text);
    // uint32_t colorTemp = TFT_BLUE;
    // if (temperature > 15) {
    //     colorTemp = TFT_WHITE;
    // }
    // if (temperature > 20) {
    //     colorTemp = TFT_YELLOW;
    // }

    // tft->loadFont(RobotoBold_33);
    // tft->setTextDatum(CC_DATUM);
    
    // tft->setTextColor(colorTemp);
    // sprintf(text, "%+.1f°", temperature);
    // tft->drawString(text, 120, 38);

    // tft->setTextColor(TFT_WHITE);
    // sprintf(text, "%.1f", pressure);
    // tft->drawString(text, 60, 107);

    // tft->setTextColor(TFT_WHITE);
    // sprintf(text, "%.1f%%", humidity);
    // tft->drawString(text, 180, 107);

    // tft->unloadFont();
}
