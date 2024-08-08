#pragma once

#include "controller.h"

class ControllerSoftReset : public Controller {
    public:
        ControllerSoftReset(gpio_num_t pin);
    protected:
        virtual InitResponse_t OnInit() override;
        virtual bool OnIteration() override { return false; }
        virtual void OnHandle() override;
    private:
        gpio_num_t _pin;
    private:
        static void IRAM_ATTR gpio_isr_handler(void* arg);
};
