#ifndef _K1533_KP2_H_
#define _K1533_KP2_H_

#include <DipDevice.h>

class K1533KP2: public Dip16 {
  public:
    K1533KP2(void);
  protected:
    virtual const __FlashStringHelper * menu(void);
    virtual void info(void);
};

#endif
