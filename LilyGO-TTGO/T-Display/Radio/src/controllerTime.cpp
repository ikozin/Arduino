#include "controllerTime.h"
#include "main.h"

ControllerTime::ControllerTime(const char* name, Preferences* prefs):
                    Controller(name) {
    _updateTimeInSec = 1;
    _prefs = prefs;
}

InitResponse_t ControllerTime::OnInit() {
    if (_rtc.begin()) {
        DateTime rtcTime;
        time_t now;
        struct tm tm;
        time(&now);
        localtime_r(&now, &tm);
        // Если время не установлено, то берем его из DS3231
        if (now < 300) {
            rtcTime = _rtc.now();
            tm.tm_year = rtcTime.year() - 1900;
            tm.tm_mon = rtcTime.month();
            tm.tm_mday = rtcTime.day();
            tm.tm_hour = rtcTime.hour();
            tm.tm_min = rtcTime.minute();
            tm.tm_sec = rtcTime.second();
            time_t t = mktime(&tm);
            struct timeval tv = { .tv_sec = t, .tv_usec = 0 };
            settimeofday(&tv, NULL);
            Serial.printf("ControllerTime::OnHandle, Setup ESP32: %s\r\n", asctime(&tm));
        }
        else {
            _rtc.adjust(DateTime(now + _prefs->getInt("tz", 10800)));
            rtcTime = _rtc.now();
            Serial.printf("ControllerTime::OnHandle, Setup DS3231: %02d:%02d:%02d\r\n", rtcTime.hour(), rtcTime.minute(), rtcTime.second());
        }      
        return OnInitResultOK;
    }
    return OnInitResultERROR;
}

void ControllerTime::OnHandle() {
    uint32_t delay = _updateTimeInSec * 1000 / portTICK_PERIOD_MS; 
    portTickType xLastWakeTime = xTaskGetTickCount();
    for (;;) {
        xTaskDelayUntil(&xLastWakeTime, delay);
        xSemaphoreGive(_updateEvent);
        LOGN("ControllerTime::OnIteration")
// #ifdef DEBUG_CONSOLE
//         char text[64];
//         time_t currenTime = time(NULL);
//         strftime(text, sizeof(text), "%d.%m.%Y %H:%M:%S ", localtime(&currenTime));
//         Serial.printf("ControllerTime::next %s\r\n", text);
// #endif
    }
}
