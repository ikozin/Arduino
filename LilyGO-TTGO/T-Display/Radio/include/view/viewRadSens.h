#pragma once

#include "view/view.h"
#include "controller/controllerRadSens.h"


class ViewRadSens : public ViewT {
    public:
        ViewRadSens(const char* name, ViewSettig* setting, ControllerRadSens* radSens, SemaphoreHandle_t updateEvent = nullptr);
    protected:
        virtual void OnDrawHandle() override;
};
