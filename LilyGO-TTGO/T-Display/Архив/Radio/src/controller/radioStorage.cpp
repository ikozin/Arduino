#include "controller/radioStorage.h"
#include <FS.h>
#include <SPIFFS.h>

#define DEFAULT_CAPACITY    64

RadioItem::RadioItem(uint16_t band, const char* text): band(band), name(text) {
}

RadioStorage::RadioStorage() {
    _size = 0;
    _capacity = DEFAULT_CAPACITY;
    _list = new RadioItem*[_capacity];
    for (int i = 0; i < _capacity; i++)
        _list[i] = nullptr;
}

bool RadioStorage::load(void) {
    File f = SPIFFS.open(FS_RADIOLIST_FILE);
    if (f) {
        String text;
        int data;
        text.reserve(64);
        while (f.available()) {
            data = f.read();
            while (data != ',' && data != -1) {
                text.concat((char)data);
                data = f.read();
            }
            text.trim();
            int band = text.toInt();
            if (band == 0) break;
            text.clear();

            data = f.read();
            while (data != 13 && data != 10 && data != -1) {
                text.concat((char)data);
                data = f.read();
            }
            text.trim();
            add(new RadioItem(band, text.c_str()));
            text.clear();
        }
        f.close();
#ifdef DEBUG_CONSOLE        
        for (int i = 0; i < length(); i++) {
            Serial.printf("%d, %s\r\n", getItem(i)->band, getItem(i)->name.c_str());
        }
#endif
        return true;
    }
    return false;
}

bool RadioStorage::add(RadioItem* item) {
    if (_size == _capacity) {
        uint16_t temp_capacity = _capacity + DEFAULT_CAPACITY;
        RadioItem** temp_list = new RadioItem*[temp_capacity];
        if (temp_list == nullptr) return false;
        for (int i = 0; i < _capacity; i++)
            temp_list[i] = _list[i];
        for (int i = _capacity; i < temp_capacity; i++)
            temp_list[i] = nullptr;
        
        delete[] _list;
        _list = temp_list;
        _capacity = temp_capacity;
    }
    _list[_size] = item;
    _size++;
    return true;
}

bool RadioStorage::remove(int index) {
    if (index < 0 || index >= _size) return false;
    delete _list[index];
    int i;
    for (i = index; i < _size - 1; i++)
        _list[i] = _list[i + 1];
    _list[i] = nullptr;
    _size--;
    return true;
}

void RadioStorage::clear(void) {
    for (int i = 0; i < _size; i++) {
        delete _list[i];
        _list[i] = nullptr;
    }
    _size = 0;
}
