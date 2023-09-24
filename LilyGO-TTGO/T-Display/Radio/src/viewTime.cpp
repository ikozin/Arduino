#include "viewTime.h"
#include "fonts/DIGI56.h"
#include "fonts/NotoSansSemiBold24.h"

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


ViewTime::ViewTime(const char* name, View** currentView, ControllerTime* device) : View(name, currentView) {
    assert(device);
    _device = device;
}

void ViewTime::OnHandle() {
    LOGN("ViewTime::OnHandle")
    char text[64];

    DateTime now =_device->getDateTime();
    sprintf(text, "%02d:%02d", now.hour(), now.minute());
    Serial.println(text);

    _sprite->fillSprite(TFT_BLACK);
    _sprite->setTextColor(TFT_WHITE);
    _sprite->setTextDatum(CC_DATUM);
    _sprite->setFreeFont(&DS_DIGI56pt7b);
    _sprite->drawString(text, TFT_HEIGHT >> 1, (TFT_WIDTH >> 1) + 20);

    sprintf(text, "%s %d %s %d", dayOfWeeks[now.dayOfTheWeek()], now.day(), months[now.month() - 1], now.year());
    Serial.println(text);

    _sprite->loadFont(NotoSansSemiBold24);
    _sprite->drawString(text, TFT_HEIGHT >> 1, 28);
    _sprite->unloadFont();
}
