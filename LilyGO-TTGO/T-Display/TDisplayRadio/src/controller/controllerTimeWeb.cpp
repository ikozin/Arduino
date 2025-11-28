#include "controller/controllerTimeWeb.h"
#include "main.h"
#include <esp_sntp.h>

ControllerTimeWeb::ControllerTimeWeb(const char* name, Preferences* prefs):
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

void ControllerTimeWeb::SyncTime() {
    configTime(_prefs->getInt("tz", 10800), 0, "ntp1.vniiftri.ru", "ntp2.vniiftri.ru");
}

bool ControllerTimeWeb::OnInit() {
    SyncTime();
    
    int counter = 60;
    do vTaskDelay(1000 / portTICK_RATE_MS);
    while (sntp_get_sync_status() != SNTP_SYNC_STATUS_COMPLETED && counter--);
    if (counter == 0) return false;

    struct tm tinfo;
    getLocalTime(&tinfo);
    _value.year = (uint16_t)tinfo.tm_year + 1900;
    _value.month = (uint8_t)tinfo.tm_mon;
    _value.day = (uint8_t)tinfo.tm_mday;
    _value.hour = (uint8_t)tinfo.tm_hour;
    _value.minute = (uint8_t)tinfo.tm_min;
    _value.second = (uint8_t)tinfo.tm_sec;
    _value.dayOfTheWeek = (uint8_t)tinfo.tm_wday;

    return true;
}

bool ControllerTimeWeb::OnUpdate() {
    struct tm tinfo;
    getLocalTime(&tinfo);
    _value.year = (uint16_t)tinfo.tm_year + 1900;
    _value.month = (uint8_t)tinfo.tm_mon;
    _value.day = (uint8_t)tinfo.tm_mday;
    _value.hour = (uint8_t)tinfo.tm_hour;
    _value.minute = (uint8_t)tinfo.tm_min;
    _value.second = (uint8_t)tinfo.tm_sec;
    _value.dayOfTheWeek = (uint8_t)tinfo.tm_wday;
    return true;
}
