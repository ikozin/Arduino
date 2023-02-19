#include <Arduino.h>
#include <matrix.h>

void test1(Matrix *matrix, unsigned long timeDelay) {
    matrix->fill(0xFF);
    delay(timeDelay);
    matrix->fill(0x00);
    delay(timeDelay);
}