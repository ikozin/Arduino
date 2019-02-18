#ifndef DateTimeModuleHelper_h
#define DateTimeModuleHelper_h

#include <Arduino.h>

typedef void  (*Func)(void);
typedef char* (*FuncGettter)(void);
typedef void  (*FuncSetter)(int, int, int);

class DateTimeModuleHelper
{
  private:
    Func  _handlerInit;
    Func  _handlerDump;
    FuncGettter _handlerGetDateTime;
    FuncSetter  _handlerSetDate;
    FuncSetter  _handlerSetTime;
  public:
    DateTimeModuleHelper(Func init, FuncGettter getDateTime, FuncSetter setDate, FuncSetter setTime, Func dump);
  public:
    void setup();
    void loop();
    void help();
    int getDayOfWeek(int day, int month, int year);
};

#endif
