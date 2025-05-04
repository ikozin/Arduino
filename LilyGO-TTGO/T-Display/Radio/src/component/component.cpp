#include <typeinfo>
#include "component/component.h"

Component::Component(const char* name, SemaphoreHandle_t updateEvent) {
    _name = name;
    _updateEvent = (updateEvent == nullptr) ? xSemaphoreCreateBinary() : updateEvent;
}

void Component::Start(Controller* ctrl, uint16_t stackDepth) {
    if (ctrl) {
        static_cast<IUpdater*>(ctrl)->AddUpdateEvent(GetEvent());        
    }
    xTaskCreate(Handler, this->_name, stackDepth, this, 50, &this->_task);
}

void Component::Handler(void* parameter) {
    assert(parameter);
    Component* component = static_cast<Component*>(parameter);
    for (;;) {
        xSemaphoreTake(component->_updateEvent, portMAX_DELAY);
        // LOGN("%s::OnHandle", component->_name)
        component->OnHandle();
    }
    vTaskDelete(component->_task);    
}
