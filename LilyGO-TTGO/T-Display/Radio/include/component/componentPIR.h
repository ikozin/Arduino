#pragma once

#include "component/component.h"
#include "controller/controllerPIR.h"

class ComponentPIR : public Component {
    public:
        ComponentPIR(const char* name, ControllerPIR* pir);
    protected:
        virtual void OnHandle() override;
    private:
        ControllerPIR* _pir;
};
