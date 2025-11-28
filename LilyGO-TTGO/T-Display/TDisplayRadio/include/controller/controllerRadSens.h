#pragma once

#include "controller/controller.h"
#include <CG_RadSens.h>

class ControllerRadSens : public ControllerValue<float> {
    public:
        ControllerRadSens(const char* name);
    protected:
        virtual bool OnInit() override;
        virtual bool OnUpdate() override;
    private:
        CG_RadSens _radSens;    // I2C
};
