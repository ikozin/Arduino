#ifndef _K555_IR11A_H_
#define _K555_IR11A_H_

#include <DipDevice.h>

class K555IR11A: public Dip16 {
  public:
    K555IR11A(void);
  protected:
    virtual const __FlashStringHelper * menu(void);
    virtual void info(void);
};

#endif
