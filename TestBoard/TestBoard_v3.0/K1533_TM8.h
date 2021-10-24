#ifdef K1533_TM8

#ifndef _K1533_TM8_
#define _K1533_TM8_

#include "DipDevice.h"

class K1533TM8: public Dip16 {
  public:
    K1533TM8();
  protected:
    virtual void info(void);
};

#endif

#endif
