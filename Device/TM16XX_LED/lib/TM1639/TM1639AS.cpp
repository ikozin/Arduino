
#include "TM1639AS.h"

TM1639AS::TM1639AS(byte dataPin, byte clockPin, byte strobePin) {
    _dataPin = dataPin;
    _clockPin = clockPin;
    _strobePin = strobePin;

    _digits = 8;

    pinMode(_dataPin, OUTPUT);
    pinMode(_clockPin, OUTPUT);
    pinMode(_strobePin, OUTPUT);

    digitalWrite(_strobePin, HIGH);
    digitalWrite(_clockPin, HIGH);

	sendCommand(B10000111);	// команда настройки дисплея
	sendCommand(B01000000);	// команда настройки данных
	sendCommand(B11000000);	// команда настройки адрес

	digitalWrite(_strobePin, LOW);
	for (int i = 0; i < 16; i++) send(0x00);
	digitalWrite(_strobePin, HIGH);
}

void TM1639AS::begin(bool activateDisplay, byte intensity) {
	sendCommand(B10000000 | (activateDisplay ? 0x80: 0x00) | (intensity & B00000111));	// команда настройки дисплея
}

void TM1639AS::clearDisplay() {
	sendCommand(B01000000);	// команда настройки данных
	sendCommand(B11000000);	// команда настройки адрес
	digitalWrite(_strobePin, LOW);
	for (int i = 0; i < 16; i++) send(0x00);
	digitalWrite(_strobePin, HIGH);
}

void TM1639AS::setSegments(byte* segments) {
	sendCommand(B01000000);	// команда настройки данных
	sendCommand(B11000000);	// команда настройки адрес

	digitalWrite(_strobePin, LOW);
	for (int i = 0; i < 8; i++) {
		byte segment= segments[i];
		send(segment & B00001111);
		send((segment & B11110000) >> 4);
	}
	digitalWrite(_strobePin, HIGH);
}

void TM1639AS::sendCommand(byte cmd) {
	digitalWrite(_strobePin, LOW);
	send(cmd);
	digitalWrite(_strobePin, HIGH);
}

void TM1639AS::send(byte data) {
	for (int i = 0; i < 8; i++) {
		digitalWrite(_clockPin, LOW);
		digitalWrite(_dataPin, data & 1 ? HIGH : LOW);
		data >>= 1;
		digitalWrite(_clockPin, HIGH);
		delay(1);
	}
}
