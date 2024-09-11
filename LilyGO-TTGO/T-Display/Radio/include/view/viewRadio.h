#pragma once

#include "view/view.h"
#include "controller/controllerRadio.h"

class ViewRadio : public ViewT {
    public:
        ViewRadio(const char* name, ViewSettig* setting, ControllerRadio* ctrl, SemaphoreHandle_t updateEvent = nullptr): 
            ViewT(name, setting, ctrl, 0, updateEvent) { }
    protected:
        virtual void OnDrawHandle() override;
};
