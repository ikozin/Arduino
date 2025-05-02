#pragma once

#include "component/component.h"
#include "controller/controllerIrRemote.h"
#include "controller/controllerRadio.h"

class ComponentIrRemote : public Component {
    public:
        ComponentIrRemote(const char* name, ControllerIrRemote* ir_remote, ControllerRadio* radio);
    protected:
        virtual void OnHandle() override;
    private:
        uint8_t _lastCommand;
        ControllerIrRemote* _ir_remote;
        ControllerRadio* _radio;
};
