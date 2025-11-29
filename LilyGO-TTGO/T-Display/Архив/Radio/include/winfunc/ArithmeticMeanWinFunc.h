#pragma once

#include "IWindowFunction.h"

class ArithmeticMeanWinFunc : public IWindowFunction<float> {
    private:
        size_t  n;
        float   s;
    public:
        ArithmeticMeanWinFunc() : IWindowFunction() {
            n = 0;
            s = 0;
        }
    public:
        virtual void Reset() override {
            n = 0;
            s = 0;
        };
        virtual float Calc(float value) override {
            s += value;
            return s / ++n; 
        };
};