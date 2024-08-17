#pragma once

#include "controller/controller.h"

class ControllerGPIOInput : public Controller {
    public:
        ControllerGPIOInput(const char* name, gpio_num_t pin,
            gpio_int_type_t int_type = GPIO_INTR_ANYEDGE, gpio_pull_mode_t pull_mode = GPIO_PULLUP_ONLY,
            SemaphoreHandle_t updateEvent = nullptr);
    protected:
        virtual InitResponse_t OnInit() override;
        virtual IterationCode_t OnIteration() override { return IterationCode_t::Stop; }
    private:
        gpio_num_t          _pin;
        gpio_int_type_t     _int_type;
        gpio_pull_mode_t    _pull_mode;        
        int                 _state;
    public:
        int getState() const { return _state; }
    private:
        static void IRAM_ATTR gpio_isr_handler(void* parameter);
};
