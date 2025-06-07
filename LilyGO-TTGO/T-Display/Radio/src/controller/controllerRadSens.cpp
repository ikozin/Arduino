#include "controller/controllerRadSens.h"

ControllerRadSens::ControllerRadSens(const char* name):
                    Controller(name), ISensorWindowFunc(), _radSens(RS_DEFAULT_I2C_ADDRESS) {
    _updateTimeInSec = 60;
    _value = 0; 
}

InitResponse_t ControllerRadSens::OnInit() {
#ifdef RADSENS_FAKE
    int16_t step = 1;
    int16_t min = 4;
    int16_t max = 14;
    int16_t current = min;
    for (int i = 0; i < Size(); i++) {
        _value = current; 
        AddValue(_value);
        current += step;
        if (current <= min) {
            current = min;
            step = -step;
        }
        if (current >= max) {
            current = max;
            step = -step;
        }
    }
    return OnInitResultStart;
#else
    return _radSens.init() ? OnInitResultStart : OnInitResultERROR;
#endif
}

IterationCode_t ControllerRadSens::OnIteration() {
#ifdef RADSENS_FAKE
    _value = (float)(random() % 20);
#else
    _value = _radSens.getRadIntensyStatic();
#endif
    AddValue(_value);
    return IterationCode_t::Ok;
}
