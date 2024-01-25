#include "controller.h"

Controller::Controller(const char* name) {
    assert(name);
    _task = NULL;
    _name = name;
    _updateEvent = xSemaphoreCreateBinary();
}

void Controller::Start(uint16_t stackDepth) {
    xTaskCreate(ControllerHandler, _name, stackDepth, this, 1, &_task);
 }

void Controller::ControllerHandler(void* parameter) {
    assert(parameter);
    Controller* controller = static_cast<Controller*>(parameter);
    controller->OnHandle();
    vTaskDelete(controller->_task);
}