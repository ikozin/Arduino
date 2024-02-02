#pragma once

#include <DipDevice.h>

class K1533LN1LN2LN3LN5LN8TL2: public Dip14Ext {
  public:
    K1533LN1LN2LN3LN5LN8TL2(void);
  protected:
    virtual const __FlashStringHelper * menu(void) override;
    virtual const __FlashStringHelper * title(void) override;
    virtual const __FlashStringHelper * description(void) override;
};
