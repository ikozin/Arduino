#include "component/componentIrRemote.h"
#include "RemoteControl.h"


ComponentIrRemote::ComponentIrRemote(const char* name, ControllerIrRemote* ir_remote, ControllerRadio* radio,
            uint8_t cmdChannelPrev,
            uint8_t cmdChannelNext,
            uint8_t cmdVolumeMinus,
            uint8_t cmdVolumePlus,
            uint8_t cmdVolumeMute) : Component(name) {
    _ir_remote = ir_remote;
    _radio = radio;
    _lastCommand = -1;

    _cmdChannelPrev = cmdChannelPrev;
    _cmdChannelNext = cmdChannelNext;
    _cmdVolumeMinus = cmdVolumeMinus;
    _cmdVolumePlus = cmdVolumePlus;
    _cmdVolumeMute = cmdVolumeMute;
}

void ComponentIrRemote::OnHandle() {
    IrData value = _ir_remote->GetData();
    uint8_t cmd =  value.Command;
    if (value.IsRepeat) {
        if (_lastCommand == cmd) {
            return;
        }
    }
    _lastCommand = cmd;
    LOGN("%s::OnHandle, CMD=%d", _name, cmd);
    if (cmd == _cmdChannelPrev) _radio->changeChannel(-1);
    if (cmd == _cmdChannelNext) _radio->changeChannel(+1);
    if (cmd == _cmdVolumePlus) _radio->changeVolume(+1);
    if (cmd == _cmdVolumeMinus) _radio->changeVolume(-1);
    if (cmd == _cmdVolumeMute) _radio->toggleMute();
}
