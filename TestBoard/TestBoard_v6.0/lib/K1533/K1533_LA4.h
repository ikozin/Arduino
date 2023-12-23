#ifndef _K1533_LA4_H_
#define _K1533_LA4_H_

#include <DipDevice.h>
#include "K1533_LA4_LA10_LA24.h"

class K1533LA4: public K1533LA4LA10LA24 {
  protected:
    virtual const __FlashStringHelper * menu(void) override;
    virtual const __FlashStringHelper * title(void) override;
};

#endif
