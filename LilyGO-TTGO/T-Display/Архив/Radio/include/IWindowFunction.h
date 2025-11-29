#pragma once

#include "main.h"

template<typename DataType>
class IWindowFunction {
    public: 
        IWindowFunction() {
        }
    public:
        virtual void Reset() = 0;
        virtual DataType Calc(DataType value) = 0;
};
