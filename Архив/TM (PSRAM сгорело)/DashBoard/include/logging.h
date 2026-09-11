#pragma once

#include <Arduino.h>

#define DEBUG_CONSOLE

#ifdef DEBUG_CONSOLE
    #define LOG(...)        {Serial.printf(__VA_ARGS__);}
    #define LOG_EXT(...)    {tft.printf(__VA_ARGS__);}
#else
    #define LOG(...)
    #define LOG_EXT(...)
#endif
