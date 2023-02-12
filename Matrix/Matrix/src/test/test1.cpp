#include <Arduino.h>
#include <matrix.h>

void test1(Matrix *matrix, unsigned long timeDelay) {
    matrix->fill();
    delay(timeDelay);
    matrix->clear();
    delay(timeDelay);
}