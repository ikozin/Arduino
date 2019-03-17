#include "ledDisplay.h"
#include <MsTimer2.h>

byte LED_DISPLAY::_curIndex;
byte LED_DISPLAY::_dataValue[LED_DISPLAY_LENGTH];

void LED_DISPLAY::begin()
{
  _curIndex = 0;
  for (int i = 0; i < LED_DISPLAY_LENGTH; i++) _dataValue[i] = DISPLAY_SPACE;

	DDRB = B11111111;
	for (int i = 0; i < LED_DISPLAY_LENGTH; i++)
	{
		pinMode(_digitPin[i], OUTPUT);
		digitalWrite(_digitPin[i], HIGH); // для S8550 HIGH = выключено, при прямом подключении LOW = выключено
	}
	MsTimer2::set(4, LED_DISPLAY::_refresh); // 4ms period
	MsTimer2::start();  
}

void LED_DISPLAY::print(byte v1, byte v2, byte v3, byte v4)
{
  _dataValue[0] = v1;
  _dataValue[1] = v2;
  _dataValue[2] = v3;
  _dataValue[3] = v4;
}

void LED_DISPLAY::setTemperature(uint16_t value)
{
  _dataValue[0] = _digits[(value >= 0)? DISPLAY_SPACE: DISPLAY_MINUS];
  value = (value < 0)? -value: value;
  _dataValue[1] = _digits[value / 10];
  _dataValue[2] = _digits[value % 10];
  _dataValue[3] = _digits[DISPLAY_CELCIUS];
}

void LED_DISPLAY::setHumidity(uint16_t value)
{
  value = (value < 100)? value: 99;
  _dataValue[0] = _digits[DISPLAY_SPACE];
  _dataValue[1] = _digits[value / 10];
  _dataValue[2] = _digits[value % 10];
  _dataValue[3] = _digits[DISPLAY_HUMIDITY];
}

void LED_DISPLAY::setTime(uint16_t value)
{
  uint8_t hour = highByte(value);
  uint8_t minute = lowByte(value);
  _dataValue[0] = _digits[hour >> 4];
  _dataValue[1] = _digits[hour & 0x0F] | B10000000;
  _dataValue[2] = _digits[minute >> 4];
  _dataValue[3] = _digits[minute & 0x0F];  
}

void LED_DISPLAY::_refresh()
{
#ifdef INSIDE_IRQ
  noInterrupts();
#endif
  byte value = _dataValue[_curIndex];
  for (int i = 0; i < LED_DISPLAY_LENGTH; i++)
    digitalWrite(_digitPin[i], HIGH); // для S8550 HIGH = выключено, при прямом подключении LOW = выключено
  PORTB = ~value;
  digitalWrite(_digitPin[_curIndex], LOW); // для S8550 LOW = включено, при прямом подключении HIGH = включено
  _curIndex = ++_curIndex & B00000011;
#ifdef INSIDE_IRQ
  interrupts();
#endif
}
