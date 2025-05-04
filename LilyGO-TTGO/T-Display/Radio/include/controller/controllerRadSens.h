#pragma once

#include "controller/controller.h"
#include <CG_RadSens.h>

typedef struct _RadSensData_ {
    float Dynamic;
    float Static;
    float Impulse;
} RadSensData;

class ControllerRadSens : public Controller, public ISensorWindow<RadSensData, 30> {
    public:
        ControllerRadSens(const char* name);
    protected:
        virtual InitResponse_t OnInit() override;
        virtual IterationCode_t OnIteration() override;
    private:
        CG_RadSens _radSens;    // I2C
};
