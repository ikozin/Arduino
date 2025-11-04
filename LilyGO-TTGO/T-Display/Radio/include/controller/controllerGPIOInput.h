#pragma once

#include "controller/controller.h"

class ControllerGPIOInput : public Controller, public ISensor<int> {
    public:
        ControllerGPIOInput(const char* name, gpio_num_t pin,
            uint8_t int_type = FALLING, uint8_t pull_mode = INPUT_PULLUP);
    protected:
        virtual InitResponse_t OnInit() override;
        virtual IterationCode_t OnIteration() override { return IterationCode_t::Stop; }
    private:
        gpio_num_t  _pin;
        uint8_t     _int_type;
        uint8_t     _pull_mode;        
    private:
        static void isr_handler(void* parameter);
};
