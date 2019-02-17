#define _CALC_TIME_
#define _CHECK_BOUNDS_

#include "DateTimeModuleHelper.h"
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

class Module: public DateTimeModuleHelper
{
  private:
    char text[128];
    ThreeWire ds1302;
    RtcDS1302<ThreeWire> rtc;
  public:
    Module(): ds1302(PIN_DAT, PIN_CLK, PIN_RST), rtc(ds1302) {}

    void init()
    {
      rtc.Begin();
      Wire.begin();
    }
    
    char* getDateTime()
    {
      RtcDateTime now = rtc.GetDateTime();
      sprintf(text, "Date=%02u.%02u.%04u, Time=%02u:%02u:%02u",
          now.Day(),
          now.Month(),
          now.Year(),
          now.Hour(),
          now.Minute(),
          now.Second());
      return text;
    }

    void setDate(int year, int month, int day)
    {
      RtcDateTime dt(year, month, day, 0, 0, 0);
      rtc.SetDateTime(dt);
    }

    void setTime(int hour, int minute, int second)
    {
      RtcDateTime now = rtc.GetDateTime();
      RtcDateTime dt(now.Year(), now.Month(), now.Day(), hour, minute, second);
      rtc.SetDateTime(dt);
    }  
} helper;

void setup()
{
  helper.setup();
}

void loop()
{
  helper.loop();
}
