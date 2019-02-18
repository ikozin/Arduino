#include "DateTimeModuleHelper.h"


DateTimeModuleHelper::DateTimeModuleHelper(Func init, FuncGettter getDateTime, FuncSetter setDate, FuncSetter setTime, Func dump)
{
  _handlerInit = init;
  _handlerDump = dump;
  _handlerGetDateTime = getDateTime;
  _handlerSetDate = setDate;
  _handlerSetTime = setTime;
}

void DateTimeModuleHelper::setup()
{
  Serial.begin(9600);
  Serial.println(F("Start"));
  help();
  if (_handlerInit != NULL) _handlerInit();
}

void DateTimeModuleHelper::loop()
{
  int len = Serial.available();
  if (len)
  {
#ifdef _CALC_TIME_
    long time = micros();
#endif
    String text = Serial.readString();
    text.trim();
    text.toLowerCase();
    switch (text[0])
    {
      case 'd':
        if (text.length() == 12)
        {
          char* p = text.begin();
          text.remove(0, 2);
          text.setCharAt(2, 0);
          text.setCharAt(5, 0);

          int day = atol(p);
          p += 3;
          int month = atol(p);
          p += 3;
          int year = atol(p);
#ifdef _CHECK_BOUNDS_
          if (day < 0 || day > 31) break;
          if (month < 0 || month > 12) break;
          if (year < 2000) break;
#endif
          if (_handlerSetDate != NULL) _handlerSetDate(year, month, day);
        }
        break;
      case 't':
        if (text.length() == 10)
        {
          char* p = text.begin();
          text.remove(0, 2);
          text.setCharAt(2, 0);
          text.setCharAt(5, 0);

          int hour = atol(p);
          p += 3;
          int minute = atol(p);
          p += 3;
          int second = atol(p);
#ifdef _CHECK_BOUNDS_
          if (hour < 0 || hour > 23) break;
          if (minute < 0 || minute > 59) break;
          if (second < 0 || second > 59) break;
#endif
          if (_handlerSetTime != NULL) _handlerSetTime(hour, minute, second);
        }
        break;
      case 'i':
        if (_handlerDump != NULL) _handlerDump();
        break;
      default:
        Serial.println(text);
        help();
    }
#ifdef _CALC_TIME_
    time = micros() - time;
    Serial.print("micros:");
    Serial.println(time);
#endif
  }
  if (_handlerGetDateTime != NULL) Serial.println(_handlerGetDateTime());
  delay(1000);
}

void DateTimeModuleHelper::help()
{
  Serial.println(F("Set Date command: d=01.01.2019, format: <Day>.<Month>.<Year>"));
  Serial.println(F("Set Time command: t=13:31:59, format: <Hour>:<Minute>:<Second>"));
  Serial.println(F("Get Dump command: i"));
}

int DateTimeModuleHelper::getDayOfWeek(int year, int month, int day)
{
  int a = (14 - month) / 12;
  int y = year - a;
  int m = month + 12 * a - 2;
  int dayOfWeek = 1 + (7000 + (day + y + y / 4 - y / 100 + y / 400 + (31 * m) / 12)) % 7;
  return dayOfWeek;
}
