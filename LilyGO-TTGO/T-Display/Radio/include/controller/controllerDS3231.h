#pragma once

#include "controller/controllerTime.h"
#include <Preferences.h>

class ControllerDS3231 : public ControllerTime {
    public:
        ControllerDS3231(const char* name, Preferences* prefs);
    protected:
        virtual InitResponse_t OnInit() override;
    private:
        RTC_DS3231 _rtc;
};
