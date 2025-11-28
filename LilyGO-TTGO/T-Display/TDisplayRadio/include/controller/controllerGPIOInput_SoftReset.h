#pragma once

#include "controller/controllerGPIOInput.h"

class ControllerGPIOInput_SoftReset : public ControllerGPIOInput {
    public:
        ControllerGPIOInput_SoftReset(const char* name, gpio_num_t pin):
                ControllerGPIOInput(name, pin, FALLING, INPUT_PULLUP) {
        }
    protected:
        virtual bool OnCommand() override {
            ESP.restart();
            return true;
        }
};
