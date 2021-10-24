#ifndef _TDevice_
#define _TDevice_

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

class TDevice {
  protected:
    TDevicePin * _devices;
    TDeviceVal * _values;  
    size_t _devices_count;
    size_t _values_count;

    int test_device(TDevicePin *device, TDeviceVal *value);

    virtual int check_devices();
    virtual void info(void) = 0;

    virtual int getPin(int value) const {
      return value;
    }
  public:
    virtual void init(void);
    virtual int test(void);
    virtual void done(void);
};

class TDeviceExt: public TDevice {
  protected:
    void set_input(int value);
    int check_devices();
};

#endif
