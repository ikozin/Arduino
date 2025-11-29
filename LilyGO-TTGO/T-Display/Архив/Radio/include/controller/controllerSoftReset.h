#pragma once

#include "controller/controllerGPIOInput.h"

class ControllerSoftReset : public ControllerGPIOInput {
    public:
        ControllerSoftReset(const char* name, gpio_num_t pin):
                ControllerGPIOInput(name, pin, FALLING, INPUT_PULLUP) {
        }
};
