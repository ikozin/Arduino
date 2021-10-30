#ifdef K580_VA86

#ifndef _K580_VA86_H_
#define _K580_VA86_H_

#include "DipDevice.h"

class K580VA86_SubDev: public Dip20 {
  public:
    K580VA86_SubDev(TDevicePin *device, TDeviceVal *value, size_t value_count) {
      _devices = device;
      _values = value;
      _devices_count = 1;
      _values_count = value_count;
    }
  protected:
    virtual void info(void) {};
};

class K580VA86: public TDeviceComposite {
  public:
    K580VA86();
  protected:
    virtual void info(void);
};

#endif

#endif
