#ifdef K1533_LI1_LI2

#ifndef _K1533_LI1_LI2_H_
#define _K1533_LI1_LI2_H_

#include "DipI8O8Device.h"

class K1533LI1LI2: public Dip14I8O8DeviceExt {
  public:
    K1533LI1LI2();
  protected:
    virtual void info(void);
};

#endif

#endif
