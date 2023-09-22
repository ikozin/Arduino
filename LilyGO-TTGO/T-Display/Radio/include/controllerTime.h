#ifndef _CONTROLLERTIME_H_
#define _CONTROLLERTIME_H_

#include "controller.h"
#include <RTClib.h>

class ControllerTime : public Controller {
    public:
        ControllerTime(const char* name);
    protected:
        virtual void OnHandle();
    private:
        RTC_DS3231 _rtc;
};

#endif  //_CONTROLLERTIME_H_