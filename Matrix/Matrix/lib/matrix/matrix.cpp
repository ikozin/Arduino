#include "matrix.h"


Matrix::Matrix(int pinReset, int pinClock, int row, int col) {
    _reset = pinReset;
    _clock = pinClock;
    _row = row;
    _col = col;
}

void Matrix::init(void) {
  pinMode(D0, OUTPUT);
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D4, OUTPUT);
  pinMode(D5, OUTPUT);
  pinMode(D6, OUTPUT);
  pinMode(D7, OUTPUT);
  setData(0x00);

  pinMode(_reset, OUTPUT);
  pinMode(_clock, OUTPUT);

  digitalWrite(_clock, LOW);
  digitalWrite(_reset, HIGH);
}

void inline Matrix::clockCycle(void) {
  digitalWrite(_clock, HIGH);
  digitalWrite(_clock, LOW);
}

void inline Matrix::resetAddress(void) {
  digitalWrite(_reset, LOW);
  digitalWrite(_reset, HIGH);
}

void Matrix::setData(uint8_t data) {
  digitalWrite(D0, bitRead(data, 0));
  digitalWrite(D1, bitRead(data, 1));
  digitalWrite(D2, bitRead(data, 2));
  digitalWrite(D3, bitRead(data, 3));
  digitalWrite(D4, bitRead(data, 4));
  digitalWrite(D5, bitRead(data, 5));
  digitalWrite(D6, bitRead(data, 6));
  digitalWrite(D7, bitRead(data, 7));
}

void Matrix::loadData(uint8_t data) {
  setData(data);
  clockCycle();
}

void Matrix::clear(void) {
    resetAddress();
    for (int c = 0; c < _col; c++)
        for (int r = 0; r < _row; r++)
            for (int n = 0; n < 8; n++)
                loadData(0x00);
}

void Matrix::fill(void) {
    resetAddress();
    for (int c = 0; c < _col; c++)
        for (int r = 0; r < _row; r++)
            for (int n = 0; n < 8; n++)
                loadData(0xFF);
}

void Matrix::loadBlock(uint8_t data[]) {
    resetAddress();
    for (int c = 0; c < _col; c++)
        for (int r = 0; r < _row; r++)
            for (int n = 0; n < 8; n++)
                loadData(data[n]);
}

void Matrix::load(uint8_t *data) {
    resetAddress();
    for (int c = 0; c < _col; c++)
        for (int r = 0; r < _row; r++)
            for (int n = 0; n < 8; n++)
                loadData(*data++);
}
