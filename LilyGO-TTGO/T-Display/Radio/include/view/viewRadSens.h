#pragma once

#include "view/view.h"
#include "IViewGraph.h"
#include "controller/controllerRadSens.h"


class ViewRadSens : public ViewT, public IViewGraph<float, 15, 120, 110, 6, 4, 15, TFT_BROWN, TFT_BLUE, TFT_RED> {
    public:
        ViewRadSens(const char* name, ViewSettig* setting, ControllerRadSens* radSens, SemaphoreHandle_t updateEvent = nullptr);
    protected:
        virtual void OnDrawHandle() override;
};
