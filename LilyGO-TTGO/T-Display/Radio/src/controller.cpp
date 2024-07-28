#include "controller.h"
// https://docs.espressif.com/projects/esp-idf/en/v5.0/esp32/api-reference/system/freertos.html#task-api

Controller::Controller(const char* name, SemaphoreHandle_t updateEvent) {
    assert(name);
    _task = NULL;
    _name = name;
    _updateTimeInSec = 0;
    _updateEvent = (updateEvent == NULL) ? xSemaphoreCreateBinary() : updateEvent;
}

void Controller::Start(uint16_t stackDepth) {
    xTaskCreate(ControllerHandler, _name, stackDepth, this, 1, &_task);
 }

void Controller::ControllerHandler(void* parameter) {
    assert(parameter);
    Controller* controller = static_cast<Controller*>(parameter);
    controller->Lock();
    InitResponse_t result = controller->OnInit();
    controller->Unlock();
    if (result.Code != InitCode_t::INIT_ERROR) {
        if (result.Code != InitCode_t::INIT_OK) {
            DelayInSec(result.DelaySeconds);
        }
        controller->OnHandle();
    }
    vTaskDelete(controller->_task);
}

void Controller::OnHandle() {
    bool result;
    do {
        Lock();
        result  = OnIteration();
        Unlock();
        xSemaphoreGive(_updateEvent);
        if (result) {
            DelayInSec(_updateTimeInSec);
        }

    } while (result);
}

void Controller::DelayInSec(uint32_t seconds) {
    vTaskDelay(seconds * 1000 / portTICK_PERIOD_MS);
}

void Controller::DelayInMin(uint32_t minutes) {
    vTaskDelay(minutes * 60000 / portTICK_PERIOD_MS);
}

void Controller::Lock() {
    if (_xMutex != NULL) {
        xSemaphoreTake(_xMutex, portMAX_DELAY);
    }
}

void Controller::Unlock() {
    if (_xMutex != NULL) {
        xSemaphoreGive(_xMutex);
    }
}

void Controller::SetLockingHandler(SemaphoreHandle_t  xMutex) {
    _xMutex = xMutex;
}
