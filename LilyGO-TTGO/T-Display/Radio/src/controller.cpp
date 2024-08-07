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
    Lock();
    InitResponse_t result = OnInit();
    Unlock();
    if (result.IsError) {
        LOGN("%s::ERROR INIT", _name)
        return;
    }
    if (result.IsDone) {
        return;
    }
    if (result.DelaySeconds) {
        DelayInSec(result.DelaySeconds);
    }
    xTaskCreate(ControllerHandler, _name, stackDepth, this, 1, &_task);
 }

void Controller::ControllerHandler(void* parameter) {
    assert(parameter);
    Controller* controller = static_cast<Controller*>(parameter);
    controller->OnHandle();
    vTaskDelete(controller->_task);
}

void Controller::OnHandle() {
    for (;;) {
        LOGN("%s::OnIteration", _name)
        Lock();
        bool result  = OnIteration();
        Unlock();
        xSemaphoreGive(_updateEvent);
        if (!result) {
            break;
        }
        DelayInSec(_updateTimeInSec);
    }
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
