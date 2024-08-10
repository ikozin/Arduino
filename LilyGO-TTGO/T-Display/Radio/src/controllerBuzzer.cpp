#include "controllerBuzzer.h"


ControllerBuzzer::ControllerBuzzer(const char* name, gpio_num_t pin) :
                        Controller(name, nullptr) {
    _pin = pin;
}

InitResponse_t ControllerBuzzer::OnInit() {
    return OnInitResultStart;
}

bool ControllerBuzzer::OnIteration() {
    return true;
}

