#pragma once

#include "controller.h"
#include "controllerRadio.h"

class ControllerIrRemote : public ControllerT<ControllerRadio> {
    public:
        ControllerIrRemote(gpio_num_t pin);
    protected:
        virtual InitResponse_t OnInit() override;
        virtual bool OnIteration() override;
    private:
        gpio_num_t _pin;
};

//extern ControllerIrRemote ctrlIrRemote;
