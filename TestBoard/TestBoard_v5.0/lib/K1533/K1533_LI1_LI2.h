#ifndef _K1533_LI1_LI2_H_
#define _K1533_LI1_LI2_H_

#include <DipDevice.h>

class K1533LI1LI2: public Dip14Ext {
  public:
    K1533LI1LI2(void);
  protected:
    virtual const __FlashStringHelper * menu(void);
    virtual void info(void);
};

#endif
