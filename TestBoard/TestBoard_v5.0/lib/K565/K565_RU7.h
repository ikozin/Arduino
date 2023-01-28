#ifndef _K565_RU7_H_
#define _K565_RU7_H_

#include <DipDevice.h>

class K565RU7: public Dip16 {
  public:
    K565RU7(void);
  protected:
    virtual const __FlashStringHelper * menu(void);
    virtual void info(void);
    virtual int test_device(const TDevicePin *device, const TDeviceVal *data);
};

#endif
