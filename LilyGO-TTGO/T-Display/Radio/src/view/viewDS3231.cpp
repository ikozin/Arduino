#include "view/viewDS3231.h"
#include "fonts/DIGI56.h"
#include "fonts/NotoSansSemiBold23.h"

char* ViewDS3231::dayOfWeeks[] = {
    (char*)"ВС",
    (char*)"ПН",
    (char*)"ВТ",
    (char*)"СР",
    (char*)"ЧТ",
    (char*)"ПТ",
    (char*)"СБ",
};

char* ViewDS3231::months[] = {
    (char*)"",
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

uint16_t ViewDS3231::getDateColor(TimeData& date) {
    uint8_t day = date.dayOfTheWeek;
    if (day == 0 || day == 6) return TFT_MAGENTA;
    return TFT_WHITE;
}

void ViewDS3231::OnDrawHandle() {
    // LOGN("%s::OnDrawHandle", _name);
    ControllerTime* time = static_cast<ControllerTime*>(_ctrl);
    
    int value;
    char text[32], buffer[8];

    TimeData now = time->GetData();

    text[0] = '\0';
    value = now.hour;
    itoa(value, buffer, 10);
    if (value < 10) {
        strcat(text, "0");
    }
    strcat(text, buffer);
    strcat(text, ":");
    value = now.minute;
    itoa(value, buffer, 10);
    if (value < 10) {
        strcat(text, "0");
    }
    strcat(text, buffer);

    sprintf(text, "%02d:%02d", now.hour, now.minute);
    Serial.println(text);

    getSetting()->getSprite()->fillSprite(TFT_BLACK);
    getSetting()->getSprite()->setTextColor(TFT_WHITE);
    getSetting()->getSprite()->setTextDatum(CC_DATUM);
    getSetting()->getSprite()->setFreeFont(&DS_DIGI56pt7b);
    getSetting()->getSprite()->drawString(text, TFT_HEIGHT >> 1, (TFT_WIDTH >> 1) + 20);

    text[0] = '\0';
    strcat(text, dayOfWeeks[now.dayOfTheWeek]);
    strcat(text, " ");
    itoa(now.day, buffer, 10);
    strcat(text, buffer);
    strcat(text, " ");
    strcat(text, months[now.month]);
    strcat(text, " ");
    itoa(now.year, buffer, 10);
    strcat(text, buffer);

    sprintf(text, "%s %d %s %d", dayOfWeeks[now.dayOfTheWeek], now.day, months[now.month], now.year);
    Serial.println(text);

    getSetting()->getSprite()->setTextColor(getDateColor(now));
    getSetting()->getSprite()->loadFont(NotoSansSemiBold23);
    getSetting()->getSprite()->drawString(text, TFT_HEIGHT >> 1, 28);
    getSetting()->getSprite()->unloadFont();
}
