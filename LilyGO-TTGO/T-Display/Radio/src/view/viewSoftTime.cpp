#include "view/viewSoftTime.h"
#include "fonts/DIGI56.h"
#include "fonts/NotoSansSemiBold23.h"
#include <string>

char* ViewSoftTime::dayOfWeeks[] = {
    (char*)"ВС",
    (char*)"ПН",
    (char*)"ВТ",
    (char*)"СР",
    (char*)"ЧТ",
    (char*)"ПТ",
    (char*)"СБ",
};

char* ViewSoftTime::months[] = {
    (char*)"Января",
    (char*)"Февраля",
    (char*)"Марта",
    (char*)"Апреля",
    (char*)"Мая",
    (char*)"Июня",
    (char*)"Июля",
    (char*)"Августа",
    (char*)"Сентября",
    (char*)"Октября",
    (char*)"Ноября",
    (char*)"Декабря",
};

ViewSoftTime::ViewSoftTime(const char* name, ViewSettig* setting, ControllerSoftTime* ctrl, SemaphoreHandle_t updateEvent): 
                            ViewT(name, setting, ctrl, (uint64_t)50000, updateEvent), _textSprite(setting->getDisplay()) {
    _textSprite.createSprite(TFT_HEIGHT, 24);
    _textX = TFT_HEIGHT-1;
};

uint16_t ViewSoftTime::getDateColor(DateTime& date) {
    uint8_t day = date.dayOfTheWeek();
    if (day == 0 || day == 6) return TFT_MAGENTA;
    return TFT_WHITE;
}

void ViewSoftTime::OnInit() {
    _textSprite.loadFont(NotoSansSemiBold23);
    _textSprite.setTextColor(TFT_WHITE, TFT_BLACK);
}

void ViewSoftTime::OnDrawHandle() {
    // LOGN("ViewSoftTime::OnDrawHandle")
    ControllerSoftTime* softtime = static_cast<ControllerSoftTime*>(_ctrl);

    int value;
    char text[32], buffer[8];

    DateTime now = softtime->getDateTime();

    text[0] = '\0';
    value = now.hour();
    itoa(value, buffer, 10);
    if (value < 10) {
        strcat(text, "0");
    }
    strcat(text, buffer);
    strcat(text, ":");
    value = now.minute();
    itoa(value, buffer, 10);
    if (value < 10) {
        strcat(text, "0");
    }
    strcat(text, buffer);

    // sprintf(text, "%02d:%02d", now.hour(), now.minute());
    // Serial.println(text);

    getSetting()->getSprite()->fillSprite(TFT_BLACK);
    getSetting()->getSprite()->setTextColor(TFT_WHITE);
    getSetting()->getSprite()->setTextDatum(CC_DATUM);
    getSetting()->getSprite()->setFreeFont(&DS_DIGI56pt7b);
    getSetting()->getSprite()->drawString(text, TFT_HEIGHT >> 1, (TFT_WIDTH >> 1) + 20);
    getSetting()->getSprite()->unloadFont();

    text[0] = '\0';
    strcat(text, dayOfWeeks[now.dayOfTheWeek()]);
    strcat(text, " ");
    itoa(now.day(), buffer, 10);
    strcat(text, buffer);
    strcat(text, " ");
    strcat(text, months[now.month() - 1]);
    strcat(text, " ");
    itoa(now.year(), buffer, 10);
    strcat(text, buffer);

    // sprintf(text, "%s %d %s %d", dayOfWeeks[now.dayOfTheWeek()], now.day(), months[now.month() - 1], now.year());
    // Serial.println(text);

    _textSprite.fillSprite(TFT_BLACK);
    // _textSprite.setTextColor(TFT_WHITE, TFT_BLACK);
    // _textSprite.loadFont(NotoSansSemiBold23);
    // _textSprite.loadFont(NotoSansSemiBold23);
    // _textSprite.setTextDatum(TL_DATUM);
    _textSprite.drawString(text, 0, 1);
    // _textSprite.unloadFont();
    _textSprite.pushToSprite(getSetting()->getSprite(), _textX, 0);
    _textX -= 1;
    if (_textX < -TFT_HEIGHT) _textX = TFT_HEIGHT-1;
}
