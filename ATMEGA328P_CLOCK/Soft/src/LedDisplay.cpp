#include "LedDisplay.h"

// https://zen.yandex.ru/media/id/5b935f60343d6c00a9f52b06/dinamicheskaia-indikaciia-5d0083fb254b9f00af8aa0a8

void LedSegmentDisplay::begin(void) {
    _curIndex = 0;
    for (int i = 0; i < LED_DISPLAY_LENGTH; i++) _dataValue[i] = DISPLAY_SPACE;

    DDRB = B11111111;
    for (int i = 0; i < LED_DISPLAY_LENGTH; i++) {
        pinMode(_digitPin[i], OUTPUT);
        digitalWrite(_digitPin[i], HIGH); // для S8550 HIGH = выключено, при прямом подключении LOW = выключено
	}
}

void LedSegmentDisplay::setTemperature(uint16_t value) {
    _dataValue[0] = _digits[(value >= 0)? DISPLAY_SPACE: DISPLAY_MINUS];
    value = (value < 0)? -value: value;
    _dataValue[1] = _digits[value / 10];
    _dataValue[2] = _digits[value % 10] | B10000000;
    _dataValue[3] = _digits[DISPLAY_CELCIUS];
}

void LedSegmentDisplay::setHumidity(uint16_t value) {
    value = (value < 100)? value: 99;
    _dataValue[0] = _digits[DISPLAY_SPACE];
    _dataValue[1] = _digits[value / 10];
    _dataValue[2] = _digits[value % 10] | B10000000;
    _dataValue[3] = _digits[DISPLAY_HUMIDITY];
}

void LedSegmentDisplay::setTime(uint16_t value) {
    uint8_t hour = highByte(value);
    uint8_t minute = lowByte(value);
    _dataValue[0] = _digits[hour >> 4];
    _dataValue[1] = _digits[hour & 0x0F] | B10000000;
    _dataValue[2] = _digits[minute >> 4];
    _dataValue[3] = _digits[minute & 0x0F];  
}

void LedSegmentDisplay::display(void) {
    uint8_t value = _dataValue[_curIndex];
    noInterrupts();
    for (int i = 0; i < LED_DISPLAY_LENGTH; i++)
        digitalWrite(_digitPin[i], HIGH); // для S8550 HIGH = выключено, при прямом подключении LOW = выключено
    PORTB = ~value;
    digitalWrite(_digitPin[_curIndex], LOW); // для S8550 LOW = включено, при прямом подключении HIGH = включено
    interrupts();
    _curIndex = (uint8_t)((_curIndex + 1) & B00000011);
}
