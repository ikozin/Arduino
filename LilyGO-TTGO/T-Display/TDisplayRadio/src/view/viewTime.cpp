#include "view/viewTime.h"
#include "fonts/DIGI56.h"
// #include "fonts/NotoSansSemiBold23.h"
// #include "fonts/Roboto_Bold22.h"
#include <LittleFS.h>
#include <string>

char* ViewTime::_dayOfWeeks[] = {
    (char*)"ВС",
    (char*)"ПН",
    (char*)"ВТ",
    (char*)"СР",
    (char*)"ЧТ",
    (char*)"ПТ",
    (char*)"СБ",
};

char* ViewTime::_months[] = {
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

uint16_t ViewTime::getDateColor(TimeData& date) {
    uint8_t day = date.dayOfTheWeek;
    if (day == 0 || day == 6) return COLOR_MAGENTA;
    return COLOR_WHITE;
}

void ViewTime::OnUpdate() {
  
    int value;
    char buffer[8];

    TimeData now = _controller->GetValue();

    _time[0] = '\0';
    value = now.hour;
    itoa(value, buffer, 10);
    if (value < 10) {
        strcat(_time, "0");
    }
    strcat(_time, buffer);
    strcat(_time, ":");
    value = now.minute;
    itoa(value, buffer, 10);
    if (value < 10) {
        strcat(_time, "0");
    }
    strcat(_time, buffer);

    // sprintf(text, "%02d:%02d", now.hour, now.minute);
    // Serial.println(text);
    _tft->startWrite();

    _tft->fillSprite(COLOR_BLACK);
    _tft->setTextColor(COLOR_WHITE);
    _tft->setTextDatum(CC_DATUM);
    _tft->setFreeFont(&DS_DIGI56pt7b);
    _tft->drawString(_time, TFT_HEIGHT >> 1, (TFT_WIDTH >> 1) + 20);
    _tft->unloadFont();

    strcpy(_date, _dayOfWeeks[now.dayOfTheWeek]);
    strcat(_date, " ");
    itoa(now.day, buffer, 10);
    strcat(_date, buffer);
    strcat(_date, " ");
    strcat(_date, _months[now.month]);
    strcat(_date, " ");
    itoa(now.year, buffer, 10);
    strcat(_date, buffer);

    // sprintf(text, "%s %d %s %d", dayOfWeeks[now.dayOfTheWeek], now.day, months[now.month], now.year);
    // Serial.println(text);

    _tft->setTextColor(getDateColor(now));
    _tft->loadFont("Roboto Bold23", LittleFS);
    _tft->drawString(_date, TFT_HEIGHT >> 1, 28);
    _tft->unloadFont();

    _tft->endWrite();
}
