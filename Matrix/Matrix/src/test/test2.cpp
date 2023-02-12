#include <Arduino.h>
#include <matrix.h>

uint8_t testLine1[] = {
  B00000001,
  B00000010,
  B00000100,
  B00001000,
  B00010000,
  B00100000,
  B01000000,
  B10000000,
};

uint8_t testLine2[] = {
  B00000011,
  B00000011,
  B00001100,
  B00001100,
  B00110000,
  B00110000,
  B11000000,
  B11000000,
};

uint8_t testLine3[] = {
  B00001111,
  B00001111,
  B00001111,
  B00001111,
  B11110000,
  B11110000,
  B11110000,
  B11110000,
};

uint8_t testLine4[] = {
  B11110000,
  B11110000,
  B11110000,
  B11110000,
  B00001111,
  B00001111,
  B00001111,
  B00001111,
};

uint8_t testLine5[] = {
  B11000000,
  B11000000,
  B00110000,
  B00110000,
  B00001100,
  B00001100,
  B00000011,
  B00000011,
};

uint8_t testLine6[] = {
  B10000000,
  B01000000,
  B00100000,
  B00010000,
  B00001000,
  B00000100,
  B00000010,
  B00000001,
};

void test2(Matrix *matrix, unsigned long timeDelay) {
    matrix->loadBlock(testLine1);
    delay(timeDelay);
    matrix->loadBlock(testLine2);
    delay(timeDelay);
    matrix->loadBlock(testLine3);
    delay(timeDelay);
    matrix->loadBlock(testLine4);
    delay(timeDelay);
    matrix->loadBlock(testLine5);
    delay(timeDelay);
    matrix->loadBlock(testLine6);
    delay(timeDelay);
}