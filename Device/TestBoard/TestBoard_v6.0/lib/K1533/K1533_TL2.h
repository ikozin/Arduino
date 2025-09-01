#pragma once

#include <DipDevice.h>
#include "K1533_LN1_LN2_LN3_LN5_LN8_TL2.h"

class K1533TL2: public K1533LN1LN2LN3LN5LN8TL2 {
    protected:
        virtual const __FlashStringHelper * menu(void) override;
        virtual const __FlashStringHelper * title(void) override;
};
