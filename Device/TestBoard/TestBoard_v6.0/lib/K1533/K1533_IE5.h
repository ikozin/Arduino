#pragma once

#include <DipDevice.h>

class K1533IE5: public Dip14_IE2_IE4_IE5 {
    public:
        K1533IE5(void);
    protected:
        virtual const __FlashStringHelper * menu(void) override;
        virtual const __FlashStringHelper * title(void) override;
        virtual const __FlashStringHelper * description(void) override;
};
