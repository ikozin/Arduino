#pragma once

#include <DipDevice.h>

class K1533LI1LI2: public Dip14Ext {
    public:
        K1533LI1LI2(void);
    protected:
        virtual const __FlashStringHelper * menu(void) override;
        virtual const __FlashStringHelper * title(void) override;
        virtual const __FlashStringHelper * description(void) override;
};
