#pragma once

#include <DipDevice.h>
#include <K1533_LA1_LA6_LA7_LA22.h>

class K1533LA7: public K1533LA1LA6LA7LA22 {
    protected:
        virtual const __FlashStringHelper * menu(void) override;
        virtual const __FlashStringHelper * title(void) override;
};
