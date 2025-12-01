#pragma once

#include "view/view.h"
#include "controller/controllerRadio.h"

class ViewRadio : public ViewT<ControllerRadio> {
    public:
        ViewRadio(const char* name, ControllerEnviroment* env, TFT_eSprite* tft, ControllerRadio* controller) : 
            ViewT(name, env, tft, controller) {
        }
    public:
        virtual void OnUpdate() override;
};