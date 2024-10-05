#include "view/viewRadsMHZ19.h"
#include "fonts/CalibriBold12.h"
#include "fonts/Roboto33.h"

ViewRadsMHZ19::ViewRadsMHZ19(const char* name, ViewSettig* setting,  ControllerRadSens* radSens, ControllerMHZ19* mhz19, SemaphoreHandle_t updateEvent):
                ViewT(name, setting, radSens, (uint64_t)50000, updateEvent) {
    _co2_Min = 800;
    _co2_Max = 1200;
    _mhz19 = mhz19;
}

int counter = 0;
int cnt = 0;
void ViewRadsMHZ19::OnDrawHandle() {
    // LOGN("%s::OnDrawHandle", typeid(this).name);
    ControllerRadSens* _radSens = static_cast<ControllerRadSens*>(_ctrl);

    uint32_t backColor;
    uint32_t foreColor;
    char text[8];

    float rad = 0;
    if (_radSens) {
        rad = _radSens->getDynamic();
    }
    int co2 = 0;
    if (_mhz19) {
        co2 = _mhz19->getCO2();
    }
    
    getSetting()->getSprite()->loadFont(RobotoBold_33);
    getSetting()->getSprite()->fillSprite(TFT_BLACK);
    getSetting()->getSprite()->setTextDatum(CC_DATUM);
    // getSetting()->getSprite()->drawSmoothRoundRect(5, 5, 15, 10, 112, 125, TFT_RED, backColor);
    
    auto co2level = getCO2Level(co2);
    switch (co2level) {
        case Co2Level::Min:
            foreColor = TFT_BLUE;
            backColor = TFT_GREEN;
            counter = 0;
            break;
        case Co2Level::Middle:
            foreColor = TFT_BLACK;
            backColor = TFT_YELLOW;
            counter ++;
            break;
        case Co2Level::Max:
            foreColor = TFT_BLACK;
            backColor = TFT_RED;
            counter ++;
            break;
    }
    if (counter < 10) {
        getSetting()->getSprite()->fillSmoothRoundRect(5, 5, 112, 125, 15, backColor, TFT_BLACK);
        getSetting()->getSprite()->setTextColor(foreColor);
        sprintf(text, "%d", co2);
        getSetting()->getSprite()->drawString(text, 60, 67);
    }
    if (counter > 14) {
        counter = 0;
    }
    foreColor = TFT_WHITE;
    backColor = (rad <= 15) ? TFT_GREEN: TFT_RED;
    foreColor = (rad <= 15) ? TFT_BLUE: TFT_BLACK;
    getSetting()->getSprite()->fillSmoothRoundRect(123, 5, 112, 125, 15, backColor, TFT_BLACK);
    getSetting()->getSprite()->setTextColor(foreColor);
    sprintf(text, "%.0f", rad);    //μR/h
    getSetting()->getSprite()->drawString(text, 180, 67);

    // getSetting()->getSprite()->fillSmoothRoundRect(5, 5, 112, 125, 15, backColor);
    // getSetting()->getSprite()->fillSmoothRoundRect(123, 5, 112, 125, 15, backColor);

    getSetting()->getSprite()->unloadFont();
}
