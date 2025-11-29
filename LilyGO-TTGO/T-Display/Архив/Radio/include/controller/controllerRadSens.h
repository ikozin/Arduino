#pragma once

#include "controller/controller.h"
#include "winfunc/CurrentValueWinFunc.h"
#include <CG_RadSens.h>


class ControllerRadSens : public Controller, public ISensor<float> {
    public:
        ControllerRadSens(const char* name);
    protected:
        virtual InitResponse_t OnInit() override;
        virtual IterationCode_t OnIteration() override;
    private:
        CG_RadSens _radSens;    // I2C
};
