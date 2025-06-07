#pragma once

#include "controller/controller.h"
#include "winfunc/CurrentValueWinFunc.h"
#include <CG_RadSens.h>


class ControllerRadSens : public Controller, public ISensorWindowFunc<float, 30, CurrentValueWinFunc, 1> {
    public:
        ControllerRadSens(const char* name);
    protected:
        virtual InitResponse_t OnInit() override;
        virtual IterationCode_t OnIteration() override;
    private:
        CG_RadSens _radSens;    // I2C
};
