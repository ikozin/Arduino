#include "component/componentPIR.h"
#include "controller/controllerPIR.h"

ComponentPIR::ComponentPIR(const char* name, ControllerPIR* pir) : Component(name) {
    _pir = pir;
}

void ComponentPIR::OnHandle() {
    LOGN("%s::getState, %d", _name, _pir->getState())
}
