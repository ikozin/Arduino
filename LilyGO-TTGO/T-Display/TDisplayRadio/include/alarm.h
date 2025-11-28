#pragma once
#include <Arduino.h>
#include "main.h"
#include "logging.h"

#define WEEK_MASK     0x7F
#define MAX_ALARM_COUNT 16

#define SET_ALARM_MUTE_ON(h, m)     { { .Monday = 1, .Tuesday = 1, .Wednesday = 1, .Thursday = 1, .Friday = 1, .Saturday = 1, .Sunday = 1, .IsMute = 1, .Buzzer = 0, .Reserv = 0 , .Minute = (uint8_t)(m), .Hour = (uint8_t)(h), .Index = -1, .Volume = -1, } }
#define SET_ALARM_MUTE_OFF(h, m)     { { .Monday = 1, .Tuesday = 1, .Wednesday = 1, .Thursday = 1, .Friday = 1, .Saturday = 1, .Sunday = 1, .IsMute = 0, .Buzzer = 0, .Reserv = 0 , .Minute = (uint8_t)(m), .Hour = (uint8_t)(h), .Index = -1, .Volume = -1, } }
#define SET_ALARM_VOLUME(h, m, v)  { { .Monday = 1, .Tuesday = 1, .Wednesday = 1, .Thursday = 1, .Friday = 1, .Saturday = 1, .Sunday = 1, .IsMute = 0, .Buzzer = 0, .Reserv = 0 , .Minute = (uint8_t)(m), .Hour = (uint8_t)(h), .Index = -1, .Volume = (v), } }

#define SET_ALARM_MUTE_WORK(h, m, s)     { { .Monday = 1, .Tuesday = 1, .Wednesday = 1, .Thursday = 1, .Friday = 1, .Saturday = 0, .Sunday = 0, .IsMute = s, .Buzzer = 0, .Reserv = 0 , .Minute = (uint8_t)(m), .Hour = (uint8_t)(h), .Index = -1, .Volume = -1, } }
#define SET_ALARM_VOLUME_WORK(h, m, v)  { { .Monday = 1, .Tuesday = 1, .Wednesday = 1, .Thursday = 1, .Friday = 1, .Saturday = 0, .Sunday = 0, .IsMute = 0, .Buzzer = 0, .Reserv = 0 , .Minute = (uint8_t)(m), .Hour = (uint8_t)(h), .Index = -1, .Volume = (v), } }

typedef union _alarmItem_ {
    struct {
        uint8_t Monday    : 1;  // 0
        uint8_t Tuesday   : 1;  // 1
        uint8_t Wednesday : 1;  // 2
        uint8_t Thursday  : 1;  // 3
        uint8_t Friday    : 1;  // 4
        uint8_t Saturday  : 1;  // 5
        uint8_t Sunday    : 1;  // 6
        uint8_t IsMute    : 1;  // 7

        uint8_t Buzzer    : 1;  // 8-15
        uint8_t Reserv    : 7;  // 8-15

        uint8_t Minute    : 8;  // 16-23
        uint8_t Hour      : 8;  // 24-31

        int16_t Index;          // 32-47
        int16_t Volume;         // 48-63
    };
    uint64_t value;
} alarmItem_t;

typedef struct _alarmBlock_ {
    alarmItem_t alarm;
    TimerHandle_t timer;
    void* controller;
} alarmBlock_t;
