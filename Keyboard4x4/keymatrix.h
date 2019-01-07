#ifndef KEYMATRIX_H
#define KEYMATRIX_H

#include <Arduino.h>

class KeyMatrix
{
  public:
    void begin(uint8_t *p_row, uint8_t rowCount, uint8_t *p_col, uint8_t colCount);
    uint8_t GetKeyPressed();
  private:
    uint8_t *rows;
    uint8_t *cols;
    uint8_t rowCnt;
    uint8_t colCnt;
};
#endif
