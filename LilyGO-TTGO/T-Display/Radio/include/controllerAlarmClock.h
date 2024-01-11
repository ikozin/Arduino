#ifndef _CONTROLLERALARMCLOCK_H_
#define _CONTROLLERALARMCLOCK_H_

#include <Arduino.h>
#include "controller.h"
#include "controllerRadio.h"

#define     FS_ALARMLIST_FILE   "/alarm.json"

#define WEEK_MASK     0x7F
#define MAX_ALARMCLOCK_COUNT 16

#define SET_ALARMCLOCK_MUTE_ON(h, m)     { { .Monday = 1, .Tuesday = 1, .Wednesday = 1, .Thursday = 1, .Friday = 1, .Saturday = 1, .Sunday = 1, .IsMute = 1, .Reserv = 0 , .Minute = m, .Hour = h, .Index = -1, .Volume = -1, } }
#define SET_ALARMCLOCK_MUTE_OFF(h, m)     { { .Monday = 1, .Tuesday = 1, .Wednesday = 1, .Thursday = 1, .Friday = 1, .Saturday = 1, .Sunday = 1, .IsMute = 0, .Reserv = 0 , .Minute = m, .Hour = h, .Index = -1, .Volume = -1, } }
#define SET_ALARMCLOCK_VOLUME(h, m, v)  { { .Monday = 1, .Tuesday = 1, .Wednesday = 1, .Thursday = 1, .Friday = 1, .Saturday = 1, .Sunday = 1, .IsMute = 0, .Reserv = 0 , .Minute = m, .Hour = h, .Index = -1, .Volume = v, } }

#define SET_ALARMCLOCK_MUTE_WORK(h, m, s)     { { .Monday = 1, .Tuesday = 1, .Wednesday = 1, .Thursday = 1, .Friday = 1, .Saturday = 0, .Sunday = 0, .IsMute = s, .Reserv = 0 , .Minute = m, .Hour = h, .Index = -1, .Volume = -1, } }
#define SET_ALARMCLOCK_VOLUME_WORK(h, m, v)  { { .Monday = 1, .Tuesday = 1, .Wednesday = 1, .Thursday = 1, .Friday = 1, .Saturday = 0, .Sunday = 0, .IsMute = 0, .Reserv = 0 , .Minute = m, .Hour = h, .Index = -1, .Volume = v, } }

class ControllerAlarmClock : public Controller {
    public:
        ControllerAlarmClock(const char* name);
    
    private:
        typedef union alarmClockItem {
            struct {
                uint8_t Monday    : 1;  // 0
                uint8_t Tuesday   : 1;  // 1
                uint8_t Wednesday : 1;  // 2
                uint8_t Thursday  : 1;  // 3
                uint8_t Friday    : 1;  // 4
                uint8_t Saturday  : 1;  // 5
                uint8_t Sunday    : 1;  // 6
                uint8_t IsMute    : 1;  // 7

                uint8_t Reserv;         // 8-15

                uint8_t Minute;         // 16-23
                uint8_t Hour;           // 24-31

                int16_t Index;          // 32-47
                int16_t Volume;         // 48-63
            };
            uint64_t value;
        } alarmClockItem_t;
    
    private:
        ControllerRadio* _radio;

        uint16_t _alarmClockCount;
        TimerHandle_t* _timerList;
        alarmClockItem_t* _alarmClockList;
    private:
        uint8_t nextDay(uint8_t wday_mask, time_t* next);
        TickType_t getTimerPeriod(alarmClockItem_t* pAlarm);
        void startTimer(int index);
        static void timerCallback(TimerHandle_t pxTimer);
    protected:
        void OnHandle() override;
    public:
        ControllerAlarmClock& attachControllerRadio(ControllerRadio* radio);
};

extern ControllerAlarmClock ctrlAlarmClock;

#endif  //_CONTROLLERALARMCLOCK_H_