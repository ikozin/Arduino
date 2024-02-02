#pragma once

#include <DipDevice.h>

class K1533LE1LE5LE6LE10LE11: public Dip14Ext {
  public:
    K1533LE1LE5LE6LE10LE11(void);
  protected:
    virtual const __FlashStringHelper * menu(void) override;
    virtual const __FlashStringHelper * title(void) override;
    virtual const __FlashStringHelper * description(void) override;
};
