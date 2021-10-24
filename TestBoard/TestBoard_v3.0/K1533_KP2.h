#ifdef K1533_KP2

#ifndef _K1533_KP2_H_
#define _K1533_KP2_H_

#include "DipDevice.h"

class K1533KP2: public Dip16Ext {
  public:
    K1533KP2();
  protected:
    virtual void info(void);
};

#endif

#endif
