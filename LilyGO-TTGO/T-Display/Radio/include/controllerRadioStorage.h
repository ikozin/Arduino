#ifndef _CONTROLLERRADIOSTORAGE_H_
#define _CONTROLLERRADIOSTORAGE_H_

#include <Arduino.h>

#define RADIO_MAX   64

class ControllerRadioStorage {
    public:
        typedef struct _radioItem {
        uint16_t band;
        char name[78];
        } RadioItem_t;
    public:
        ControllerRadioStorage();
        boolean loadRadioList(const char* fileName);
        boolean saveRadioList(const char* fileName);

        uint16_t getCount() const { return _listSize;}
        RadioItem_t* getRadioList() const { return (RadioItem_t*)_radioList; }
    private:
        uint16_t _listSize;
        RadioItem_t _radioList[RADIO_MAX];
};

#endif  //_CONTROLLERRADIOSTORAGE_H_