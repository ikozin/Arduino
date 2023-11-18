#ifndef _K1533_LL1_H_
#define _K1533_LL1_H_

#include <DipDevice.h>

class K1533LL1: public Dip14Ext {
  public:
    K1533LL1(void);
  protected:
    virtual const __FlashStringHelper * menu(void) override;
    virtual const __FlashStringHelper * title(void) override;
    virtual const __FlashStringHelper * description(void) override;
};

#endif
