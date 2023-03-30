#include "controllerTime.h"
#include "main.h"

#define UPDATE_TIME_TIME  20000
ControllerTime::ControllerTime(const char* name) : Controller(name) {
}


void ControllerTime::OnHandle() {
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
        vTaskDelayUntil(&xLastWakeTime, (1000/portTICK_RATE_MS));
    }
}
