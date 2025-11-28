#include "controller/controllerTimeDS3231.h"
#include "main.h"

ControllerTimeDS3231::ControllerTimeDS3231(const char* name, Preferences* prefs):
                    ControllerTime(name, prefs) {
    _value = {
        .year = 2000,
        .month = 1,
        .day = 1,
        .hour = 0,
        .minute = 0,
        .second = 0,
        .dayOfTheWeek = 3
    };
}

bool ControllerTimeDS3231::OnInit() {
    if (!_rtc.begin()) return false;
    DateTime currentTime = _rtc.now();
    struct tm tm = {
        .tm_sec = currentTime.second(),
        .tm_min = currentTime.minute(),
        .tm_hour = currentTime.hour(),
        .tm_mday = currentTime.day(),
        .tm_mon = currentTime.month(),
        .tm_year = currentTime.year() - 1900,
    };
    struct timeval tv = {
        .tv_sec = mktime(&tm),
        .tv_usec = 0
    };
    settimeofday(&tv, nullptr);

    _value.year = currentTime.year();
    _value.month = currentTime.month();
    _value.day = currentTime.day();
    _value.hour = currentTime.hour();
    _value.minute = currentTime.minute();
    _value.second = currentTime.second();
    _value.dayOfTheWeek = currentTime.dayOfTheWeek();

    return true;
}

bool ControllerTimeDS3231::OnUpdate() {
    DateTime currentTime = _rtc.now();
    _value.year = currentTime.year();
    _value.month = currentTime.month();
    _value.day = currentTime.day();
    _value.hour = currentTime.hour();
    _value.minute = currentTime.minute();
    _value.second = currentTime.second();
    _value.dayOfTheWeek = currentTime.dayOfTheWeek();
    return true;
}
