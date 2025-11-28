#pragma once

#include "controller/controller.h"
#include "display.h"
#include "logging.h"
#include "colors.h"


// #include "esp_timer.h"

class View {
    public:
        View(const char* name, TFT_eSprite* tft) {
            _name = name;
            _tft = tft;
        }
    protected:
        const char* _name;
        TFT_eSprite* _tft;
    public:
        virtual void OnUpdate() = 0;
        virtual void Update(bool forceUpdate) = 0;
};

template<typename Type>
class ViewT : public View {
    public:
        ViewT(const char* name, TFT_eSprite* tft, Type* controller) :
            View(name, tft) {
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
