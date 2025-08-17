#pragma once

#define DEBUG_CONSOLE

#include <Arduino.h>
#include <avr/pgmspace.h>
#include "binaries.h"

#include <GyverOLED.h>
#include <EncButton.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

/*
┌─────────┬───────────┐
│ SSD1306 │  MEGA2560 │
├─────────┼───────────┤
│   GND   │   GND     │
├─────────┼───────────┤
│   +5V   │   +5V     │
├─────────┼───────────┤
│   D0    │ 52 (SCK)  │
├─────────┼───────────┤
│   D1    │ 51 (MOSI) │
├─────────┼───────────┤
│   RES   │    47     │
├─────────┼───────────┤
│   DC    │    46     │
├─────────┼───────────┤
│   CS    │    45     │
└─────────┴───────────┘

┌─────────┬─────────┬───────────┐
│ ENCODER │ ENCODER │  MEGA2560 │
├─────────┼─────────┼───────────┤
│   GND   │   GND   │   GND     │
├─────────┼─────────┼───────────┤
│   +5V   │   +5V   │   +5V     │
├─────────┼─────────┼───────────┤
│   SW    │   KEY   │    38     │
├─────────┼─────────┼───────────┤
│   DT    │   S2    │    43     │
├─────────┼─────────┼───────────┤
│   CLK   │   S1    │    44     │
└─────────┴─────────┴───────────┘

*/

#define OLED_CS     (45)
#define OLED_DC     (46)
#define OLED_RESET  (47)
typedef GyverOLED<SSD1306_128x64, OLED_NO_BUFFER, OLED_SPI, OLED_CS, OLED_DC, OLED_RESET> GyverDisplay;

#define PIN_LED_RED     (41)  //PG0
#define PIN_LED_GREEN   (40)  //PG1

extern char text[128];
#if defined(DEBUG_CONSOLE)
    #define debug_println(...)    {Serial.println(__VA_ARGS__); Serial.flush();}
    #define debug_print(...)      {Serial.print(__VA_ARGS__); Serial.flush();}
    #define debug_printf(...)    {sprintf(text, __VA_ARGS__); Serial.print(text); Serial.flush();}
#else
    #define debug_println(...)
    #define debug_print(...)
    #define debug_printf(...)
#endif

#define PIN_ENC_BTN         (38)  //PD7
#define PIN_ENC_S1          (43)  //PL6
#define PIN_ENC_S2          (44)  //PL5

#define PIN_SIZE  16

#define EXPAND_CHIP

typedef struct {
  uint8_t Input[PIN_SIZE];
  uint8_t Output[PIN_SIZE];
} TDevicePin;

typedef struct {
  uint16_t value;
  uint16_t result;
} TDeviceVal;

class IDevice {
  public:
    virtual const __FlashStringHelper * menu(void) = 0;
    virtual const __FlashStringHelper * title(void) = 0;
    virtual const __FlashStringHelper * description(void) = 0;

    virtual int test(GyverDisplay& display) = 0;
};

const size_t MAX_DEVICE = 8;
const size_t MAX_VALUE = 256;

class TDevice : public IDevice {
  protected:
    const TDevicePin * _devices;
    const TDeviceVal * _values;  
    size_t _devices_count;
    size_t _values_count;

    virtual int test_device(const TDevicePin *device, const TDeviceVal *value);

    virtual void loadStorage(void);
    virtual void clearStorage(void);

    virtual void info(GyverDisplay& display);
    virtual void init(void);
    virtual void done(void);

    virtual int getPin(int value) const {
      return value;
    }
  public:
    TDevice() {
        _devices = NULL;
        _values = NULL;  
        _devices_count = 0;
        _values_count = 0;
    }
    
    virtual int check_devices(GyverDisplay& display);
    virtual int test(GyverDisplay& display) override;

    static TDevicePin _storageDevice[MAX_DEVICE];
    static TDeviceVal _storageValue[MAX_VALUE];
};

class TDeviceExt: public TDevice {
  protected:
    void set_input(int value);
    virtual int check_devices(GyverDisplay& display) override;
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
    virtual int check_devices(GyverDisplay& display) override {
      int errorCount = 0;
      info(display);
      for (size_t i = 0; i < _count; i++) {
        TDevice * current = _composite[i];
        errorCount += current->check_devices(display);
      }
      return errorCount;
    }
};
