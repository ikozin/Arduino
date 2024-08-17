#pragma once

#include "controller/controllerGPIOInput.h"

class ControllerSoftReset : public ControllerGPIOInput {
    public:
        ControllerSoftReset(const char* name, gpio_num_t pin, SemaphoreHandle_t updateEvent = nullptr):
                ControllerGPIOInput(name, pin, GPIO_INTR_NEGEDGE, GPIO_PULLUP_ONLY, updateEvent) {
        }
};
