#ifndef _K1533_IE5_
#define _K1533_IE5_

#include <DipDevice.h>

class K1533IE5: public Dip14_IE2_IE4_IE5 {
  public:
    K1533IE5(void);
  protected:
    virtual const __FlashStringHelper * menu(void);
    virtual void info(void);
};

#endif
