#ifndef _K1533_LN1_LN2_LN3_LN5_LN8_H_
#define _K1533_LN1_LN2_LN3_LN5_LN8_H_

#include <DipDevice.h>

class K1533LN1LN2LN3LN5LN8TL2: public Dip14Ext {
  public:
    K1533LN1LN2LN3LN5LN8TL2(void);
  protected:
    virtual const __FlashStringHelper * menu(void);
    virtual void info(void);
};

#endif
