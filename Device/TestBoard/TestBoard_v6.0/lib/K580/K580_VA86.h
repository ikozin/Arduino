#pragma once

#include <DipDevice.h>

class K580VA86_SubDev: public Dip20 {
    public:
        K580VA86_SubDev(const TDevicePin *device, const TDeviceVal *value, size_t value_count) {
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

class K580VA86: public TDeviceComposite {
    public:
        K580VA86(void);
    protected:
        virtual const __FlashStringHelper * menu(void) override;
        virtual const __FlashStringHelper * title(void) override;
        virtual const __FlashStringHelper * description(void) override;
};
