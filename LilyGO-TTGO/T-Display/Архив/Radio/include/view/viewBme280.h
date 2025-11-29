#pragma once

#include "view/view.h"
#include "controller/controllerBme280.h"
#include "controller/controllerRadSens.h"

class ViewBME280 : public ViewT {
    public:
        ViewBME280(const char* name, ViewSettig* setting, ControllerBme280* ctrl, SemaphoreHandle_t updateEvent = nullptr): 
            ViewT(name, setting, ctrl, 0, updateEvent) { }
    protected:
        virtual void OnDrawHandle() override;
};
