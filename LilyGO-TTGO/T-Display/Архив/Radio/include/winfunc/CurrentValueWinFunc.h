#pragma once

#include "IWindowFunction.h"

class CurrentValueWinFunc : public IWindowFunction<float> {
    public:
        CurrentValueWinFunc() : IWindowFunction() { }
    public:
        virtual void Reset() override { };
        virtual float Calc(float value) override {
            return value; 
        };
};