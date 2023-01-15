#ifndef _K1533_LA1_LA6_LA7_LA22_H_
#define _K1533_LA1_LA6_LA7_LA22_H_

#include <DipDevice.h>

class K1533LA1LA6LA7LA22: public Dip14Ext {
  public:
    K1533LA1LA6LA7LA22();
  protected:
    virtual const __FlashStringHelper * menu(void);
    virtual void info(void);
};

#endif
