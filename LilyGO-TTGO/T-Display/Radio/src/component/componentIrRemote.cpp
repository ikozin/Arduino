#include "component/componentIrRemote.h"


ComponentIrRemote::ComponentIrRemote(const char* name, ControllerIrRemote* ir_remote, ControllerRadio* radio) : Component(name) {
    _ir_remote = ir_remote;
    _radio = radio;
    _lastCommand = -1;
}

void ComponentIrRemote::OnHandle() {
    //LOGN("ComponentIrRemote::OnHandle")
    uint8_t cmd =  _ir_remote->GetCommand();
    if (_ir_remote->IsRepeat()) {
        if (_lastCommand == cmd) {
            return;
        }
    }
    _lastCommand = cmd;
    LOGN("%s::OnHandle, CMD=%d", _name, cmd);
    switch (cmd) {
        case 7:             // PREV
            _radio->changeChannel(-1);
            break;
        case 21:            // NEXT
            _radio->changeChannel(+1);
            break;
        case 9:             // PLAY/PAUSE
            _radio->toggleMute();
            break;
        case 22:            // VOLUME-
            _radio->changeVolume(-1);
            break;
        case 25:            // VOLUME+
            _radio->changeVolume(+1);
            break;
        default:
            break;
    }
}
