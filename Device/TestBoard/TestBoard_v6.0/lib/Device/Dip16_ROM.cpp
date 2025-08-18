#include "Dip16_ROM.h"

int Dip16_ROM::test_device(const TDevicePin *device, const TDeviceVal *data) {
    int errorCount = 0;
    Serial.print(F("      00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F"));
    size_t max_addr = 1 << _bits_address;
    for (size_t addr = 0; addr < max_addr; addr++) {
        if (addr % 16 == 0) {
            Serial.println();
            sprintf(text, "[%02X]:", addr);
            Serial.print(text);
        }
        for (int n = 0; n < PIN_SIZE; n++) {
            int pin = getPin(device->Input[n]);
            if (pin == 0) break;
            int value = bitRead((n < _bits_address) ? addr : data->value, n);
            gio::write(pin, value);
        }
        delay(10);
        uint8_t value = 0;
        for (int n = 0; n < _bits_data; n++) {
            int pin = getPin(device->Output[n]);
            if (pin == 0) break;
            if (gio::read(pin)) bitSet(value, n);
        }
        sprintf(text, " %02X", value);
        Serial.print(text);
        errorCount += value > 0;
    }
    Serial.println();
    return errorCount;
}
