#pragma once
#include <Arduino.h>
#include "main.h"

template<typename Type>
class ISensor {
    protected:
        Type   _value;
    public:
        Type GetData() const { return _value; }
};
