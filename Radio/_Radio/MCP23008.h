#ifndef _MCP23008_H
#define _MCP23008_H

class MCP23008
{
public:
  void begin(uint8_t addr);
  void pinMode(uint8_t p, uint8_t d);
  void digitalWrite(uint8_t p, uint8_t d);
  void pullUp(uint8_t p, uint8_t d);
  uint8_t digitalRead(uint8_t p);
  uint8_t readGPIO(void);
  void writeGPIO(uint8_t);

private:
  uint8_t i2caddr;
  uint8_t read8(uint8_t addr);
  void write8(uint8_t addr, uint8_t data);
};

#define MCP23008_ADDRESS 0x20

// registers
#define MCP23008_IODIR 0x00
#define MCP23008_IPOL 0x01
#define MCP23008_GPINTEN 0x02
#define MCP23008_DEFVAL 0x03
#define MCP23008_INTCON 0x04
#define MCP23008_IOCON 0x05
#define MCP23008_GPPU 0x06
#define MCP23008_INTF 0x07
#define MCP23008_INTCAP 0x08
#define MCP23008_GPIO 0x09
#define MCP23008_OLAT 0x0A

#endif
