#pragma once

#include "controller/controller.h"

class ControllerGPIOInput : public ControllerValue<int> {
    public:
        ControllerGPIOInput(const char* name, gpio_num_t pin, uint8_t int_type = FALLING, uint8_t pull_mode = INPUT_PULLUP);
    private:
        gpio_num_t  _pin;
        uint8_t     _int_type;
        uint8_t     _pull_mode;
        SemaphoreHandle_t _xMutex;
    private:
        static void isr_handler(void* parameter);
    protected:
        virtual bool OnInit() override;
        virtual bool OnUpdate() override;
    protected:
        virtual bool OnCommand() = 0;
};
