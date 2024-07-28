#pragma once
// https://docs.espressif.com/projects/esp-idf/en/v5.0/esp32/api-reference/system/freertos.html#task-api

#include <Arduino.h>
#include "logging.h"
#include "main.h"

typedef enum InitCode {
    INIT_ERROR = -1,
    INIT_OK = 0,
} InitCode_t;

typedef union Response {
    int16_t DelaySeconds;
    InitCode_t Code;
} InitResponse_t;

#define OnInitResultOK              (InitResponse_t){ .Code = InitCode_t::INIT_OK }
#define OnInitResultERROR           (InitResponse_t){ .Code = InitCode_t::INIT_ERROR }
#define OnInitDelayInSec(delay)     (InitResponse_t){ .DelaySeconds = delay }


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
        virtual bool OnIteration() = 0;
        virtual void OnHandle();
    protected:
        static void DelayInSec(uint32_t seconds);
        static void DelayInMin(uint32_t minutes);
    protected:
        SemaphoreHandle_t  _xMutex = NULL;
    public:
        void Lock();
        void Unlock();
        void SetLockingHandler(SemaphoreHandle_t xMutex);
    private:
        static void ControllerHandler(void* parameter);
};
