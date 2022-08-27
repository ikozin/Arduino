#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_

#include <Arduino.h>
#include "main.h"

class Controller {
    public:
        Controller(const char* name);
        void Start();
        SemaphoreHandle_t GetEvent() const { return _updateEvent; };
    protected:
        const char* _name;
        SemaphoreHandle_t _updateEvent;
        TaskHandle_t _task;
    protected:
        virtual void OnHandle() = 0;
    private:
        static void ControllerHandler(void* parameter);
};

#endif  //_CONTROLLER_H_