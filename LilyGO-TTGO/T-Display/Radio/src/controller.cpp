#include "controller.h"
// https://docs.espressif.com/projects/esp-idf/en/v5.0/esp32/api-reference/system/freertos.html#task-api

Controller::Controller(const char* name) {
    assert(name);
    _task = NULL;
    _name = name;
    _updateTimeInSec = 0;
    _updateEvent = xSemaphoreCreateBinary();
}

void Controller::Start(uint16_t stackDepth) {
    xTaskCreate(ControllerHandler, _name, stackDepth, this, 1, &_task);
 }

void Controller::ControllerHandler(void* parameter) {
    assert(parameter);
    Controller* controller = static_cast<Controller*>(parameter);
    InitResponse_t result = controller->OnInit();
    if (result.Code != InitCode_t::INIT_ERROR) {
        if (result.Code != InitCode_t::INIT_OK) {
            DelayInSec(result.DelaySeconds);
        }
        controller->OnHandle();
    }
    vTaskDelete(controller->_task);
}

void Controller::OnHandle() {
    while (OnIteration())  {
        xSemaphoreGive(_updateEvent);
        DelayInSec(_updateTimeInSec);
    }
}

void Controller::DelayInSec(uint32_t seconds) {
    vTaskDelay(seconds * 1000 / portTICK_PERIOD_MS);
}

void Controller::DelayInMin(uint32_t minutes) {
    vTaskDelay(minutes * 60000 / portTICK_PERIOD_MS);
}
