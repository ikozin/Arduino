#pragma once

#include <DipDevice.h>

class K1533TM8: public Dip16 {
    public:
        K1533TM8();
    protected:
        virtual const __FlashStringHelper * menu(void) override;
        virtual const __FlashStringHelper * title(void) override;
        virtual const __FlashStringHelper * description(void) override;
};
