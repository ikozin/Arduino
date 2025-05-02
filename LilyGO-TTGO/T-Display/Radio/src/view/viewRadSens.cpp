#include "view/viewRadSens.h"
#include "fonts/CalibriBold12.h"
#include "fonts/Roboto33.h"

ViewRadSens::ViewRadSens(const char* name, ViewSettig* setting,  ControllerRadSens* radSens, SemaphoreHandle_t updateEvent):
                ViewT(name, setting, radSens, (uint64_t)50000, updateEvent) {
}

void ViewRadSens::OnDrawHandle() {
    // LOGN("%s::OnDrawHandle", typeid(this).name);
    ControllerRadSens* _radSens = static_cast<ControllerRadSens*>(_ctrl);

    uint32_t backColor;
    uint32_t foreColor;
    char text[8];

    float rad = 0;
    if (_radSens) {
        rad = _radSens->getDynamic();
    }
    
    getSetting()->getSprite()->loadFont(RobotoBold_33);
    getSetting()->getSprite()->fillSprite(TFT_BLACK);
    getSetting()->getSprite()->setTextDatum(CC_DATUM);
    // getSetting()->getSprite()->drawSmoothRoundRect(5, 5, 15, 10, 112, 125, TFT_RED, backColor);
    
    getSetting()->getSprite()->fillSmoothRoundRect(5, 5, 112, 125, 15, backColor, TFT_BLACK);
    getSetting()->getSprite()->setTextColor(foreColor);

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
