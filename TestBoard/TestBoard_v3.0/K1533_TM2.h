#ifdef K1533_TM2

#ifndef _K1533_TM2_
#define _K1533_TM2_

#include "DipI8O8Device.h"

class K1533TM2: public Dip14I8O8Device {
  public:
    K1533TM2();
  protected:
    virtual void info(void);
};

#endif

#endif
