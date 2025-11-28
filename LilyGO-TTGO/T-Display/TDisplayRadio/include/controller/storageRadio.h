#pragma once

#include <Arduino.h>
#include "logging.h"

#define FS_RADIOLIST_FILE   "/radio.txt"

#define RADIO_MAX   64

class RadioItem {
    public:
        uint16_t band;
        String name;
    public:
        RadioItem(uint16_t band, const char* text);
};

class StorageRadio {
    public:
        StorageRadio();

        bool load(void);

        uint16_t length() const { return _size; };
        RadioItem* getItem(int index) const { return _list[index]; }

        bool add(RadioItem* item);
        bool remove(int index);
        void clear(void);
    private:
        uint16_t _size;
        uint16_t _capacity;
        RadioItem** _list;
};
