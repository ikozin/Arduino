#include "viewTime.h"

ViewTime::ViewTime(const char* name, TFT_eSPI* tft, View** currentView) : View(name, tft, currentView), sprite(tft) {
    sprite.createSprite(TFT_HEIGHT, TFT_WIDTH);
}

void ViewTime::OnHandle() {
    LOGN("ViewTime::OnHandle")
    char text[64];
    time_t now;
    struct tm timeinfo;

    time(&now);
    localtime_r(&now, &timeinfo);
    strftime(text, sizeof(text), "%H:%M", &timeinfo);

    sprite.fillRect(0, 0, sprite.width(), sprite.height(), TFT_BLACK);

    sprite.setTextColor(TFT_WHITE);
    //_tft->setTextDatum(CC_DATUM);

    sprite.drawCentreString(text, TFT_HEIGHT >> 1, TFT_WIDTH >> 1, 7);
//    _tft->loadFont(FONT_DIGIT_56);
//    _tft->drawString(text, TFT_HEIGHT >> 1, TFT_WIDTH >> 1);
//    _tft->unloadFont();
    sprite.pushSprite(0, 0);
}
