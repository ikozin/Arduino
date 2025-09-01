#pragma once

#include <DipDevice.h>
#include "K1533_LI1_LI2.h"

class K1533LI2: public K1533LI1LI2 {
    protected:
        virtual const __FlashStringHelper * menu(void) override;
        virtual const __FlashStringHelper * title(void) override;
};
