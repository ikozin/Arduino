#include "component/componentIrRemote.h"

ComponentIrRemote::ComponentIrRemote(const char* name, ControllerIrRemote* ir_remote, ControllerRadio* radio) : Component(name) {
    _ir_remote = ir_remote;
    _radio = radio;
    _lastCommand = -1;
}

void ComponentIrRemote::OnHandle() {
    //LOGN("ComponentIrRemote::OnHandle")
    uint32_t cmd =  _ir_remote->GetCommand();
    if (_ir_remote->IsRepeat()) {
        if (_lastCommand == cmd) {
            return;
        }
    }
    _lastCommand = cmd;
    switch (cmd) {
        case 0xf807:            // PREV
            _radio->changeChannel(-1);
            break;
        case 0xea15:            // NEXT
            _radio->changeChannel(+1);
            break;
        case 0xf609:            // PLAY/PAUSE
            _radio->toggleMute();
            break;
        case 0xe916:            // VOLUME-
            _radio->changeVolume(-1);
            break;
        case 0xe619:            // VOLUME+
            _radio->changeVolume(+1);
            break;
        default:
            break;
    }
}
