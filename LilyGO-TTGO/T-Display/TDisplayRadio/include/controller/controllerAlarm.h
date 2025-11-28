#pragma once

#include "alarm.h"
#include "controller/controller.h"
#include "controller/controllerRadio.h"
#include "controller/controllerBuzzer.h"
#include "controller/storageAlarm.h"

class ControllerAlarm : public Controller {
    public:
        ControllerAlarm(const char* name, StorageAlarm* storage);
    private:
        StorageAlarm* _storage;
    protected:
        ControllerRadio* _radio;
        ControllerBuzzer* _buzzer;
    public:
        void Attach(ControllerRadio* radio, ControllerBuzzer* buzzer) {
            _radio = radio;
            _buzzer = buzzer;
        }
    private:
        uint8_t nextDay(uint8_t wday_mask, time_t* next);
        TickType_t getTimerPeriod(alarmBlock_t* block);
        void startTimer(alarmBlock_t* block);
        static void timerCallback(TimerHandle_t pxTimer);
    protected:
        virtual bool OnInit() override;
};

