#pragma once

#include "component/componentIrRemote.h"
#include "ir/carmp3.h"

class ComponentIrRemoteCarMp3 : public ComponentIrRemote {
    public:
        ComponentIrRemoteCarMp3(const char* name, ControllerIrRemote* ir_remote, ControllerRadio* radio) :
            ComponentIrRemote(name, ir_remote, radio,
                68, 64, 7, 21, 67, 69, 70) {
            
        };
};
