#include "keymatrix.h"

void KeyMatrix::begin(uint8_t *p_row, uint8_t rowCount, uint8_t *p_col, uint8_t colCount)
{
  rows = p_row;
  rowCnt = rowCount;
  cols = p_col;
  colCnt = colCount;  

  for (int i = 0; i < rowCount; i++)
  {
    pinMode(rows[i], OUTPUT);
    digitalWrite(rows[i], HIGH);
  }
  for (int i = 0; i < colCount; i++)
  {
    pinMode(cols[i], INPUT_PULLUP);
  }
}

uint8_t KeyMatrix::GetKeyPressed()
{
  uint8_t keyIndex = 0;
  for (int i = 0; i < rowCnt; i++)
  {
    digitalWrite(rows[i], LOW);
    for (int n = 0; n < colCnt; n++)
    {
      if (!digitalRead(cols[n]))
      {
        digitalWrite(rows[i], HIGH);
        return keyIndex + n + 1;
      }
    }
    digitalWrite(rows[i], HIGH);
    keyIndex += rowCnt;
  }
  return 0;
}
