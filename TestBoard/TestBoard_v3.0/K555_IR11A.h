#ifdef K555_IR11A

#ifndef _K555_IR11A_H_
#define _K555_IR11A_H_

#include "DipDevice.h"

class K555IR11A: public Dip16 {
  public:
    K555IR11A();
  protected:
    virtual void info(void);
};

#endif

#endif
