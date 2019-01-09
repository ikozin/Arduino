#define _CALC_TIME_
#define _CHECK_BOUNDS_

#include <Wire.h>
#include <ThreeWire.h>  
#include <RtcDS1302.h>

/*
https://datasheets.maximintegrated.com/en/ds/DS1302.pdf
http://tixer.ru/catalog/modules/rtc-modules/chasy_r_v_rtc_na_ds1302/

       -------------------
 VCC -|   __      ____    |
 GND -|   __    /      \  |
 CLK -|  |  |   |CR2032|  |
 DAT -|  |__|   \ ____ /  |
 RST -|                   |
       -------------------

*/

#define PIN_CLK  5
#define PIN_DAT  4
#define PIN_RST  2

ThreeWire myWire(PIN_DAT, PIN_CLK, PIN_RST); // IO, SCLK, CE
RtcDS1302<ThreeWire> rtc(myWire);

void setup()
{
  rtc.Begin();
  Serial.begin(9600);
  Serial.println(F("Start"));
  Serial.println(F("Set <CR> as end of line"));
  Serial.println(F("Set Date command: d=01.01.2019, format: <Day>.<Month>.<Year>"));
  Serial.println(F("Set Time command: t=13:31:59, format: <Hour>:<Minute>:<Second>"));
  Wire.begin();
}

void loop()
{
  int len = Serial.available();
  if (len)
  {
#ifdef _CALC_TIME_
    long time = micros();
#endif
    String text = Serial.readStringUntil('\r');
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
          RtcDateTime dt(year, month, day, 0, 0, 0);
          rtc.SetDateTime(dt);
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
          RtcDateTime now = rtc.GetDateTime();
          RtcDateTime dt(now.Year(), now.Month(), now.Day(), hour, minute, second);
          rtc.SetDateTime(dt);
        }
        break;
      default:
        Serial.println(text);
    }
#ifdef _CALC_TIME_
    time = micros() - time;
    Serial.print("micros:");
    Serial.println(time);
#endif
  }
  char text[128];
  RtcDateTime now = rtc.GetDateTime();
  sprintf(text, "Date=%02u.%02u.%04u, Time=%02u:%02u:%02u",
          now.Day(),
          now.Month(),
          now.Year(),
          now.Hour(),
          now.Minute(),
          now.Second());
  Serial.println(text);
  delay(1000);
}
