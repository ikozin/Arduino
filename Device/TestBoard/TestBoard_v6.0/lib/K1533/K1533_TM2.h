#pragma once

#include <DipDevice.h>

class K1533TM2: public Dip14 {
  public:
    K1533TM2(void);
  protected:
    virtual const __FlashStringHelper * menu(void) override;
    virtual const __FlashStringHelper * title(void) override;
    virtual const __FlashStringHelper * description(void) override;
};
