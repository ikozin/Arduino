#pragma once

#include "Device.h"

///////////////////////////////////////////////////////////

class Dip16_ROM: public TDevice {
    public:
        Dip16_ROM(uint8_t bits_address, uint8_t bits_data) {
            _bits_address = bits_address;
            _bits_data = bits_data;
        } 
    private:
        const int _map[17] = {  0, 37, 36, 35, 34, 33, 32, 31,  0, 28, 27, 26, 25, 24, 23, 22};
    protected:
        uint8_t _bits_data;
        uint8_t _bits_address;
    protected:
        virtual int test_device(const TDevicePin *device, const TDeviceVal *value) override;
        virtual int getPin(int value) const {
            return Dip16_ROM::_map[value];
        }
};
