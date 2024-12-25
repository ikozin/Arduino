#pragma once

#include <DipDevice.h>

class K1533LA1LA6LA7LA22: public Dip14Ext {
  public:
    K1533LA1LA6LA7LA22();
  protected:
    virtual const __FlashStringHelper * menu(void) override;
    virtual const __FlashStringHelper * title(void) override;
    virtual const __FlashStringHelper * description(void) override;
};
