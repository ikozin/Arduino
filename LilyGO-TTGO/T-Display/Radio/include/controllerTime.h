#ifndef _CONTROLLERTIME_H_
#define _CONTROLLERTIME_H_

#include "controller.h"
#include <Preferences.h>
#include <RTClib.h>

#define UPDATE_CLOCK_TIME (1000 / portTICK_RATE_MS)

class ControllerTime : public Controller {
    public:
        ControllerTime(const char* name, Preferences* prefs);
    public:
        DateTime getDateTime() { return _rtc.now(); }
    protected:
        virtual void OnHandle();
    private:
        Preferences* _prefs;
        RTC_DS3231 _rtc;
};

#endif  //_CONTROLLERTIME_H_