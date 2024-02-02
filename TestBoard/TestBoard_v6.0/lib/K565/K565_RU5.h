#pragma once

#include "Dip16_RU5_RU7.h"

class K565RU5: public Dip16_RU5_RU7 {
  public:
    K565RU5(void);
  protected:
    virtual const __FlashStringHelper * menu(void) override;
    virtual const __FlashStringHelper * title(void) override;
    virtual const __FlashStringHelper * description(void) override;
};
