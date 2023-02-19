#ifndef _MATRIX_H_
#define _MATRIX_H_

#include <Arduino.h>

#define D0            (2)
#define D1            (3)
#define D2            (4)
#define D3            (5)
#define D4            (6)
#define D5            (7)
#define D6            (8)
#define D7            (9)

class Matrix {
    public:
        Matrix(int pinReset, int pinClock, int row = 2, int col = 3);
        void init(void);
        void fill(uint8_t data);
        void loadBlock(uint8_t data[]);
        void load(uint8_t *data);
    private:
        int _reset;
        int _clock;
        int _row;
        int _col;
    public:
        void clockCycle();
        void resetAddress();
        void setData(uint8_t data);
        void loadData(uint8_t data);
};
#endif