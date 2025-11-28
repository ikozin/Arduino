#pragma once

#include "view/view.h"
#include "controller/controllerRadio.h"

class ViewRadio : public ViewT<ControllerRadio> {
    public:
        ViewRadio(const char* name, TFT_eSprite* tft, ControllerRadio* controller) : 
            ViewT(name, tft,  controller) {
        }
    public:
        virtual void OnUpdate() override;
};