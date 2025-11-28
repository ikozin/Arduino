#pragma once

#include "view/view.h"
#include "controller/controllerBme280.h"

class ViewBme280 : public ViewT<ControllerBme280> {
    public:
        ViewBme280(const char* name, TFT_eSprite* tft, ControllerBme280* controller) : 
            ViewT(name, tft, controller) {

        }
    public:
        virtual void OnUpdate() override;
};