#pragma once

#include "controller.h"

class ControllerBuzzer : public Controller {
    public:
        ControllerBuzzer(const char* name, gpio_num_t pin);
        void play(void);
    protected:
        virtual InitResponse_t OnInit() override;
        virtual bool OnIteration() override;
    private:
        gpio_num_t _pin;
};
