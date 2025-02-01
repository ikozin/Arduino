#pragma once

#include "controller/controllerTime.h"

class ControllerTimeDS3231 : public ControllerTime {
    public:
        ControllerTimeDS3231(const char* name, Preferences* prefs);
    protected:
        virtual InitResponse_t OnInit() override;
        virtual void OnHandle() override;
    private:
        RTC_DS3231 _rtc;
};
