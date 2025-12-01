#pragma once

#include "view/view.h"
#include "controller/controllerBme280.h"

class ViewBme280 : public ViewT<ControllerBme280> {
    public:
        ViewBme280(const char* name, ControllerEnviroment* env, TFT_eSprite* tft, ControllerBme280* controller) : 
            ViewT(name, env, tft, controller) {

        }
    public:
        virtual void OnUpdate() override;
};