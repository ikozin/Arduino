#include "view/viewBme280.h"
#include "view/toolPng.h"
#include <string>

void ViewBme280::OnUpdate() {
    char text[16];
    Bme280Data value = _controller->GetValue();
    float temperature   = value.Temperature;
    float humidity      = value.Humidity;
    float pressure      = value.Pressure;

    uint32_t backColor = COLOR_BLACK;
    uint32_t foreColor = COLOR_WHITE;

    _tft->setTextDatum(CC_DATUM);
    _tft->setTextColor(foreColor);

    _tft->startWrite();

    _tft->fillSprite(backColor);
    _tft->drawSmoothRoundRect(0, 0, 15, 15, TFT_HEIGHT-1, TFT_WIDTH-1, foreColor, backColor);
    ToolPng::Draw(_tft, _env->getImage()->temp, 10);
    ToolPng::Draw(_tft, _env->getImage()->hum, 190, 60);
    
    _tft->loadFont("Roboto Bold52", LittleFS);
    dtostrf(temperature, 3, 1, text);
    strcat(text, "°");
    _tft->drawString(text, 130, 40);
    dtostrf(humidity, 3, 0, text);
    strcat(text, "%");
    _tft->drawString(text, 110, 100);
    _tft->unloadFont();

    _tft->endWrite();
}
