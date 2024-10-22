#ifndef _RADIO_H
#define _RADIO_H

#include <Arduino.h>
#include <EEPROM.h>
#include "LiquidCrystal_I2C.h"
#include "RTClib.h"
#include "Melodies.h"

const int TONE_PIN = 10;

const int lcdLines = 4;
const int lcdRows = 20;

const int controlPin = 3; // 3 or 2 only!!! так как используется прерывание
const int buttonPin1 = 4;
const int buttonPin2 = 5;
const int buttonPin3 = 6;
const int buttonPin4 = 7;

const byte MODE_CLOCK = 0;
const byte MODE_ALARM = 1;
const byte MODE_RADIO = 2;
const byte MODE_SETTING = 3;

typedef struct _radioItem
{
	long wave;
	char name[21];
} RadioItem;


typedef struct _alarmItem
{
	byte week;
	byte hour;
	byte minute;
	byte second;
} AlarmItem;

typedef void (*ActionInit)(int);
typedef void (*ActionSelect)(void);

extern volatile byte mode;
extern LiquidCrystal_I2C lcd;
extern RTC_DS1307 rtc;
extern int8_t corrSec;
extern bool corrApplied;

extern AlarmItem alarmOn[4];
extern AlarmItem alarmOff[4];

#ifdef RELOCATE
static int EEPROM_ADDR_CONFIGURATION = 4;
#else 
#define EEPROM_ADDR_CONFIGURATION     4
#endif
#define EEPROM_ADDR_RADIO_INDEX       (EEPROM_ADDR_CONFIGURATION)
#define EEPROM_ADDR_RADIO_VOLUME      (EEPROM_ADDR_CONFIGURATION + 1)
#define EEPROM_ADDR_CORRECTION_SEC    (EEPROM_ADDR_CONFIGURATION + 2)
#define EEPROM_ADDR_ALARM_INDEX       (EEPROM_ADDR_CONFIGURATION + 3)
#define EEPROM_ADDR_ALARM_ON1         (EEPROM_ADDR_CONFIGURATION + 4)
#define EEPROM_ADDR_ALARM_ON2         (EEPROM_ADDR_ALARM_ON1 + sizeof(AlarmItem))
#define EEPROM_ADDR_ALARM_ON3         (EEPROM_ADDR_ALARM_ON2 + sizeof(AlarmItem))
#define EEPROM_ADDR_ALARM_ON4         (EEPROM_ADDR_ALARM_ON3 + sizeof(AlarmItem))
#define EEPROM_ADDR_ALARM_OFF1        (EEPROM_ADDR_ALARM_ON4 + sizeof(AlarmItem))
#define EEPROM_ADDR_ALARM_OFF2        (EEPROM_ADDR_ALARM_OFF1 + sizeof(AlarmItem))
#define EEPROM_ADDR_ALARM_OFF3        (EEPROM_ADDR_ALARM_OFF2 + sizeof(AlarmItem))
#define EEPROM_ADDR_ALARM_OFF4        (EEPROM_ADDR_ALARM_OFF3 + sizeof(AlarmItem))

#define FLAG_MONDAY		  B00000001
#define FLAG_TUESDAY	  B00000010
#define FLAG_WEDNESDAY	B00000100
#define FLAG_THURSDAY	  B00001000
#define FLAG_FRIDAY		  B00010000
#define FLAG_SATURDAY	  B00100000
#define FLAG_SUNDAY		  B01000000
#define FLAG_WORK_WEEK	(FLAG_MONDAY | FLAG_TUESDAY | FLAG_WEDNESDAY | FLAG_THURSDAY | FLAG_FRIDAY)


void loopSettings();
void loadAlarmData(uint16_t, AlarmItem*);
void saveAlarmData(uint16_t, AlarmItem*);

#endif // _RADIO_H
