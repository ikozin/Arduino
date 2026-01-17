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
class ControllerTime : public ControllerValue<TimeData> {
    public:
        ControllerTime(const char* name, Preferences* prefs) : ControllerValue(name, 1000) {
            _prefs = prefs;
        }
    protected:
        Preferences* _prefs;
};
 