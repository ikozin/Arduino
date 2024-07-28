
#include <Wire.h>
#include "controllerRadSens.h"

ControllerRadSens::ControllerRadSens(const char* name, SemaphoreHandle_t updateEvent):
                    Controller(name, updateEvent), _radSens(RS_DEFAULT_I2C_ADDRESS) {
    _updateTimeInSec = 60;
    
    _dynamicValue = 0; 
    _staticValue = 0;
    _impulseValue = 0;
}

InitResponse_t ControllerRadSens::OnInit() {
    return _radSens.init() ? OnInitResultOK : OnInitResultERROR;
}

bool ControllerRadSens::OnIteration() {
    LOGN("ControllerRadSens::OnIteration")

    _dynamicValue = _radSens.getRadIntensyDynamic(); 
    _staticValue = _radSens.getRadIntensyStatic();
    _impulseValue = _radSens.getNumberOfPulses();

    LOGN("ControllerRadSens::getDynamic, %f", getDynamic())
    LOGN("ControllerRadSens::getStatic, %f", getStatic())
    LOGN("ControllerRadSens::getImpulse, %f", getImpulse())

    return true;
}
