#include "controller/controllerDS3231.h"
#include "main.h"

ControllerDS3231::ControllerDS3231(const char* name, Preferences* prefs):
                    ControllerTime(name, prefs) {
}

InitResponse_t ControllerDS3231::OnInit() {
    if (_rtc.begin()) {
        time_t now;
        struct tm tm;
        time(&now);
        localtime_r(&now, &tm);
        // Если время не установлено, то берем его из DS3231
        if (now < 300) {
            DateTime currentTime = _rtc.now();
            tm.tm_year = currentTime.year() - 1900;
            tm.tm_mon = currentTime.month();
            tm.tm_mday = currentTime.day();
            tm.tm_hour = currentTime.hour();
            tm.tm_min = currentTime.minute();
            tm.tm_sec = currentTime.second();
            time_t t = mktime(&tm);
            struct timeval tv = { .tv_sec = t, .tv_usec = 0 };
            settimeofday(&tv, nullptr);
            _value = {
                .year = currentTime.year(),
                .month = currentTime.month(),
                .day = currentTime.day(),
                .hour = currentTime.hour(),
                .minute = currentTime.minute(),
                .second = currentTime.second()
            };
            // Serial.printf("%s::OnInit, Setup ESP32: %s\r\n", _name, asctime(&tm));
        }
        else {
            _rtc.adjust(DateTime(now + _prefs->getInt("tz", 10800)));
            DateTime currentTime = _rtc.now();
            _value = {
                .year = currentTime.year(),
                .month = currentTime.month(),
                .day = currentTime.day(),
                .hour = currentTime.hour(),
                .minute = currentTime.minute(),
                .second = currentTime.second()
            };
            // Serial.printf("%s::OnInit, Setup DS3231: %02d:%02d:%04d %02d:%02d:%02d\r\n", _name, 
            //     _value.day, _value.month, _value.year, _value.hour, _value.minute, _value.second);
        }      
        return OnInitResultStart;
    }
    return OnInitResultERROR;
}
