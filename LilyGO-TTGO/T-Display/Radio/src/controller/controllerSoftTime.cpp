#include "controller/controllerSoftTime.h"
#include "main.h"

ControllerSoftTime::ControllerSoftTime(const char* name, Preferences* prefs):
                    Controller(name) {
    _updateTimeInSec = 1;
    _prefs = prefs;
}

InitResponse_t ControllerSoftTime::OnInit() {
    // struct tm timeinfo;
    // getLocalTime(&timeinfo);
    // _currentTime = DateTime(
    //     timeinfo.tm_year,
    //     timeinfo.tm_mon,
    //     timeinfo.tm_mday, 
    //     timeinfo.tm_hour,
    //     timeinfo.tm_min,
    //     timeinfo.tm_sec);
    _currentTime = DateTime(2024, 9, 6, 17, 30, 0);
    return OnInitResultStart;
}

void ControllerSoftTime::OnHandle() {
    uint32_t delay = _updateTimeInSec * 1000 / portTICK_PERIOD_MS; 
    portTickType xLastWakeTime = xTaskGetTickCount();
    for (;;) {
        xTaskDelayUntil(&xLastWakeTime, delay);
        Lock();
        // struct tm timeinfo;
        // getLocalTime(&timeinfo);
        // _currentTime = DateTime(
        //     timeinfo.tm_year,
        //     timeinfo.tm_mon,
        //     timeinfo.tm_mday, 
        //     timeinfo.tm_hour,
        //     timeinfo.tm_min,
        //     timeinfo.tm_sec);
        _currentTime = _currentTime + TimeSpan(1);
        Unlock();
        for (int i = 0; i < EventListMax && _eventList[i] != nullptr; i++) {
            xSemaphoreGive(_eventList[i]);
        }
    }
}
