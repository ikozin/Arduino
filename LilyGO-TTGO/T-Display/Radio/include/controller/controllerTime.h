#pragma once

#include "controller/controller.h"
#include <Preferences.h>
#include <RTClib.h>

class ControllerTime : public Controller {
    public:
        ControllerTime(const char* name, Preferences* prefs);
    public:
        DateTime getDateTime() const { return _currentTime; }
    protected:
        virtual InitResponse_t OnInit() override;
        virtual IterationCode_t OnIteration() override { return IterationCode_t::Stop; }
        virtual void OnHandle() override;
    private:
        DateTime _currentTime;
        Preferences* _prefs;
        RTC_DS3231 _rtc;
};
