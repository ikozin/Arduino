#include "controllerTime.h"
#include "main.h"

#define UPDATE_TIME_TIME  20000
ControllerTime::ControllerTime(const char* name) : Controller(name) {
}


void ControllerTime::OnHandle() {
    if (!_rtc.begin()) {
        return;
    }

    Wire.beginTransmission(0x68);
    Wire.write(0x10);
    Wire.write(0);
    Wire.endTransmission();

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
        settimeofday(&tv,  NULL);
        Serial.printf("ControllerTime::OnHandle, Setup ESP32: %s", asctime(&tm));
    }
    else {
        _rtc.adjust(DateTime(now));
        rtcTime = _rtc.now();
        Serial.printf("ControllerTime::OnHandle, Setup DS3231: %02d:%02d:%02d", rtcTime.hour(), rtcTime.minute(), rtcTime.second());
    }      

    portTickType xLastWakeTime = xTaskGetTickCount();
    for (;;) {
        LOGN("ControllerTime::OnHandle")
// #ifdef DEBUG_CONSOLE
//         char text[64];
//         time_t currenTime = time(NULL);
//         strftime(text, sizeof(text), "%d.%m.%Y %H:%M:%S ", localtime(&currenTime));
//         Serial.printf("ControllerTime::next %s\r\n", text);
// #endif
        xSemaphoreGive(_updateEvent);
        vTaskDelayUntil(&xLastWakeTime, UPDATE_CLOCK_TIME);
    }
}
