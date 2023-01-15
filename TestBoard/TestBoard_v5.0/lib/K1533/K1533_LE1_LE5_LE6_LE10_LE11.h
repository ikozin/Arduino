#ifndef _K1533_LE1_LE5_LE6_LE10_LE11_H_
#define _K1533_LE1_LE5_LE6_LE10_LE11_H_

#include <DipDevice.h>

class K1533LE1LE5LE6LE10LE11: public Dip14Ext {
  public:
    K1533LE1LE5LE6LE10LE11(void);
  protected:
    virtual const __FlashStringHelper * menu(void);
    virtual void info(void);
};

#endif
