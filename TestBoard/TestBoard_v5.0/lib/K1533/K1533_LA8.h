#ifndef _K1533_LA8_H_
#define _K1533_LA8_H_

#include <DipDevice.h>

class K1533LA8: public Dip14Ext {
  public:
    K1533LA8(void);
  protected:
    virtual const __FlashStringHelper * menu(void);
    virtual void info(void);
};

#endif
