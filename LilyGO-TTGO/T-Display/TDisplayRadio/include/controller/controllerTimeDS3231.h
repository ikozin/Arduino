#pragma once

#include "controller/controllerTime.h"

class ControllerTimeDS3231 : public ControllerTime {
    public:
        ControllerTimeDS3231(const char* name, Preferences* prefs);
    protected:
        virtual bool OnInit() override;
        virtual bool OnUpdate() override;
    private:
        RTC_DS3231 _rtc;
};
