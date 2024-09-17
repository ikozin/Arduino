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
            _currentTime = _rtc.now();
            tm.tm_year = _currentTime.year() - 1900;
            tm.tm_mon = _currentTime.month();
            tm.tm_mday = _currentTime.day();
            tm.tm_hour = _currentTime.hour();
            tm.tm_min = _currentTime.minute();
            tm.tm_sec = _currentTime.second();
            time_t t = mktime(&tm);
            struct timeval tv = { .tv_sec = t, .tv_usec = 0 };
            settimeofday(&tv, nullptr);
            Serial.printf("%s::OnHandle, Setup ESP32: %s\r\n", _name, asctime(&tm));
        }
        else {
            _rtc.adjust(DateTime(now + _prefs->getInt("tz", 10800)));
            _currentTime = _rtc.now();
            Serial.printf("%s::OnHandle, Setup DS3231: %02d:%02d:%02d\r\n",
                             _name, _currentTime.hour(), _currentTime.minute(), _currentTime.second());
        }      
        return OnInitResultStart;
    }
    return OnInitResultERROR;
}

void ControllerDS3231::OnHandle() {
    uint32_t delay = _updateTimeInSec * 1000 / portTICK_PERIOD_MS; 
    portTickType xLastWakeTime = xTaskGetTickCount();
    for (;;) {
        xTaskDelayUntil(&xLastWakeTime, delay);
        Lock();
        _currentTime = _rtc.now();
        Unlock();
        FireUpdateEvent();
    }
}
