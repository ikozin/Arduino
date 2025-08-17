#pragma once

#include <Dip16_ROM.h>

class K556RT4: public Dip16_ROM {
    public:
        K556RT4(void);
    protected:
        virtual const __FlashStringHelper * menu(void) override;
        virtual const __FlashStringHelper * title(void) override;
        virtual const __FlashStringHelper * description(void) override;
};
