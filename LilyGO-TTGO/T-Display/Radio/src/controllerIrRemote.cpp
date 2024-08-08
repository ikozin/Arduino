#include "controllerIrRemote.h"
#include "IrRemote_CarMP3.h"

ControllerIrRemote::ControllerIrRemote(gpio_num_t pin) :
                        ControllerT("CtrlIrRemote", NULL) {
    _pin = pin;
}

InitResponse_t ControllerIrRemote::OnInit() {
    return OnInitResultStart;
}

bool ControllerIrRemote::OnIteration() {
    return false;
}
