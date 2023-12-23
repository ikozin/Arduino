#ifndef _K1533_LE1_H_
#define _K1533_LE1_H_

#include <DipDevice.h>
#include "K1533_LE1_LE5_LE6_LE10_LE11.h"

class K1533LE1: public K1533LE1LE5LE6LE10LE11 {
  protected:
    virtual const __FlashStringHelper * menu(void) override;
    virtual const __FlashStringHelper * title(void) override;
};

#endif
