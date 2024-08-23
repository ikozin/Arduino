#include "view/viewTime.h"
#include "fonts/DIGI56.h"
#include "fonts/NotoSansSemiBold23.h"

const char* dayOfWeeks[] = {
  "ВС",
  "ПН",
  "ВТ",
  "СР",
  "ЧТ",
  "ПТ",
  "СБ",
};

const char* months[] = {
  "Января",
  "Февраля",
  "Марта",
  "Апреля",
  "Мая",
  "Июня",
  "Июля",
  "Августа",
  "Сентября",
  "Октября",
  "Ноября",
  "Декабря",
};

uint16_t ViewTime::getDateColor(DateTime& date) {
  uint8_t day = date.dayOfTheWeek();
  if (day == 0 || day == 6) return TFT_MAGENTA;
  return TFT_WHITE;
}

void ViewTime::OnDrawHandle() {
    //LOGN("ViewTime::OnHandle")
    char text[64];

    DateTime now =_ctrl->getDateTime();
    sprintf(text, "%02d:%02d", now.hour(), now.minute());
    // Serial.println(text);

    _sprite->fillSprite(TFT_BLACK);
    _sprite->setTextColor(TFT_WHITE);
    _sprite->setTextDatum(CC_DATUM);
    _sprite->setFreeFont(&DS_DIGI56pt7b);
    _sprite->drawString(text, TFT_HEIGHT >> 1, (TFT_WIDTH >> 1) + 20);

    sprintf(text, "%s %d %s %d", dayOfWeeks[now.dayOfTheWeek()], now.day(), months[now.month() - 1], now.year());
    // Serial.println(text);

    _sprite->setTextColor(getDateColor(now));
    _sprite->loadFont(NotoSansSemiBold23);
    _sprite->drawString(text, TFT_HEIGHT >> 1, 28);
    _sprite->unloadFont();
}
