#pragma once

#include <DipDevice.h>
#include "K1533_LA3_LA9_LA11_LA12_LA13_TL3.h"

class K1533LA12: public K1533LA3LA9LA11LA12LA13TL3 {
  protected:
    virtual const __FlashStringHelper * menu(void) override;
    virtual const __FlashStringHelper * title(void) override;
};
