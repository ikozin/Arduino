#include "component/componentSoftReset.h"
#include "controller/controllerSoftReset.h"

ComponentSoftReset::ComponentSoftReset(const char* name, ControllerSoftReset* reset) : Component(name) {
    _reset = reset;
}

void ComponentSoftReset::OnHandle() {
    ESP.restart();
}
