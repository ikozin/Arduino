#pragma once

#include <Arduino.h>
// #include <Preferences.h>
// #include <typeinfo>
#include "logging.h"

#define BIT_TIME    ( 1 << 0 )
#define BIT_STATION ( 1 << 1 )
#define BIT_TRACK   ( 1 << 2 )
#define BIT_VOLUME  ( 1 << 3 )
#define BIT_MUTE    ( 1 << 4 )

#define BIT_ALL     ( BIT_TIME | BIT_STATION | BIT_TRACK | BIT_VOLUME | BIT_MUTE )
