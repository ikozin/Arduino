#ifdef K1533_LE4

#ifndef _K1533_LE4_H_
#define _K1533_LE4_H_

#include "DipDevice.h"

class K1533LE4: public Dip14Ext {
  public:
    K1533LE4();
  protected:
    virtual void info(void);
};

#endif

#endif
