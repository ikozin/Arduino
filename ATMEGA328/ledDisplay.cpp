#include "ledDisplay.h"
#include <MsTimer2.h>

byte LED_DISPLAY::_curIndex;
byte LED_DISPLAY::_dataValue[LED_DISPLAY_LENGTH];

void LED_DISPLAY::begin()
{
  _curIndex = 0;
  for (int i = 0; i < LED_DISPLAY_LENGTH; i++) _dataValue[i] = 0;

	DDRB = B11111111;
	for (int i = 0; i < LED_DISPLAY_LENGTH; i++)
	{
		pinMode(_digitPin[i], OUTPUT);
		digitalWrite(_digitPin[i], HIGH); // для S8550 HIGH = выключено, при прямом подключении LOW = выключено
	}
	MsTimer2::set(5, LED_DISPLAY::_refresh); // 5ms period
	MsTimer2::start();  
}

void LED_DISPLAY::print(byte v1, byte v2, byte v3, byte v4)
{
  _dataValue[0] = v1;
  _dataValue[1] = v2;
  _dataValue[2] = v3;
  _dataValue[3] = v4;
}

void LED_DISPLAY::_refresh()
{
  byte value = _dataValue[_curIndex];
  for (int i = 0; i < LED_DISPLAY_LENGTH; i++)
    digitalWrite(_digitPin[i], HIGH); // для S8550 HIGH = выключено, при прямом подключении LOW = выключено
  PORTB = ~_digits[value];
  digitalWrite(_digitPin[_curIndex], LOW); // для S8550 LOW = включено, при прямом подключении HIGH = включено
  _curIndex = _curIndex++ & B00000011;
}
