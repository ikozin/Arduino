#pragma once

#include <DipDevice.h>

class K1533IR37: public Dip20 {
  public:
    K1533IR37(void);
  protected:
    virtual const __FlashStringHelper * menu(void) override;
    virtual const __FlashStringHelper * title(void) override;
    virtual const __FlashStringHelper * description(void) override;
};
