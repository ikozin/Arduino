#pragma once

#include <DipDevice.h>

class K555IR11A: public Dip16 {
    public:
        K555IR11A(void);
    protected:
        virtual const __FlashStringHelper * menu(void) override;
        virtual const __FlashStringHelper * title(void) override;
        virtual const __FlashStringHelper * description(void) override;
};
