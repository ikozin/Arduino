#pragma once

#include "controller.h"
#include <Preferences.h>
#include <RTClib.h>

class ControllerTime : public Controller {
    public:
        ControllerTime(const char* name, Preferences* prefs);
    public:
        DateTime getDateTime() { return _rtc.now(); }
    protected:
        virtual InitResponse_t OnInit() override;
        virtual bool OnIteration() override { return true; }
        virtual void OnHandle() override;
    private:
        Preferences* _prefs;
        RTC_DS3231 _rtc;
};
