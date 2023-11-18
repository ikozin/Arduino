#ifndef _K565_RU7_H_
#define _K565_RU7_H_

#include "Dip16_RU5_RU7.h"

class K565RU7: public Dip16_RU5_RU7 {
  public:
    K565RU7(void);
  protected:
    virtual const __FlashStringHelper * menu(void) override;
    virtual const __FlashStringHelper * title(void) override;
    virtual const __FlashStringHelper * description(void) override;
};

#endif
