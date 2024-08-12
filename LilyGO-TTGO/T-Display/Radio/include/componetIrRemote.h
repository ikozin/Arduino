#pragma once

#include "componet.h"
#include "componetIrRemote.h"
#include "controllerIrRemote.h"
#include "controllerRadio.h"

class ComponetIrRemote : public Component {
    public:
        ComponetIrRemote(const char* name, ControllerIrRemote* ir_remote, ControllerRadio* radio);
    protected:
        virtual void OnHandle() override;
    private:
        uint32_t _lastCommand;
        ControllerIrRemote* _ir_remote;
        ControllerRadio* _radio;
};
