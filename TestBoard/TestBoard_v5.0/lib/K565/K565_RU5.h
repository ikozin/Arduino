#ifndef _K565_RU5_H_
#define _K565_RU5_H_

#include <DipDevice.h>

class K565RU5: public Dip16 {
  public:
    K565RU5(void);
  protected:
    virtual const __FlashStringHelper * menu(void);
    virtual void info(void);
    virtual int test_device(const TDevicePin *device, const TDeviceVal *data);
};

#endif
