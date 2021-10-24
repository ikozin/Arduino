#ifndef _Input8Out8Device_
#define _Input8Out8Device_

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

typedef struct {
  byte Input[8];
  byte Output[8];
} Input8Out8DevPin;

typedef struct {
  union {
    struct {
      byte Data8  : 1;
      byte Data7  : 1;
      byte Data6  : 1;
      byte Data5  : 1;
      byte Data4  : 1;
      byte Data3  : 1;
      byte Data2  : 1;
      byte Data1  : 1;
    };
    byte value;
  };
  union {
    struct {
      byte Out8  : 1;
      byte Out7  : 1;
      byte Out6  : 1;
      byte Out5  : 1;
      byte Out4  : 1;
      byte Out3  : 1;
      byte Out2  : 1;
      byte Out1  : 1;
    };
    byte result;
  };
} Input8Out8DevVal;

class TInput8Out8Dev {
  protected:
    Input8Out8DevPin * _devices;
    Input8Out8DevVal * _values;  
    size_t _devices_count;
    size_t _values_count;

    int test_device(Input8Out8DevPin *device, Input8Out8DevVal *value);

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

class TInput8Out8DevExt: public TInput8Out8Dev {
  protected:
    void set_input(int value);
    int check_devices();
};

#endif
