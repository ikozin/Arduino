#pragma once

#include "controller.h"
#include <CG_RadSens.h>

class ControllerRadSens : public Controller {
    public:
        ControllerRadSens(const char* name, SemaphoreHandle_t updateEvent);
    public:
        float getDynamic() const { return _dynamicValue; }
        float getStatic() const { return _staticValue; }
        float getImpulse() const { return _impulseValue; }
    protected:
        virtual InitResponse_t OnInit() override;
        virtual bool OnIteration() override;
    private:
        CG_RadSens _radSens;    // I2C
        float _dynamicValue; 
        float _staticValue;
        float _impulseValue;
};
