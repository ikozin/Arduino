#ifndef _K1533_AP6_H_
#define _K1533_AP6_H_

#include <DipDevice.h>

class K1533AP6_SubDev: public Dip20 {
  public:
    K1533AP6_SubDev(const TDevicePin *device, const TDeviceVal *value, size_t value_count) {
      _devices = device;
      _values = value;
      _devices_count = 1;
      _values_count = value_count;
    }
  protected:
    virtual const __FlashStringHelper * menu(void) { return NULL; };
    virtual void info(void) {};
};

class K1533AP6: public TDeviceComposite {
  public:
    K1533AP6(void);
  protected:
    virtual const __FlashStringHelper * menu(void);
    virtual void info(void);
};

#endif
