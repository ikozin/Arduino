#ifdef K1533_IR33

#ifndef _K1533_IR33_H_
#define _K1533_IR33_H_

#include "DipDevice.h"

class K1533IR33: public Dip20 {
  public:
    K1533IR33();
  protected:
    virtual void info(void);
};

#endif

#endif
