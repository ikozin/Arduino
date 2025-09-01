#pragma once

#include <DipDevice.h>

class K1533LA3LA9LA11LA12LA13TL3: public Dip14Ext {
    public:
        K1533LA3LA9LA11LA12LA13TL3();
    protected:
        virtual const __FlashStringHelper * menu(void) override;
        virtual const __FlashStringHelper * title(void) override;
        virtual const __FlashStringHelper * description(void) override;
};
