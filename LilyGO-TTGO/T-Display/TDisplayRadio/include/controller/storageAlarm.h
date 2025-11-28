#pragma once
#include "alarm.h"

#define FS_ALARM_FILE   "/alarm.json"
#define MAX_BLOCK_ALARM_SIZE    (16)

class StorageAlarm {
    public:
        StorageAlarm() {
            _size = 0;
        }
    private:
        alarmBlock_t  _list[MAX_BLOCK_ALARM_SIZE];
        uint16_t      _size;
    public:
        bool load();
        alarmBlock_t* GetData() { return _list; };
        uint16_t GetSize() const { return _size; }
};