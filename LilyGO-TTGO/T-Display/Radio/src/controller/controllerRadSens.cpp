#include "controller/controllerRadSens.h"

ControllerRadSens::ControllerRadSens(const char* name):
                    Controller(name), _radSens(RS_DEFAULT_I2C_ADDRESS) {
    _updateTimeInSec = 60;
    _dynamicValue = 0; 
    _staticValue = 0;
    _impulseValue = 0;
}

InitResponse_t ControllerRadSens::OnInit() {
#ifdef RADSENS_FAKE
    _dynamicValue = 5; 
    _staticValue = 5;
    _impulseValue = 5;
    return OnInitResultStart;
#else
    return _radSens.init() ? OnInitResultStart : OnInitResultERROR;
#endif
}

IterationCode_t ControllerRadSens::OnIteration() {
#ifdef RADSENS_FAKE
    _dynamicValue += esp_random() > (UINT32_MAX >> 1) ? 1: -1; 
    _staticValue += esp_random() > (UINT32_MAX >> 1) ? 1: -1;
    _impulseValue += esp_random() > (UINT32_MAX >> 1) ? 1: -1;
#else
    _dynamicValue = _radSens.getRadIntensyDynamic(); 
    _staticValue = _radSens.getRadIntensyStatic();
    _impulseValue = _radSens.getNumberOfPulses();
#endif
    // LOGN("%s::getDynamic, %f", _name, getDynamic())
    // LOGN("%s::getStatic, %f", _name, getStatic())
    // LOGN("%s::getImpulse, %f", _name, getImpulse())

    return IterationCode_t::Ok;
}
