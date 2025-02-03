#pragma once

#include "controller/controllerTime.h"
// https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/system/system_time.html
#define NUM_SNTP_TIMERS 1

class ControllerTimeSNTP : public ControllerTime {
    public:
        ControllerTimeSNTP(const char* name, Preferences* prefs):
            ControllerTime(name, prefs) { }
    protected:
        TimerHandle_t _handler = nullptr;
    protected:
        virtual InitResponse_t OnInit() override;
        virtual void OnHandle() override {};
    private:
        static void TimerCallback(TimerHandle_t pxTimer);
};
