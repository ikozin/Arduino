#include "view/viewRadSens.h"
#include "view/toolPng.h"
#include <string>

void ViewRadSens::OnUpdate() {
    char text[8];

    float radcounter = _controller->GetValue(); 
    
    uint32_t backColor = COLOR_BLACK;
    uint32_t foreColor = COLOR_WHITE;

    _tft->setTextDatum(CC_DATUM);
    _tft->setTextColor(foreColor);

    _tft->startWrite();

    _tft->fillSprite(COLOR_BLACK);
    _tft->drawSmoothRoundRect(0, 0, 15, 15, TFT_HEIGHT-1, TFT_WIDTH-1, COLOR_YELLOW, COLOR_BLACK);
    ToolPng::Draw(_tft, _env->getImage()->rads, 10);
    _tft->loadFont("Roboto Bold52", LittleFS);
    dtostrf(radcounter, 3, 1, text);        //μR/h
    // // sprintf(text, "%.1f", radcounter);
    _tft->drawString(text, 170, 60);
    _tft->unloadFont();
    _tft->loadFont("Roboto Bold20", LittleFS);
    _tft->drawString("мкР/Час", 170, 100);
    _tft->unloadFont();
    
    _tft->endWrite();
}
