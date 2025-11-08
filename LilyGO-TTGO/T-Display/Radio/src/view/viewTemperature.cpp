#include "view/viewTemperature.h"
#include "fonts/CalibriBold12.h"
#include "fonts/Roboto33.h"

ViewTemperature::ViewTemperature(const char* name, ViewSettig* setting,  ControllerBme280* bme280, SemaphoreHandle_t updateEvent):
                ViewT(name, setting, bme280, 0, updateEvent) {
}

void ViewTemperature::OnDrawHandle() {
    // LOGN("%s::OnDrawHandle", _name);
    ControllerBme280* _bme280 = static_cast<ControllerBme280*>(_ctrl);
    char text[8];

    Bme280Data value = _bme280->GetData(); 
    
    getSetting()->getSprite()->loadFont(RobotoBold_33);
    getSetting()->getSprite()->fillSprite(TFT_BLACK);
    getSetting()->getSprite()->setTextDatum(CC_DATUM);

    uint32_t backColor = TFT_WHITE;
    uint32_t foreColor = TFT_BLUE;
    getSetting()->getSprite()->fillSmoothRoundRect(5, 5, 230, 125, 15, backColor, TFT_BLACK);
    // getSetting()->getSprite()->pushImage(18, 12, 32, 32, reinterpret_cast<uint16_t*>(image));
    getSetting()->getSprite()->setTextColor(foreColor);
    dtostrf(value.Temperature, 3, 1, text);
    // sprintf(text, "%.1f", temp);
    getSetting()->getSprite()->drawString(text, 120, 30);

    getSetting()->getSprite()->unloadFont();
}
