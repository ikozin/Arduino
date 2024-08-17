#pragma once

#include <Arduino.h>
#include "main.h"
#include "logging.h"

class Component{
    protected:
        const char* _name;
        SemaphoreHandle_t _updateEvent;
        TaskHandle_t _task;
    protected:
        virtual void OnHandle() = 0;
    public:
        Component(const char* name);
        void Start(SemaphoreHandle_t updateEvent, uint16_t stackDepth = 2048);
        SemaphoreHandle_t GetEvent() const { 
            assert(_updateEvent);
            return _updateEvent;
        };
    private:
        static void Handler(void* parameter);
};
