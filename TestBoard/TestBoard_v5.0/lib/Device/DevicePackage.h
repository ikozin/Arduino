#ifndef _TDevicePackage_
#define _TDevicePackage_

#include <Arduino.h>
#include "Device.h"

class DevicePackage {
  protected:
    int _selected = -1;
    size_t _count = 0;
    TDevice** _list = NULL;
    const char * _title = NULL;
  public:
    DevicePackage(const char * title, TDevice** list, size_t count);
    const char * title(void) const { return _title; };
    void menu(void);
    int test(void);
};

#endif
