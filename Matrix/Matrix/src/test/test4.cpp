#include <Arduino.h>
#include <matrix.h>

uint8_t testBlockData1[] = {
  B10000000,
  B01000000,
  B00100000,
  B00010000,
  B00001000,
  B00000100,
  B00000010,
  B00000001,
};

uint8_t testBlockData2[] = {
  B01000000,
  B00100000,
  B00100000,
  B00010000,
  B00001000,
  B00000100,
  B00000100,
  B00000010,
};

uint8_t testBlockData3[] = {
  B00010000,
  B00010000,
  B00010000,
  B00010000,
  B00001000,
  B00001000,
  B00001000,
  B00001000,
};

uint8_t testBlockData4[] = {
  B00001000,
  B00001000,
  B00001000,
  B00001000,
  B00010000,
  B00010000,
  B00010000,
  B00010000,
};

uint8_t testBlockData5[] = {
  B00000010,
  B00000100,
  B00000100,
  B00001000,
  B00010000,
  B00100000,
  B00100000,
  B01000000,
};

uint8_t testBlockData6[] = {
  B00000001,
  B00000010,
  B00000100,
  B00001000,
  B00010000,
  B00100000,
  B01000000,
  B10000000,
};

uint8_t testBlockData7[] = {
  B00000000,
  B00000011,
  B00000100,
  B00001000,
  B00010000,
  B00100000,
  B11000000,
  B00000000,
};

uint8_t testBlockData8[] = {
  B00000000,
  B00000000,
  B00000011,
  B00001100,
  B00110000,
  B11000000,
  B00000000,
  B00000000,
};

uint8_t testBlockData9[] = {
  B00000000,
  B00000000,
  B00000000,
  B00001111,
  B11110000,
  B00000000,
  B00000000,
  B00000000,
};

uint8_t testBlockData10[] = {
  B00000000,
  B00000000,
  B00000000,
  B11110000,
  B00001111,
  B00000000,
  B00000000,
  B00000000,
};

uint8_t testBlockData11[] = {
  B00000000,
  B00000000,
  B11000000,
  B00110000,
  B00001100,
  B00000011,
  B00000000,
  B00000000,
};


uint8_t testBlockData12[] = {
  B00000000,
  B11000000,
  B00100000,
  B00010000,
  B00001000,
  B00000100,
  B00000011,
  B00000000,
};

void test4(Matrix *matrix, unsigned long timeDelay) {
    matrix->loadBlock(testBlockData1);
    delay(timeDelay);
    matrix->loadBlock(testBlockData2);
    delay(timeDelay);
    matrix->loadBlock(testBlockData3);
    delay(timeDelay);
    matrix->loadBlock(testBlockData4);
    delay(timeDelay);
    matrix->loadBlock(testBlockData5);
    delay(timeDelay);
    matrix->loadBlock(testBlockData6);
    delay(timeDelay);
    matrix->loadBlock(testBlockData7);
    delay(timeDelay);
    matrix->loadBlock(testBlockData8);
    delay(timeDelay);
    matrix->loadBlock(testBlockData9);
    delay(timeDelay);
    matrix->loadBlock(testBlockData10);
    delay(timeDelay);
    matrix->loadBlock(testBlockData11);
    delay(timeDelay);
    matrix->loadBlock(testBlockData12);
    delay(timeDelay);
}