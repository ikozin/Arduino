#include "controller/controllerTimeSNTP.h"
// https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/system/system_time.html

ControllerTimeSNTP::ControllerTimeSNTP(const char* name, Preferences* prefs):
                    ControllerTime(name, prefs) {
}

// https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/system/freertos_idf.html?highlight=xtimercreate#_CPPv412xTimerCreatePCKcK10TickType_tK10BaseType_tPCv23TimerCallbackFunction_t
InitResponse_t ControllerTimeSNTP::OnInit() {
    for (int index = 0; index < NUM_SNTP_TIMERS; index++) {
        if (xTimers[index] == nullptr) {
            _handler = xTimerCreate("TimerClock", pdMS_TO_TICKS(1000), pdTRUE, reinterpret_cast<void *>(index), TimerCallback);
            xTimers[index] = this;
            xTimerStart(_handler, 0);
            return OnInitResultStop;
        }
    }
    return OnInitResultERROR;
}

void ControllerTimeSNTP::TimerCallback(TimerHandle_t pxTimer) {
    int32_t index = (int32_t)pvTimerGetTimerID(pxTimer);
    ControllerTimeSNTP * controller = ControllerTimeSNTP::xTimers[index];
    time_t now = time(nullptr);
    struct tm* timeinfo = localtime(&now);
    controller->_currentTime = DateTime(timeinfo->tm_year, timeinfo->tm_mon, timeinfo->tm_mday,
                            timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
    controller->FireUpdateEvent();
}
