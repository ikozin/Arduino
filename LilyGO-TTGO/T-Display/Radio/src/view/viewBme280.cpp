#include "view/viewBme280.h"
#include "fonts/Roboto33.h"

void ViewBME280::OnDrawHandle() {
    // LOGN("%s::OnDrawHandle", _name);
    ControllerBme280* bme280 = static_cast<ControllerBme280*>(_ctrl);

    char text[8];
    Bme280Data value = bme280->GetValue();
    float temperature   = value.Temperature;
    float humidity      = value.Humidity;
    float pressure      = value.Pressure;

    uint32_t backColor = TFT_DARKCYAN;

    getSetting()->getSprite()->fillSprite(TFT_BLACK);

    getSetting()->getSprite()->fillSmoothRoundRect(5, 5, 230, 60, 15, backColor);
    getSetting()->getSprite()->fillSmoothRoundRect(5, 70, 112, 60, 15, backColor);
    getSetting()->getSprite()->fillSmoothRoundRect(123, 70, 112, 60, 15, backColor);
    
    getSetting()->getSprite()->fillSmoothRoundRect(190, 20, 6, 30, 3, TFT_RED, backColor);
    getSetting()->getSprite()->fillSmoothCircle(193, 44, 7, TFT_RED);

    // dtostrf(temperature, 3, 1, text);
    uint32_t colorTemp = TFT_BLUE;
    if (temperature > 15) {
        colorTemp = TFT_WHITE;
    }
    if (temperature > 20) {
        colorTemp = TFT_YELLOW;
    }

    getSetting()->getSprite()->loadFont(RobotoBold_33);

    getSetting()->getSprite()->setTextDatum(CC_DATUM);
    
    getSetting()->getSprite()->setTextColor(colorTemp);
    dtostrf(temperature, 3, 1, text);
    // sprintf(text, "%+.1f°", temperature);
    getSetting()->getSprite()->drawString(text, 120, 38);

    getSetting()->getSprite()->setTextColor(TFT_WHITE);
    dtostrf(pressure, 3, 1, text);
    // sprintf(text, "%.1f", pressure);
    getSetting()->getSprite()->drawString(text, 60, 107);

    getSetting()->getSprite()->setTextColor(TFT_WHITE);
    dtostrf(humidity, 3, 1, text);
    // sprintf(text, "%.1f%%", humidity);
    getSetting()->getSprite()->drawString(text, 180, 107);

    getSetting()->getSprite()->unloadFont();
}
