#pragma once

#include "view/view.h"
#include "controller/controllerBme280.h"
#include "controller/controllerRadSens.h"

class ViewBME280 : public ViewT<ControllerBme280> {
    public:
        ViewBME280(const char* name, View** currentView, ControllerBme280* ctrl, SemaphoreHandle_t updateEvent = nullptr): 
            ViewT(name, currentView, ctrl, updateEvent) { }
    protected:
        virtual void OnDrawHandle() override;
};
