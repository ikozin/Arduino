#pragma once

#include "view/view.h"
#include "controller/controllerRadSens.h"

class ViewRadSens : public ViewT<ControllerRadSens> {
    public:
        ViewRadSens(const char* name, ControllerEnviroment* env, TFT_eSprite* tft, ControllerRadSens* controller) : 
            ViewT(name, env, tft, controller) {

        }
    public:
        virtual void OnUpdate() override;
};