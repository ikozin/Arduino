#include "WebRadio.h"

int timeX           = 16;
int timeY           = 30;
int calendarY       = 94;
int dowY            = 4;

#define TimeDelay   500
long lastTimeTime       = 0;

char timeText[32]       = { 0 };
char dayOfWeekText[32]  = { 0 };
char calendarText[32]   = { 0 };

const char* dayOfWeek[] = {
  "ВОСКРЕСЕНИЕ",
  "ПОНЕДЕЛЬНИК",
  "ВТОРНИК",
  "СРЕДА",
  "ЧЕТВЕРГ",
  "ПЯТНИЦА",
  "СУББОТА",
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
  "Декабря"
};

void displayTimePage() {
  tft.fillScreen(TFT_BLACK);
  timeText[0]       = '\0';
  calendarText[0]   = '\0';
  dayOfWeekText[0]  = '\0';
}

void loopTimePage() {
  long t = millis();
  if (t - lastTimeTime < TimeDelay) return;
  lastTimeTime = t;


  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    return;
  }

  // Для уменьшения моргания выводм время в момент когда секуда = 0
  if (timeText[0] == '\0' || timeinfo.tm_sec == 0) {
    strftime(timeText, sizeof(timeText), "%H:%M ", &timeinfo);
    //tft.fillScreen(TFT_BLACK);
    tft.setFreeFont(&FreeMono18pt8b);
    tft.setTextSize(2);
    tft.setTextColor(TFT_GREEN, TFT_BLACK);
    tft.drawString(timeText, timeX, timeY);
  }

  // Для уменьшения моргания выводм календарь и день недели при переходе на следующие сутки
  if (calendarText[0] == '\0' || (timeinfo.tm_hour == 0 && timeinfo.tm_min == 0 && timeinfo.tm_sec == 0)) {
    tft.setFreeFont(&FreeMono12pt8b);
    tft.setTextSize(1);
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    sprintf(calendarText, "%2d %s %4d", timeinfo.tm_mday, utf8rus(months[timeinfo.tm_mon]), timeinfo.tm_year + 1900);
    tft.drawString(calendarText, ((TFT_HEIGHT - tft.textWidth(calendarText)) >> 2) + 8, calendarY);
    tft.setTextColor(TFT_YELLOW, TFT_BLACK);
    sprintf(dayOfWeekText, "%s", utf8rus(dayOfWeek[timeinfo.tm_wday])); 
    tft.drawString(dayOfWeekText, ((TFT_HEIGHT - tft.textWidth(dayOfWeekText)) >> 2) + 35, dowY);
  }
}
