#include "GyverTM1637.h" //https://alexgyver.ru/tm1637_display/

#define CLK 6
#define DIO 7

GyverTM1637 disp(CLK, DIO);
uint32_t Now, clocktimer;
boolean flag;

void setup()
{
  Serial.begin(9600);
  disp.clear();
  disp.brightness(7);  // 0 - 7)
}

void loop ()
{
  byte hrs = 21, mins = 55;
  uint32_t tmr;
  Now = millis();
  while (millis () - Now < 10000)
  {
    if (millis() - tmr > 500)
    {
      tmr = millis();
      flag = !flag;
      disp.point(flag);
      if (flag)
      {
        mins ++;
        if (mins > 59)
        {
          mins = 0;
          hrs++;
          if (hrs > 24) hrs = 0;
        }
        disp.displayClockTwist(hrs, mins, 35);
      }
    }
  }
  disp.point(0);
}
