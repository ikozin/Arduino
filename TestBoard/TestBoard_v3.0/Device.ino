#include "Device.h"

void TDevice::init() {
  for (size_t i = 0; i < _devices_count; i++) {
    for (int n = 0; n < PIN_SIZE; n++) {
      int pin = getPin(_devices[i].Input[n]);
      if (pin == 0) break;
      pinMode(pin, OUTPUT);
      debug_printf("%d(%d) - OUTPUT ", _devices[i].Input[n], pin);
    }
    debug_println();
    for (int n = 0; n < PIN_SIZE; n++) {
      int pin = getPin(_devices[i].Output[n]);
      if (pin == 0) break;
      pinMode(pin, INPUT_PULLUP);
      debug_printf("%d(%d) - INPUT ", _devices[i].Output[n], pin);
    }
    debug_println();
  }
}

void TDevice::done(void) {
  DDRA = B00000000;   // Set input mode
  DDRC = B00000000;   // Set input mode
  PORTA = B11111111;  // Подтягиваем выводы к +5V
  PORTC = B11111111;  // Подтягиваем выводы к +5V
}

int TDevice::test_device(TDevicePin *device, TDeviceVal *data) {
  debug_println("\nInput:");
  for (int n = 0; n < PIN_SIZE; n++) {
    int pin = getPin(device->Input[n]);
    if (pin == 0) break;
    int value = bitRead(data->value, n);
    debug_printf("%d(%d) = %d\r\n", device->Input[n], pin, value);
    digitalWrite(pin, value);
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

int TDevice::check_devices() {
  int errorCount = 0;
  info();
  init();
  debug_println("----------");
  for (size_t i = 0; i < _devices_count; i++) {
    for (size_t n = 0; n < _values_count; n++) {
      debug_printf("\r\nDevice[%d], Test[%d]\r\n", i, n);
      errorCount += test_device(&_devices[i], &_values[n]);
    }
  }
  debug_println("----------");
  done();
  return errorCount;
}

int TDevice::test(void) {
  int result = check_devices();
  if (result == 0) {
    debug_println(F("\r\nТЕСТ ПРОЙДЕН"));
  }
  else {
    debug_printf("\r\nОШИБКА!\r\nКол-во ошибок = %d\r\n\r\n", result);
  }
  return result;
}

void TDeviceExt::set_input(int value) {
  for (size_t i = 0; i < _devices_count; i++) {
    for (int n = 0; n < PIN_SIZE; n++) {
      int pin = getPin(_devices[i].Input[n]);
      if (pin == 0) break;
      digitalWrite(pin, value);
    }
  }  
}

int TDeviceExt::check_devices() {
  int errorCount = 0;
  info();
  init();
  debug_println("----------");
  for (size_t i = 0; i < _devices_count; i++) {
    set_input(LOW);
    for (size_t n = 0; n < _values_count; n++) {
      debug_printf("\r\nDevice[%d], Test[%d]\r\n", i, n);
      errorCount += test_device(&_devices[i], &_values[n]);
    }
  }
  debug_println("----------");
  for (size_t i = 0; i < _devices_count; i++) {
    set_input(HIGH);
    for (size_t n = 0; n < _values_count; n++) {
      debug_printf("\r\nDevice[%d], Test[%d]\r\n", i, n);
      errorCount += test_device(&_devices[i], &_values[n]);
    }
  }
  debug_println("----------");
  done();
  return errorCount;
}
