#pragma once

#include <Arduino.h>
#include "main.h"
#include "logging.h"

class Controller {
    public:
        Controller(const char* name, uint64_t updateTime) {
            _name = name;
            _updateTime = updateTime;
            _lastTick = 0;
            _updateEvent = xSemaphoreCreateBinary();
        }
    public:
        const char* GetName() const {
            return _name;
        }
        
        SemaphoreHandle_t GetEvent() const { return _updateEvent; };

        bool Initialize() {
            LOGN("%s::OnInit", _name);
            return OnInit();
        }

        bool Update(uint64_t ticks) {
            if (_updateTime == portMAX_DELAY) return false;
            if (ticks - _lastTick < _updateTime) return false;
            _lastTick = ticks;
            //LOGN("%s::OnUpdate", _name);
            bool result = OnUpdate();
            if (result) setEvent();
            return result;
        }
    protected:
        const char* _name;
        uint64_t _updateTime;
        uint64_t _lastTick;
        SemaphoreHandle_t _updateEvent;
    protected:
        virtual bool OnInit() { return false; };
        virtual bool OnUpdate() { return false; };
        virtual void setEvent() {
            LOGN("%s::setEvent", _name);
            bool result = xSemaphoreTake(_updateEvent, 0);
            if (result) return;
            xSemaphoreGive(_updateEvent);
        }
};

template<typename Type>
class ControllerValue : public Controller {
    public:
        ControllerValue(const char* name, uint64_t updateTime): Controller(name, updateTime) {
        }
    protected:
        Type _value;
    public:
        Type GetValue() { return _value; }
};
