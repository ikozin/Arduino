#include "controller/controllerTimeSNTP.h"
// https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/system/system_time.html
// https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/system/freertos_idf.html
// https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/system/esp_timer.html
InitResponse_t ControllerTimeSNTP::OnInit() {
    _handler = xTimerCreate("TimerClock", pdMS_TO_TICKS(10000), pdTRUE, reinterpret_cast<void *>(this), TimerCallback);
    xTimerStart(_handler, 0);
    return OnInitResultStop;
}

void ControllerTimeSNTP::TimerCallback(TimerHandle_t pxTimer) {
    LOG("ControllerTimeSNTP::TimerCallback\r\n");
    ControllerTimeSNTP * controller = reinterpret_cast<ControllerTimeSNTP *>(pvTimerGetTimerID(pxTimer));
    time_t now = time(nullptr);
    struct tm* timeinfo = localtime(&now);
    controller->_currentTime = DateTime(timeinfo->tm_year, timeinfo->tm_mon, timeinfo->tm_mday,
                            timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
    controller->FireUpdateEvent();
}
