#define _CALC_TIME_
#define _CHECK_BOUNDS_

#include <Wire.h>  
#include <ThreeWire.h>  
#include <RtcDS1302.h>
#include "DateTimeModuleHelper.h"

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

ThreeWire myWire(PIN_DAT, PIN_CLK, PIN_RST);
RtcDS1302<ThreeWire> Rtc(myWire);

char text[128];

void InitModule()
{
  Rtc.Begin();
  Wire.begin();
}
    
char* GetCurrentDateTime()
{
  RtcDateTime now = Rtc.GetDateTime();
  sprintf(text, "Date=%02u.%02u.%04u, Time=%02u:%02u:%02u",
      now.Day(),
      now.Month(),
      now.Year(),
      now.Hour(),
      now.Minute(),
      now.Second());
  return text;
}

void SetCurrentDate(int year, int month, int day)
{
  RtcDateTime dt(year, month, day, 0, 0, 0);
  Rtc.SetDateTime(dt);
}

void SetCurrentTime(int hour, int minute, int second)
{
  RtcDateTime now = Rtc.GetDateTime();
  RtcDateTime dt(now.Year(), now.Month(), now.Day(), hour, minute, second);
  Rtc.SetDateTime(dt);
}  

DateTimeModuleHelper helper(InitModule, GetCurrentDateTime, SetCurrentDate, SetCurrentTime, NULL);

void setup()
{
  helper.setup();
}

void loop()
{
  helper.loop();
}
