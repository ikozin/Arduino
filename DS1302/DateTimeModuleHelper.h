#ifndef DateTimeModuleHelper_h
#define DateTimeModuleHelper_h

#include <Arduino.h>

class DateTimeModuleHelper
{
  protected:
    int getDayOfWeek(int day, int month, int year);
  public:
    void setup();
    void loop();
    void help();
  public:
    virtual void init() {};
    virtual char* getDateTime() = 0;
    virtual void setDate(int year, int month, int day) = 0;
    virtual void setTime(int hour, int minute, int second) = 0;
    virtual void dump();
};

#endif
