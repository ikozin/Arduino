#include "controller/controllerRadSens.h"

ControllerRadSens::ControllerRadSens(const char* name, SemaphoreHandle_t updateEvent):
                    Controller(name, updateEvent), _radSens(RS_DEFAULT_I2C_ADDRESS) {
    _updateTimeInSec = 60;
    
    _dynamicValue = 0; 
    _staticValue = 0;
    _impulseValue = 0;
}

InitResponse_t ControllerRadSens::OnInit() {
    return _radSens.init() ? OnInitResultStart : OnInitResultERROR;
}

IterationCode_t ControllerRadSens::OnIteration() {
    _dynamicValue = _radSens.getRadIntensyDynamic(); 
    _staticValue = _radSens.getRadIntensyStatic();
    _impulseValue = _radSens.getNumberOfPulses();
    LOGN("%s::getDynamic, %f", _name, getDynamic())
    LOGN("%s::getStatic, %f", _name, getStatic())
    LOGN("%s::getImpulse, %f", _name, getImpulse())

    return IterationCode_t::Ok;
}
