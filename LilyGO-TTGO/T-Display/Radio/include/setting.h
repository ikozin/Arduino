#ifndef _SETTING_H_
#define _SETTING_H_

#include <Arduino.h>
#include <WiFi.h>
#include <Preferences.h>
#include <SPIFFS.h>
#include <TFT_eSPI.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include "logging.h"

void setSettings(Preferences& prefs, TFT_eSPI& tft, AsyncWebServer& server);

#endif