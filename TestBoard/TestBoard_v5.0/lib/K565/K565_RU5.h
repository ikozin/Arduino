#ifndef _K565_RU5_H_
#define _K565_RU5_H_

#include "Dip16_RU5_RU7.h"

class K565RU5: public Dip16_RU5_RU7 {
  public:
    K565RU5(void);
  protected:
    virtual const __FlashStringHelper * menu(void);
    virtual void info(void);
};

#endif