#include "component/componentSoftReset.h"
#include "controller/controllerSoftReset.h"

ComponentSoftReset::ComponentSoftReset(const char* name, ControllerSoftReset* reset) : Component(name) {
    _reset = reset;
}

void ComponentSoftReset::OnHandle() {
    // int state = _reset->getState();
    // LOGN("%s::OnHandle, %d", _name, state)
    ESP.restart();
}
