#ifndef _K580_IR82_H_
#define _K580_IR82_H_

#include <DipDevice.h>

class K580IR82: public Dip20 {
  public:
    K580IR82(void);
  protected:
    virtual const __FlashStringHelper * menu(void) override;
    virtual const __FlashStringHelper * title(void) override;
    virtual const __FlashStringHelper * description(void) override;
};

#endif