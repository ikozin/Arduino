#ifndef _K580_VA86_H_
#define _K580_VA86_H_

#include <DipDevice.h>

class K580VA86_SubDev: public Dip20 {
  public:
    K580VA86_SubDev(const TDevicePin *device, const TDeviceVal *value, size_t value_count) {
      _devices = device;
      _values = value;
      _devices_count = 1;
      _values_count = value_count;
    }
  protected:
    virtual const __FlashStringHelper * menu(void) { return NULL; };
    virtual void info(void) {};
};

class K580VA86: public TDeviceComposite {
  public:
    K580VA86(void);
  protected:
    virtual const __FlashStringHelper * menu(void);
    virtual void info(void);
};

#endif
