#pragma once

#include "controller/controller.h"
#include <RTClib.h>

typedef struct _TimeData_ {
    uint16_t    year;
    uint8_t     month;
    uint8_t     day;

    uint8_t     hour;
    uint8_t     minute;
    uint8_t     second;
    uint8_t     dayOfTheWeek;
} TimeData;

// https://docs.espressif.com/projects/esp-idf/en/v5.0/esp32/api-reference/system/system_time.html
class ControllerTime : public Controller, public ISensor<TimeData> {
    public:
        ControllerTime(const char* name, Preferences* prefs) : Controller(name) {
            _updateTimeInSec = 1;
            _prefs = prefs;
        }
    protected:
        virtual IterationCode_t OnIteration() override { return IterationCode_t::Stop; }
        virtual void OnHandle() override {
            uint32_t delay = _updateTimeInSec * 1000 / portTICK_PERIOD_MS; 
            portTickType xLastWakeTime = xTaskGetTickCount();
            for (;;) {
                xTaskDelayUntil(&xLastWakeTime, delay);
                struct tm timeinfo;
                // time_t now;
                // time(&now);
                // localtime_r(&now, &timeinfo);
                getLocalTime(&timeinfo);
                _value = {
                    .year = (uint16_t)(timeinfo.tm_year + 1900), .month = (uint8_t)timeinfo.tm_mon, .day = (uint8_t)timeinfo.tm_mday,
                    .hour = (uint8_t)timeinfo.tm_hour, .minute = (uint8_t)timeinfo.tm_min, .second = (uint8_t)timeinfo.tm_sec,
                    .dayOfTheWeek = (uint8_t)timeinfo.tm_wday
                };
                // Serial.printf("%s::OnHandle: %02d:%02d:%04d %02d:%02d:%02d\r\n", _name, 
                //     _value.day, _value.month, _value.year, _value.hour, _value.minute, _value.second);
                FireUpdateEvent();
            }
        }        
    protected:
        Preferences* _prefs;
};
