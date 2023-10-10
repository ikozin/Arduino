#ifndef _TDevicePackage_
#define _TDevicePackage_

#include <Arduino.h>
#include "Device.h"

class DevicePackage {
  protected:
    size_t _count = 0;
    TDevice** _list = NULL;
    const char * _title = NULL;
  public:
    DevicePackage(const char * title, TDevice** list, size_t count);
    const char * title(void) const { return _title; };
    const size_t count() const { return _count; }
    int menu(void);
    int test(int index);
};

#endif
