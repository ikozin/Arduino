#include "controllerIrRemote.h"
#include "IrRemote_CarMP3.h"

#define IR_INPUT_PIN        13

ControllerIrRemote::ControllerIrRemote() :
                        Controller("CtrlIrRemote", NULL) {
    _radio = NULL;
}

ControllerIrRemote& ControllerIrRemote::attachControllerRadio(ControllerRadio* radio) {
    _radio = radio;
    return *this;
}

InitResponse_t ControllerIrRemote::OnInit() {
    return OnInitResultOK;
}

bool ControllerIrRemote::OnIteration() {
    LOGN("ControllerIrRemote::OnIteration")
    return false;
}
