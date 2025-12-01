#pragma once

#include "iview.h"
#include "controller/controller.h"
#include "controller/controllerEnviroment.h"
#include "display.h"
#include "logging.h"

// #include "esp_timer.h"

class View : public IView {
    public:
        View(const char* name, ControllerEnviroment* env, TFT_eSprite* tft) {
            _name = name;
            _env = env;
            _tft = tft;

        }
    protected:
        const char* _name;
        ControllerEnviroment* _env;
        TFT_eSprite* _tft;
    public:
        virtual void OnUpdate() = 0;
        virtual void Update(bool forceUpdate) = 0;
};

template<typename Type>
class ViewT : public View {
    public:
        ViewT(const char* name, ControllerEnviroment* env, TFT_eSprite* tft, Type* controller) :
            View(name, env, tft) {
            _controller = controller;
        }
    protected:
        Type* _controller;
    public:
        virtual void Update(bool forceUpdate) {
            if (forceUpdate || xSemaphoreTake(_controller->GetEvent(), 0))
                OnUpdate();
        }
};
