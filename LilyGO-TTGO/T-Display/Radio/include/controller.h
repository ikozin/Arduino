#pragma once
// https://docs.espressif.com/projects/esp-idf/en/v5.0/esp32/api-reference/system/freertos.html#task-api

#include <Arduino.h>
#include "logging.h"
#include "main.h"

typedef enum InitCode {
    INIT_ERROR = -1,
    INIT_OK = 0,
} InitCode_t;

typedef struct Response {
    int16_t DelaySeconds    : 14;
    int16_t IsDone          : 1;
    int16_t IsError         : 1;
} InitResponse_t;

#define OnInitResultStart                   (InitResponse_t){ .IsDone  = 0 }
#define OnInitResultStartDelaySec(delay)    (InitResponse_t){ .DelaySeconds = delay }
#define OnInitResultStop                    (InitResponse_t){ .IsDone  = 1 }
#define OnInitResultERROR                   (InitResponse_t){ .IsError = 1 }

class Controller {
    public:
        Controller(const char* name, SemaphoreHandle_t updateEvent);
        void Start(uint16_t stackDepth = 2048);
        SemaphoreHandle_t GetEvent() const { return _updateEvent; };
    protected:
        const char* _name;
        uint32_t  _updateTimeInSec;
        SemaphoreHandle_t _updateEvent;
        TaskHandle_t _task;
    protected:
        virtual InitResponse_t OnInit() = 0;
        virtual void OnDone() {};
        virtual bool OnIteration() = 0;
        virtual void OnHandle();
    protected:
        static void DelayInSec(uint32_t seconds);
        static void DelayInMin(uint32_t minutes);
    protected:
        SemaphoreHandle_t  _xMutex = nullptr;
    public:
        void Lock();
        void Unlock();
        void SetLockingHandler(SemaphoreHandle_t xMutex);
    private:
        static void ControllerHandler(void* parameter);
};

template<typename Type>
class ControllerT: public Controller {
    public:
        ControllerT(const char* name, SemaphoreHandle_t updateEvent):
            Controller(name, updateEvent) {
            _controller = nullptr;
        }
    protected:
        Type* _controller;
    public:
        void attachController(Type* controller) {
            _controller = controller;
        };
};
