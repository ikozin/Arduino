#pragma once

#include <Arduino.h>
#include <EEPROM.h>

#define FLAG_MONDAY		B00000001
#define FLAG_TUESDAY	B00000010
#define FLAG_WEDNESDAY  B00000100
#define FLAG_THURSDAY	B00001000
#define FLAG_FRIDAY		B00010000
#define FLAG_SATURDAY	B00100000
#define FLAG_SUNDAY		B01000000
#define FLAG_WORK_WEEK	(FLAG_MONDAY | FLAG_TUESDAY | FLAG_WEDNESDAY | FLAG_THURSDAY | FLAG_FRIDAY)

enum class ALARM_STATE: byte {
    On = 0,
    Off = 0xFF
};

enum class ALARM_MODE: byte {
    Mute = 0,
    Voice = 0xFF
};

typedef struct {
    ALARM_STATE state;
    uint8_t week;
    ALARM_MODE mode;
	uint8_t hour;
	uint8_t minute;
	uint8_t second;
	uint8_t volume;
    uint8_t radio;
} AlarmItem;

typedef struct {
	uint8_t index;
	uint8_t volume;
	int8_t  corrSec;
	int8_t  currentPlay;
	AlarmItem alarm[6];
} Configuration;

class Storage {
    private:
        const uint16_t StorageWindow = 1024;
    public:
        Storage() { }

    private:
        uint16_t    address = 0;
        Configuration data = {
            .index = 35,        // индекс радиостанции
            .volume = 10,       // громкость
            .corrSec = 0,
            .currentPlay = 0,
            .alarm = {
                {
                    .state = ALARM_STATE::On,
                    .week = FLAG_WORK_WEEK | FLAG_SATURDAY | FLAG_SUNDAY,
                    .mode = ALARM_MODE::Mute,
                    .hour = 23,
                    .minute = 0,
                    .second = 0,
                    .volume = 0,
                    .radio = 0,
                },
                {
                    .state = ALARM_STATE::On,
                    .week = FLAG_WORK_WEEK,
                    .mode = ALARM_MODE::Voice,
                    .hour = 8,
                    .minute = 10,
                    .second = 0,
                    .volume = 5,
                    .radio = 35,
                },
                {
                    .state = ALARM_STATE::On,
                    .week = FLAG_WORK_WEEK,
                    .mode = ALARM_MODE::Mute,
                    .hour = 8,
                    .minute = 20,
                    .second = 0,
                    .volume = 0,
                    .radio = 0,
                },
                {
                    .state = ALARM_STATE::On,
                    .week = FLAG_SATURDAY | FLAG_SUNDAY,
                    .mode = ALARM_MODE::Voice,
                    .hour = 9,
                    .minute = 0,
                    .second = 0,
                    .volume = 5,
                    .radio = 35,
                },
                {
                    .state = ALARM_STATE::On,
                    .week = FLAG_SATURDAY | FLAG_SUNDAY,
                    .mode = ALARM_MODE::Mute,
                    .hour = 10,
                    .minute = 0,
                    .second = 0,
                    .volume = 0,
                    .radio = 0,
                }
            }
        };
    public:
        void begin() {
            for (address = 0; address < StorageWindow && EEPROM.read(address) != 0xFFU; address++);
            if (address == StorageWindow) address = 0;
        }    
        void Load() {
            byte* ptr = reinterpret_cast<byte*>(&data);
            for (uint16_t i = 0; i < sizeof(data); i++) ptr[i] = EEPROM.read(address + i);
        }
        void Save() {
            byte* ptr = reinterpret_cast<byte*>(&data);
            EEPROM.write(address++, 0xFFU);
            for (uint16_t i = 0; i < sizeof(data); i++) EEPROM.write(address + i, ptr[i]);
        }

        void AlarmClear() {
            memset(data.alarm, 0xFF, sizeof(data.alarm));
        }
        
        inline uint8_t GetIndex() const { return data.index; };
        inline uint8_t GetVolume() const { return data.volume; };
        inline uint8_t GetCorrSec() const { return data.corrSec; };
        inline uint8_t GetCurrentPlay() const { return data.currentPlay; };
        inline AlarmItem* GetAlarm(uint8_t value) { return &data.alarm[value]; }
        inline uint16_t GetAlarmSize() { return sizeof(data.alarm)/sizeof(data.alarm[0]); }

        void SetIndex(uint8_t value) { data.index = value; };
        void SetVolume(uint8_t value) { data.volume = constrain(value, 0, 15); };
        void SetCurrentPlay(uint8_t value) { data.currentPlay = value; };
        void SetCorrSec(uint8_t value) { data.corrSec = value; };
};