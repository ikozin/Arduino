#include "component/componentIrRemote.h"
#include "RemoteControl.h"


ComponentIrRemote::ComponentIrRemote(const char* name, ControllerIrRemote* ir_remote, ControllerRadio* radio) : Component(name) {
    _ir_remote = ir_remote;
    _radio = radio;
    _lastCommand = -1;
}

void ComponentIrRemote::OnHandle() {
    // LOGN("%s::OnHandle", _name)
    uint8_t cmd =  _ir_remote->GetCommand();
    if (_ir_remote->IsRepeat()) {
        if (_lastCommand == cmd) {
            return;
        }
    }
    _lastCommand = cmd;
    // LOGN("%s::OnHandle, CMD=%d", _name, cmd);
    switch (cmd) {
        case KEY_PREV:
            _radio->changeChannel(-1);
            break;
        case KEY_NEXT:
            _radio->changeChannel(+1);
            break;
        case KEY_PLAY:
            _radio->toggleMute();
            break;
        case KEY_VOL_PREV:
            _radio->changeVolume(-1);
            break;
        case KEY_VOL_NEXT:
            _radio->changeVolume(+1);
            break;
        default:
            break;
    }
}
