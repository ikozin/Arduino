#ifdef K1533_AP6

#ifndef _K1533_AP6_H_
#define _K1533_AP6_H_

#include "DipDevice.h"

class K1533AP6_SubDev: public Dip20 {
  public:
    K1533AP6_SubDev(TDevicePin *device, TDeviceVal *value, size_t value_count) {
      _devices = device;
      _values = value;
      _devices_count = 1;
      _values_count = value_count;
    }
  protected:
    virtual void info(void) {};
};

class K1533AP6: public TDeviceComposite {
  public:
    K1533AP6();
  protected:
    virtual void info(void);
};

#endif

#endif
