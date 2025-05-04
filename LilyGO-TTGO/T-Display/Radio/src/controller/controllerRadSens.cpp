#include "controller/controllerRadSens.h"

ControllerRadSens::ControllerRadSens(const char* name):
                    Controller(name), ISensorWindow(), _radSens(RS_DEFAULT_I2C_ADDRESS) {
    _updateTimeInSec = 60;
    _value = { .Dynamic = 0, .Static = 0, .Impulse = 0 }; 
}

InitResponse_t ControllerRadSens::OnInit() {
#ifdef RADSENS_FAKE
    for (int i = 0; i < Size(); i++) {
        _value = {
            .Dynamic = (float)(random() % 20),
            .Static = (float)(random() % 20),
            .Impulse = (float)(random() % 20)
        }; 
        AddValue(_value);
    }
    return OnInitResultStart;
#else
    return _radSens.init() ? OnInitResultStart : OnInitResultERROR;
#endif
}

IterationCode_t ControllerRadSens::OnIteration() {
#ifdef RADSENS_FAKE
    _value = {
        .Dynamic = (float)(random() % 20),
        .Static = (float)(random() % 20),
        .Impulse = (float)(random() % 20)
    };
#else
    float dynamicValue = _radSens.getRadIntensyDynamic(); 
    float staticValue = _radSens.getRadIntensyStatic();
    float impulseValue = _radSens.getNumberOfPulses();
    _value = { .Dynamic = dynamicValue, .Static = staticValue, .Impulse = impulseValue };
#endif
    AddValue(_value);
    return IterationCode_t::Ok;
}
