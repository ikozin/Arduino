#pragma once

#include "component/component.h"
#include "controller/controllerSoftReset.h"

class ComponentSoftReset : public Component {
    public:
        ComponentSoftReset(const char* name, ControllerSoftReset* reset);
    protected:
        virtual void OnHandle() override;
    private:
        ControllerSoftReset* _reset;
};
