#ifndef _K1533_TM7_
#define _K1533_TM7_

#include <DipDevice.h>

class K1533TM7: public Dip16_ID1_IM3_TM7 {
  public:
    K1533TM7();
  protected:
    virtual const __FlashStringHelper * menu(void);
    virtual void info(void);
};

#endif
