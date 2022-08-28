#include <FS.h>
#include <SPIFFS.h>
#include "controllerRadioStorage.h"

ControllerRadioStorage::ControllerRadioStorage() {
    _listSize = 0;
}

boolean ControllerRadioStorage::loadRadioList(const char* fileName) {
    File f = SPIFFS.open(fileName);
    if (f) {
        f.read((uint8_t*)_radioList, sizeof(_radioList));
        f.close();
        for (_listSize = 0; _listSize < RADIO_MAX; _listSize++) {
            if (_radioList[_listSize].band == 0) break;
        }
        return true;
    }
    return false;
}

boolean ControllerRadioStorage::saveRadioList(const char* fileName) {
    File f = SPIFFS.open(fileName);
    if (f) {
        f.write((uint8_t*)_radioList, sizeof(_radioList));
        return true;
    }
    return false;
}
