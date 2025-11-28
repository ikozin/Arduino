#pragma once

#include <Arduino.h>
#include <TFT_eSPI.h>        // Подключение Библиотеки Lovyan GFX

#if !defined(USER_SETUP_ID) || USER_SETUP_ID != 25
    #error Ошибка настройки TFT_eSPI, необходимо подключить "User_Setups/Setup25_TTGO_T_Display.h"
#endif
