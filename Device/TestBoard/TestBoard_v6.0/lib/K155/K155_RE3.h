#pragma once

#include <DipDevice.h>

class K155RE3: public Dip16 {
  public:
    K155RE3(void);
  protected:
    virtual const __FlashStringHelper * menu(void) override;
    virtual const __FlashStringHelper * title(void) override;
    virtual const __FlashStringHelper * description(void) override;
};
