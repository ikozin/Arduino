#ifndef _K1533_ID4_H_
#define _K1533_ID4_H_

#include <DipDevice.h>

class K1533ID4_SubDev: public Dip14 {
  public:
    K1533ID4_SubDev(const TDevicePin *device, const TDeviceVal *value, size_t value_count) {
      _devices = device;
      _values = value;
      _devices_count = 1;
      _values_count = value_count;
    }
  protected:
    virtual const __FlashStringHelper * menu(void) { return NULL; };
    virtual void info(void) {};
};

class K1533ID4: public TDeviceComposite {
  public:
    K1533ID4(void);
  protected:
    virtual const __FlashStringHelper * menu(void);
    virtual void info(void);
};

#endif
