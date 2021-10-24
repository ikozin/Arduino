#ifdef K1533_ID4

#ifndef _K1533_ID4_H_
#define _K1533_ID4_H_

#include "DipDevice.h"

class K1533ID4_SubDev: public TDeviceExt {
  public:
    K1533ID4_SubDev(Input16Out16DevPin *device, size_t device_count, Input16Out16DevVal *value, size_t value_count);
  protected:
    void info(void) {};
  friend class K1533ID4;
};

class K1533ID4: public TDeviceExt {
  public:
    K1533ID4();
  protected:
    virtual void info(void);
  public:
    virtual int test(void);
};

#endif

#endif
