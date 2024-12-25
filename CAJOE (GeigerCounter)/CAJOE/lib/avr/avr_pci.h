#pragma once

#include <Arduino.h>

#if defined(__AVR__)

typedef void (*isr_handler_t)(uint8_t);

void pciSetup(byte pin, isr_handler_t func);

#endif