#ifdef K1533_LA8

#ifndef _K1533_LA8_H_
#define _K1533_LA8_H_

#include "DipDevice.h"

class K1533LA8: public Dip14Ext {
  public:
    K1533LA8();
  protected:
    virtual void info(void);
};

#endif

#endif
