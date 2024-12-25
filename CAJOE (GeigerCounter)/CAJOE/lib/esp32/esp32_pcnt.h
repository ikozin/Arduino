#pragma once

#include <Arduino.h>

#if defined(ESP32)

#include <driver/pcnt.h>

void pcntSetup(gpio_num_t pin, pcnt_unit_t unit, pcnt_channel_t channel = PCNT_CHANNEL_0);

#endif