#pragma once

#include "controller/controllerGPIOInput.h"

class ControllerPIR : public ControllerGPIOInput {
    public:
        ControllerPIR(const char* name, gpio_num_t pin, SemaphoreHandle_t updateEvent = nullptr):
                ControllerGPIOInput(name, pin, GPIO_INTR_ANYEDGE, GPIO_FLOATING, updateEvent) {
        }
};
