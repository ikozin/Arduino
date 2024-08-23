#pragma once

#include "view/view.h"
#include "controller/controllerRadio.h"

class ViewRadio : public ViewT<ControllerRadio> {
    public:
        ViewRadio(const char* name, View** currentView, ControllerRadio* ctrl, SemaphoreHandle_t updateEvent = nullptr): 
            ViewT(name, currentView, ctrl, updateEvent) { }
    protected:
        virtual void OnDrawHandle() override;
};
