#pragma once

#include "component/component.h"
#include "controller/controllerIrRemote.h"
#include "controller/controllerRadio.h"
#include "navigator.h"

class ComponentIrRemote : public Component {
    public:
        ComponentIrRemote(const char* name, ControllerIrRemote* ir_remote, ControllerRadio* radio, 
                uint8_t cmdChannelPrev,
                uint8_t cmdChannelNext,
                uint8_t cmdVolumeMinus,
                uint8_t cmdVolumePlus,
                uint8_t cmdVolumeMute,
                uint8_t cmdPagePrev,
                uint8_t cmdPageNext);
    public:
            void SetNavigator(Navigator * navigator) {
                _navigator = navigator;
            };
    protected:
        virtual void OnHandle() override;
    private:
        uint8_t _lastCommand;
        ControllerIrRemote* _ir_remote;
        ControllerRadio* _radio;
        Navigator* _navigator;
    protected:
        uint8_t _cmdChannelPrev;
        uint8_t _cmdChannelNext;
        uint8_t _cmdVolumeMinus;
        uint8_t _cmdVolumePlus;
        uint8_t _cmdVolumeMute;
        uint8_t _cmdPagePrev;
        uint8_t _cmdPageNext;
};
