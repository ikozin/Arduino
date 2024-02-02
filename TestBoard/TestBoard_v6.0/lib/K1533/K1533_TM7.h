#pragma once

#include <DipDevice.h>

class K1533TM7: public Dip16_ID1_IM3_TM7 {
  public:
    K1533TM7();
  protected:
    virtual const __FlashStringHelper * menu(void) override;
    virtual const __FlashStringHelper * title(void) override;
    virtual const __FlashStringHelper * description(void) override;
};
