#pragma once

#include "component/component.h"
#include "controller/controllerIrRemote.h"
#include "controller/controllerRadio.h"

class ComponentIrRemote : public Component {
    public:
        ComponentIrRemote(const char* name, ControllerIrRemote* ir_remote, ControllerRadio* radio, 
                uint8_t cmdChannelPrev,
                uint8_t cmdChannelNext,
                uint8_t cmdVolumeMinus,
                uint8_t cmdVolumePlus,
                uint8_t cmdVolumeMute);
    protected:
        virtual void OnHandle() override;
    private:
        uint8_t _lastCommand;
        ControllerIrRemote* _ir_remote;
        ControllerRadio* _radio;
    protected:
        uint8_t _cmdChannelPrev;
        uint8_t _cmdChannelNext;
        uint8_t _cmdVolumeMinus;
        uint8_t _cmdVolumePlus;
        uint8_t _cmdVolumeMute;
};
