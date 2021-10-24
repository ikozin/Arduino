#ifdef K1533_ID4

#ifndef _K1533_ID4_H_
#define _K1533_ID4_H_

#include "DipI8O8Device.h"

class K1533ID4_SubDev: public TInput8Out8DevExt {
  public:
    K1533ID4_SubDev(Input8Out8DevPin *device, size_t device_count, Input8Out8DevVal *value, size_t value_count);
  protected:
    void info(void) {};
  friend class K1533ID4;
};

class K1533ID4: public TInput8Out8DevExt {
  public:
    K1533ID4();
  protected:
    virtual void info(void);
  public:
    virtual int test(void);
};

#endif

#endif
