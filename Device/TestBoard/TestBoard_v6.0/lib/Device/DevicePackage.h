#pragma once

#include <Arduino.h>
#include "Device.h"

class DevicePackage {
    protected:
        int _count = 0;
        TDevice** _list = NULL;
        const char * _title = NULL;
        int _selected = 0;
    public:
        DevicePackage(const char * title, TDevice** list, size_t count);
        const char * title(void) const { return _title; };
        const size_t count() const { return _count; }
        const size_t selected() const { return _selected; }

        void next(size_t step);
        void prev(size_t step);
        void display(GyverDisplay& display);
        int test(GyverDisplay& display, int index);
        int test(GyverDisplay& display);
};
