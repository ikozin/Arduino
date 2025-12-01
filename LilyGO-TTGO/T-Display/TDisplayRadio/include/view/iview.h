#pragma once
#include <Arduino.h>

class IView {
    public:
        virtual void Update(bool forceUpdate) = 0;
};
