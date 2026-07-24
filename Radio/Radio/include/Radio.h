#pragma once

#include <Arduino.h>
#include <EEPROM.h>
#include <Wire.h>
#include <SPI.h>
#include <GyverIO.h>
#include "LiquidCrystal_I2C.h"
#include "Melodies.h"
#include "MP1090S.h"
#include "Storage.h"

const int lcdLines = 4;
const int lcdRows = 20;

const int radio_RST = 8;
const int radio_SEN = 9;

const int TONE_PIN = 10;

const byte MODE_CLOCK = 0;
const byte MODE_ALARM = 1;
const byte MODE_RADIO = 2;
const byte MODE_SETTING = 3;


typedef void (*ActionInit)(int);
typedef void (*ActionSelect)(void);

