#pragma once

#include <Arduino.h>
#include "main.h"
#include "logging.h"
#include "controller/controller.h"

class Component{
    protected:
        const char* _name;
        SemaphoreHandle_t _updateEvent;
        TaskHandle_t _task;
    protected:
        virtual void OnHandle() = 0;
    public:
        Component(const char* name, SemaphoreHandle_t updateEvent = nullptr);
        void Start(Controller* ctrl = nullptr, uint16_t stackDepth = 2048);
        SemaphoreHandle_t GetEvent() const { return _updateEvent; };
    private:
        static void Handler(void* parameter);
};
