#include "controller/controllerRadSens.h"

ControllerRadSens::ControllerRadSens(const char* name):
                    ControllerValue(name, 60000), _radSens(RS_DEFAULT_I2C_ADDRESS) {
    _value = 0.0; 
}

bool ControllerRadSens::OnInit() {
    return _radSens.init();
}

bool ControllerRadSens::OnUpdate() {
    _value = _radSens.getRadIntensyStatic();
    return true;
}
