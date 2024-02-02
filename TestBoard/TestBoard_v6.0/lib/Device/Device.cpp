#include "Device.h"

#if defined(DEBUG_CONSOLE)
char text[128];
#endif

TDevicePin TDevice::_storageDevice[MAX_DEVICE] = { 0 };
TDeviceVal TDevice::_storageValue[MAX_VALUE] = { 0 };

void TDevice::loadStorage(void) {
    uint8_t* src;
    uint8_t* dst;

    if (_devices_count > MAX_DEVICE) {
        debug_printf("\r\nERROR _devices_count %d\r\n", _devices_count);
        _devices_count = MAX_DEVICE;
    }
    if (_values_count > MAX_VALUE) {
        debug_printf("\r\nERROR _values_count %d\r\n", _values_count);
        _values_count = MAX_VALUE;
    }
    src = (uint8_t*)_devices;
    dst = reinterpret_cast<uint8_t*>(TDevice::_storageDevice);
    for (size_t i = 0; i < (sizeof(TDevicePin) * _devices_count); i++) {
        *(dst + i) = pgm_read_byte(src + i); 
    }  
    src = (uint8_t*)_values;
    dst = reinterpret_cast<uint8_t*>(TDevice::_storageValue);
    for (size_t i = 0; i < (sizeof(TDeviceVal) * _values_count); i++) {
        *(dst + i) = pgm_read_byte(src + i); 
    }
}

void TDevice::clearStorage(void) {
    memset(TDevice::_storageDevice, 0, sizeof(TDevice::_storageDevice));
    memset(TDevice::_storageValue, 0, sizeof(TDevice::_storageValue));
}

void TDevice::info(GyverDisplay& display) {
  const __FlashStringHelper * text = title();
  if (text == NULL) return;
  display.clear();
  display.setCursor(0, 0);
  display.println(text);
  display.update();
  Serial.println(description());
}

void TDevice::init() {
    loadStorage();

    for (size_t i = 0; i < _devices_count; i++) {
        for (int n = 0; n < PIN_SIZE; n++) {
            int pin = getPin(TDevice::_storageDevice[i].Input[n]);
            if (pin == 0) break;
            pinMode(pin, OUTPUT);
            debug_printf("%d(%d) - OUTPUT ", TDevice::_storageDevice[i].Input[n], pin);
        }
        debug_println();
        for (int n = 0; n < PIN_SIZE; n++) {
            int pin = getPin(TDevice::_storageDevice[i].Output[n]);
            if (pin == 0) break;
            pinMode(pin, INPUT_PULLUP);
            debug_printf("%d(%d) - INPUT ", TDevice::_storageDevice[i].Output[n], pin);
        }
        debug_println();
    }
}

void TDevice::done(void) {
    clearStorage();
    DDRA = B00000000;   // Set input mode
    DDRC = B00000000;   // Set input mode
    PORTA = B11111111;  // Подтягиваем выводы к +5V
    PORTC = B11111111;  // Подтягиваем выводы к +5V
}

int TDevice::test_device(const TDevicePin *device, const TDeviceVal *data) {
    debug_println("\nInput:");
    for (int n = 0; n < PIN_SIZE; n++) {
        int pin = getPin(device->Input[n]);
        if (pin == 0) break;
        int value = bitRead(data->value, n);
        debug_printf("%d(%d) = %d\r\n", device->Input[n], pin, value);
        gio::write(pin, value);
        // digitalWrite(pin, value);
    }
  
    delay(1);
    debug_println("Output:");
    int errorCount = 0;
    for (int n = 0; n < PIN_SIZE; n++) {
        int pin = getPin(device->Output[n]);
        if (pin == 0) break;
        int result = digitalRead(pin);
        int expected = bitRead(data->result, n);
        errorCount += (result != expected) ? 1 : 0;
        debug_printf("%d(%d) = %d,%d%s\r\n", device->Output[n], pin, result, expected, (result == expected) ? "" : " - ОШИБКА");
    }
    return errorCount;
}

int TDevice::check_devices(GyverDisplay& display) {
    int errorCount = 0;
    info(display);
    init();
    debug_println("----------");
    for (size_t i = 0; i < _devices_count; i++) {
        for (size_t n = 0; n < _values_count; n++) {
            debug_printf("\r\nDevice[%d], Test[%d]\r\n", i, n);
            errorCount += test_device(&TDevice::_storageDevice[i], &TDevice::_storageValue[n]);
        }
    }
    debug_println("----------");
    done();
    return errorCount;
}

int TDevice::test(GyverDisplay& display) {
    int result = check_devices(display);
    if (result == 0) {
        display.setScale(2);
        display.println(F(" ПРОЙДЕН"));
        display.setScale(1);
        
        Serial.println(F(" ПРОЙДЕН"));
    }
    else {
        display.setScale(2);
        display.invertText(true);
        display.println(F(" OШИБKA! "));
        display.invertText(false);
        display.setScale(1);
        display.print(F("Koл-во ошибок = "));
        display.println(result);
        
        Serial.println(F(" OШИБKA! "));
        Serial.print(F("Koл-во ошибок = "));
    }
    return result;
}

void TDeviceExt::set_input(int value) {
    for (size_t i = 0; i < _devices_count; i++) {
        for (int n = 0; n < PIN_SIZE; n++) {
            int pin = getPin(TDevice::_storageDevice[i].Input[n]);
            if (pin == 0) break;
            gio::write(pin, value);
            // digitalWrite(pin, value);
        }
    }
}

int TDeviceExt::check_devices(GyverDisplay& display) {
    int errorCount = 0;
    info(display);
    init();
    debug_println("----------");
    for (size_t i = 0; i < _devices_count; i++) {
        set_input(LOW);
        for (size_t n = 0; n < _values_count; n++) {
            debug_printf("\r\nDevice[%d], Test[%d]\r\n", i, n);
            errorCount += test_device(&TDevice::_storageDevice[i], &TDevice::_storageValue[n]);
        }
    }
    debug_println("----------");
    for (size_t i = 0; i < _devices_count; i++) {
        set_input(HIGH);
        for (size_t n = 0; n < _values_count; n++) {
            debug_printf("\r\nDevice[%d], Test[%d]\r\n", i, n);
            errorCount += test_device(&TDevice::_storageDevice[i], &TDevice::_storageValue[n]);
        }
    }
    debug_println("----------");
    done();
    return errorCount;
}
