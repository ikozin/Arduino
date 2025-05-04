#include "view/viewRadSens.h"
#include "fonts/CalibriBold12.h"
#include "fonts/Roboto33.h"

ViewRadSens::ViewRadSens(const char* name, ViewSettig* setting,  ControllerRadSens* radSens, SemaphoreHandle_t updateEvent):
                ViewT(name, setting, radSens, 0, updateEvent) {
}

void DrawGraph(TFT_eSprite* sprite,  int x, int y, int height, int colwidth, float multiplier, RadSensData* data, size_t size) {
    for (size_t i = 0; i < size; i++) {
        int value = data[i].Dynamic * multiplier;
        LOG("%d (%d) ", value, (int)data[i].Dynamic);
        if (value > 0) {
            if (value > height) value = height;
            sprite->fillRect(x + (i * (colwidth + 1)), y - value, colwidth, value, TFT_BLUE);
        }
    }
    LOGN(""); 
}

void ViewRadSens::OnDrawHandle() {
    LOGN("%s::OnDrawHandle", _name);
    ControllerRadSens* _radSens = static_cast<ControllerRadSens*>(_ctrl);

    uint32_t backColor;
    uint32_t foreColor;
    char text[8];

    RadSensData* data = _radSens->GetWindow();
    size_t size =_radSens->Size();

    RadSensData value = _radSens->GetData();
    float radcounter = value.Dynamic; 
    
    getSetting()->getSprite()->loadFont(RobotoBold_33);
    getSetting()->getSprite()->fillSprite(TFT_BLACK);
    getSetting()->getSprite()->setTextDatum(CC_DATUM);
    
    getSetting()->getSprite()->fillSmoothRoundRect(5, 5, 230, 125, 15, backColor, TFT_BLACK);
    getSetting()->getSprite()->setTextColor(foreColor);

    foreColor = TFT_WHITE;
    backColor = (radcounter <= 15) ? TFT_GREEN: TFT_RED;
    foreColor = (radcounter <= 15) ? TFT_BLUE: TFT_BLACK;
    getSetting()->getSprite()->fillSmoothRoundRect(5, 5, 230, 125, 15, backColor, TFT_BLACK);
    getSetting()->getSprite()->setTextColor(foreColor);
    sprintf(text, "%.0f", radcounter);    //μR/h
    getSetting()->getSprite()->drawString(text, 120, 30);

    getSetting()->getSprite()->unloadFont();

    DrawGraph(getSetting()->getSprite(), 20, 120, 110, 6, 4, data, size);
}
