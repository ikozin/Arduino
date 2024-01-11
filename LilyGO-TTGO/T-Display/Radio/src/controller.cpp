#include "controller.h"

Controller::Controller(const char* name) {
    assert(name);
    _task = NULL;
    _name = name;
    _updateEvent = xSemaphoreCreateBinary();
}

void Controller::Start() {
    xTaskCreate(ControllerHandler, _name, 4096, this, 1, &_task);
 }

void Controller::ControllerHandler(void* parameter) {
    assert(parameter);
    Controller* controller = static_cast<Controller*>(parameter);
    controller->OnHandle();
    vTaskDelete(controller->_task);
}