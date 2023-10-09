#ifndef _K1533_LP5_H_
#define _K1533_LP5_H_

#include <DipDevice.h>

class K1533LP5: public Dip14Ext {
  public:
    K1533LP5(void);
  protected:
    virtual const __FlashStringHelper * menu(void);
    virtual void info(void);
};

#endif
