#ifdef K1533_TM2

#ifndef _K1533_TM2_
#define _K1533_TM2_

#include "DipDevice.h"

class K1533TM2: public Dip14 {
  public:
    K1533TM2();
  protected:
    virtual void info(void);
};

#endif

#endif
