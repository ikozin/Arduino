#include <typeinfo>
#include "componet.h"

Component::Component(const char* name) {
    _name = name;
}

void Component::Start(SemaphoreHandle_t updateEvent, uint16_t stackDepth) {
    assert(updateEvent);
    _updateEvent = updateEvent;
    xTaskCreate(Handler, this->_name, stackDepth, this, 50, &this->_task);
}

void Component::Handler(void* parameter) {
    assert(parameter);
    Component* component = static_cast<Component*>(parameter);
    for (;;) {
        xSemaphoreTake(component->_updateEvent, portMAX_DELAY);
        component->OnHandle();
    }
}
