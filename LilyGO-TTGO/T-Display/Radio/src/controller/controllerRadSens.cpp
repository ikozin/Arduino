#include "controller/controllerRadSens.h"

ControllerRadSens::ControllerRadSens(const char* name):
                    Controller(name), _radSens(RS_DEFAULT_I2C_ADDRESS) {
    _updateTimeInSec = 60;
    _value = 0; 
}

InitResponse_t ControllerRadSens::OnInit() {
#ifdef RADSENS_FAKE
    _value = 10; 
    return OnInitResultStart;
#else
    return _radSens.init() ? OnInitResultStart : OnInitResultERROR;
#endif
}

IterationCode_t ControllerRadSens::OnIteration() {
#ifdef RADSENS_FAKE
    _value = (float)(random() % 20);
    LOGN("FAKE NEW (%s)", _name);
#else
    _value = _radSens.getRadIntensyStatic();
#endif
    return IterationCode_t::Ok;
}
