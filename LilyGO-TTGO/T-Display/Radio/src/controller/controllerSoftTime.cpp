#include "controller/controllerSoftTime.h"
#include "main.h"

ControllerSoftTime::ControllerSoftTime(const char* name, Preferences* prefs):
                    ControllerTime(name, prefs) {
}

InitResponse_t ControllerSoftTime::OnInit() {
    _currentTime = DateTime(2000, 1, 1, 0, 0, 0);
    return OnInitResultStart;
}

void ControllerSoftTime::OnHandle() {
    uint32_t delay = _updateTimeInSec * 1000 / portTICK_PERIOD_MS; 
    portTickType xLastWakeTime = xTaskGetTickCount();
    for (;;) {
        xTaskDelayUntil(&xLastWakeTime, delay);
        Lock();
        _currentTime = _currentTime + TimeSpan(1);
        Unlock();
        FireUpdateEvent();
    }
}
