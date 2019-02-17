#define _CALC_TIME_
#define _CHECK_BOUNDS_

#include "DateTimeModuleHelper.h"

class Module: public DateTimeModuleHelper
{
  private:
      String text;
  public:

    char* getDateTime()
    {
      int result = getDayOfWeek(2019, 2, 17);
      text = result;
      return text.c_str();
    }

    void setDate(int year, int month, int day)
    {
    }

    void setTime(int hour, int minute, int second)
    {
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
