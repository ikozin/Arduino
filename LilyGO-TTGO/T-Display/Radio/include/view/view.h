#pragma once

#include <Arduino.h>
#include <TFT_eSPI.h>
#include "main.h"
#include "logging.h"
#include "controller/controller.h"

class View {
    protected:
        View** _currentView;
        const char* _name;
        SemaphoreHandle_t _updateEvent;
        TaskHandle_t _task;
        TFT_eSprite* _sprite;
    protected:
        virtual void OnHandle() = 0;
    public:
        View(const char* name, View** currentView, SemaphoreHandle_t updateEvent = nullptr);
        void Start(TFT_eSprite* sprite, Controller* ctrl = nullptr, uint16_t stackDepth = 4096);
        SemaphoreHandle_t GetEvent() const { return _updateEvent; };
    private:
        static void ViewHandler(void* parameter);
};
