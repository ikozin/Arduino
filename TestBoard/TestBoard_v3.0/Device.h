#ifndef _TDevice_
#define _TDevice_

#include "binaries.h"

#define DEBUG_CONSOLE

#if defined(DEBUG_CONSOLE)
char text[128];
#define debug_println(...)    Serial.println(__VA_ARGS__)
#define debug_print(...)      Serial.print(__VA_ARGS__)
#define debug_printf(...)    {sprintf(text, __VA_ARGS__); Serial.print(text);}
#else
#define debug_println(...)
#define debug_print(...)
#define debug_printf(...)
#endif

#define PIN_SIZE  16

typedef struct {
  byte Input[PIN_SIZE];
  byte Output[PIN_SIZE];
} TDevicePin;

typedef struct {
  uint16_t value;
  uint16_t result;
} TDeviceVal;

class IDevice {
  public:
    virtual int test(void) = 0;
};

class TDevice : public IDevice {
  protected:
    TDevicePin * _devices;
    TDeviceVal * _values;  
    size_t _devices_count;
    size_t _values_count;

    int test_device(TDevicePin *device, TDeviceVal *value);

    virtual void info(void) = 0;
    virtual void init(void);
    virtual void done(void);

    virtual int getPin(int value) const {
      return value;
    }
  public:
    virtual int check_devices();
    virtual int test(void);
};

class TDeviceExt: public TDevice {
  protected:
    void set_input(int value);
    int check_devices();
};

class TDeviceComposite: public TDevice {
  protected:
    size_t _count;
    TDevice ** _composite;
  public:
    TDeviceComposite(TDevice ** composite, size_t count)  {
      _devices_count = 0;
      _values_count = 0;
      _composite = composite;
      _count = count;
    }
    virtual int check_devices() {
      int errorCount = 0;
      info();
      for (size_t i = 0; i < _count; i++) {
        TDevice * current = _composite[i];
        errorCount += current->check_devices();
      }
      return errorCount;
    }
};

#endif
