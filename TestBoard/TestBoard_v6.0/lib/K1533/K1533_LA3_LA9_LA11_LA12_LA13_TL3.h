#ifndef _K1533_LA3_LA9_LA11_LA12_LA13_TL3_H_
#define _K1533_LA3_LA9_LA11_LA12_LA13_TL3_H_

#include <DipDevice.h>

class K1533LA3LA9LA11LA12LA13TL3: public Dip14Ext {
  public:
    K1533LA3LA9LA11LA12LA13TL3();
  protected:
    virtual const __FlashStringHelper * menu(void) override;
    virtual const __FlashStringHelper * title(void) override;
    virtual const __FlashStringHelper * description(void) override;
};

#endif
