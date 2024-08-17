#pragma once

#include <Arduino.h>
#include <TFT_eSPI.h>
#include "main.h"
#include "logging.h"

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
        View(const char* name, View** currentView);
        void Start(TFT_eSprite* sprite, SemaphoreHandle_t updateEvent, uint16_t stackDepth = 4096);
        SemaphoreHandle_t GetEvent() const { 
            assert(_updateEvent);
            return _updateEvent;
        };
    private:
        static void ViewHandler(void* parameter);
};
