#pragma once

#include "view/view.h"
#include "IViewGraph.h"
#include "controller/controllerBme280.h"


class ViewTemperature : public ViewT, public IViewGraph<float, 15, 120, 110, 6, 2, 35, TFT_BROWN, TFT_BLUE, TFT_RED> {
    public:
        ViewTemperature(const char* name, ViewSettig* setting, ControllerBme280* bme280, SemaphoreHandle_t updateEvent = nullptr);
    protected:
        virtual void OnDrawHandle() override;
};
