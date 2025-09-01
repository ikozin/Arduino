#pragma once

#include <DipDevice.h>

class K1533ID4_SubDev: public Dip16 {
    public:
        K1533ID4_SubDev(const TDevicePin *device, const TDeviceVal *value, size_t value_count) {
            _devices = device;
            _values = value;
            _devices_count = 1;
            _values_count = value_count;
        }
    protected:
        virtual const __FlashStringHelper * menu(void) override { return NULL; };
        virtual const __FlashStringHelper * title(void) override { return NULL; };
        virtual const __FlashStringHelper * description(void) override { return NULL; };
};

class K1533ID4: public TDeviceComposite {
    public:
        K1533ID4(void);
    protected:
        virtual const __FlashStringHelper * menu(void) override;
        virtual const __FlashStringHelper * title(void) override;
        virtual const __FlashStringHelper * description(void) override;
};
