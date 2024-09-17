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

typedef enum IterationCode {
    Ok   = 0,
    Skip = 1,
    Stop = 2,
} IterationCode_t;

#define OnInitResultStart                   (InitResponse_t){ .DelaySeconds = 0,     .IsDone  = 0, .IsError = 0 }
#define OnInitResultStartDelaySec(delay)    (InitResponse_t){ .DelaySeconds = delay, .IsDone  = 0, .IsError = 0 }
#define OnInitResultStop                    (InitResponse_t){ .DelaySeconds = 0,     .IsDone  = 1, .IsError = 0 }
#define OnInitResultERROR                   (InitResponse_t){ .DelaySeconds = 0,     .IsDone  = 0, .IsError = 1 }
#define EventListMax                        (3)

class Controller {
    public:
        Controller(const char* name);
        void Start(uint16_t stackDepth = 2048);
        void Start(SemaphoreHandle_t  xMutex, uint16_t stackDepth = 2048);
        bool AddUpdateEvent(SemaphoreHandle_t event);
    protected:
        const char*     _name;
        TaskHandle_t    _task;
        uint32_t        _updateTimeInSec;
        SemaphoreHandle_t   _xMutex = nullptr;
        SemaphoreHandle_t   _eventList[EventListMax] { nullptr, nullptr, nullptr };
    protected:
        void FireUpdateEvent();
    protected:
        virtual InitResponse_t OnInit() = 0;
        virtual IterationCode_t OnIteration() = 0;
        virtual void OnDone() {};
        virtual void OnHandle();
    protected:
        static void DelayInSec(uint32_t seconds);
        static void DelayInMin(uint32_t minutes);
    public:
        void Lock();
        void Unlock();
    private:
        static void ControllerHandler(void* parameter);
};

template<typename Type>
class ControllerT: public Controller {
    public:
        ControllerT(const char* name):
            Controller(name) {
            _controller = nullptr;
        }
    protected:
        Type* _controller;
    public:
        void attachController(Type* controller) {
            _controller = controller;
        };
};
