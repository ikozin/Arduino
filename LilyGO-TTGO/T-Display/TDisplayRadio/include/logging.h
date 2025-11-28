#pragma once

#include <Arduino.h>

#define DEBUG_CONSOLE

#ifdef DEBUG_CONSOLE
    #define LOG(...)    {Serial.printf(__VA_ARGS__);}
    #define LOGN(...)   {Serial.printf(__VA_ARGS__);Serial.println();}
#else
    #define LOG(...)
    #define LOGN(...)
#endif
