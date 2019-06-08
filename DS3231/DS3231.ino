/*
https://static.chipdip.ru/lib/248/DOC000248544.pdf

SCL  - A5
SDA  - A4
       -------------------
 32K -|                   |
 SQW -|                   |
 SCL -|                   |
 SDA -|                   |
 VCC -|                   |
 GND -|                   |
       -------------------

*/

#include "DateTimeModuleHelper.h"
#include <Wire.h>

//Адрес устройства
#define DS3231_ROM  0x57
#define DS3231_RTC  0x68

const char* months[12] =
{
  "января", 
  "февраля", 
  "марта", 
  "апреля", 
  "мая", 
  "июня", 
  "июля", 
  "августа", 
  "сентября", 
  "октября", 
  "ноября", 
  "декабря" 
};


const char* daysOfWeek[7] =
{
  "ВС", 
  "ПН", 
  "ВТ", 
  "СР", 
  "ЧТ", 
  "ПТ", 
  "CБ" 
};

char text[160];

void initModule();
char* getDateTime();
void setDate(int, int, int);
void setTime(int, int, int);
void dump();

DateTimeModuleHelper helper(initModule, getDateTime, setDate, setTime, dump);

void setup()
{
  helper.setup();
}

void loop()
{
  helper.loop();
}

void initModule()
{
  Wire.begin();
}

void setDate(int year, int month, int day)
{
  uint8_t dayOfWeek = helper.getDayOfWeek(year, month, day);
  day = dec2bcd(day);
  month = dec2bcd(month);
  year = dec2bcd(year % 100);
  Wire.beginTransmission(DS3231_RTC);
  Wire.write(3);
  Wire.write(dayOfWeek);  // set day of week (1=Sunday, 7=Saturday)
  Wire.write(day);
  Wire.write(month);
  Wire.write(year);
  Wire.endTransmission();
}
    
void setTime(int hour, int minute, int second)
{
  second = dec2bcd(second);
  minute = dec2bcd(minute);
  hour = dec2bcd(hour);
  Wire.beginTransmission(DS3231_RTC);
  Wire.write(0);
  Wire.write(second);
  Wire.write(minute);
  Wire.write(hour);
  Wire.endTransmission();
}

char* getDateTime()
{
  char* pText = text;

  Wire.beginTransmission(DS3231_RTC);
  Wire.write(3);
  Wire.endTransmission();
  Wire.requestFrom(DS3231_RTC, 4);
  uint8_t dayOfWeek = Wire.read() - 1;
  uint8_t day = Wire.read();
  uint8_t month = Wire.read() - 1;
  uint16_t year = 0x2000 | Wire.read();
  strcpy(pText, daysOfWeek[dayOfWeek]);
  pText += strlen(daysOfWeek[dayOfWeek]);  
  *pText++ = ' ';
  pText = bin2hex(pText, day);
  *pText++ = ' ';
  strcpy(pText, months[month]);
  pText += strlen(months[month]);
  *pText++ = ' ';
  pText = bin2hex(pText, year);

  *pText++ = ',';
  Wire.beginTransmission(DS3231_RTC);
  Wire.write(0);
  Wire.endTransmission();
  Wire.requestFrom(DS3231_RTC, 3);
  uint8_t second = Wire.read();
  uint8_t minute = Wire.read();
  uint8_t hour = Wire.read();
  pText = bin2hex(pText, hour);
  *pText++ = ':';
  pText = bin2hex(pText, minute);
  *pText++ = ':';
  pText = bin2hex(pText, second);
  return text;
}

void dump()
{
  Wire.beginTransmission(DS3231_RTC);
  Wire.write(0);
  Wire.endTransmission();
  Wire.requestFrom(DS3231_RTC, 19);
  uint8_t _Seconds = Wire.read();
  uint8_t _Minutes = Wire.read();
  uint8_t _Hours = Wire.read();
  uint8_t _Day = Wire.read();
  uint8_t _Date = Wire.read();
  uint8_t _Month_Century = Wire.read();
  uint8_t _Year = Wire.read();
  uint8_t _Alarm_1_Seconds = Wire.read();
  uint8_t _Alarm_1_Minutes = Wire.read();
  uint8_t _Alarm_1_Hours = Wire.read();
  uint8_t _Alarm_1_Day_Date = Wire.read();
  uint8_t _Alarm_2_Minutes = Wire.read();
  uint8_t _Alarm_2_Hours = Wire.read();
  uint8_t _Alarm_2_Day_Date = Wire.read();
  uint8_t _Control = Wire.read();
  uint8_t _Control_Status = Wire.read();
  uint8_t _Aging_Offset = Wire.read();
  uint8_t _MSB_of_Temp = Wire.read();
  uint8_t _LSB_of_Temp = Wire.read();
    
  char* pText;
  
  pText = text;
  pText = bin2hex(pText, _Seconds);
  *pText++ = ' ';
  pText = bin2hex(pText, _Minutes);
  *pText++ = ' ';
  pText = bin2hex(pText, _Hours);
  *pText++ = ' ';
  pText = bin2hex(pText, _Day);
  *pText++ = ' ';
  pText = bin2hex(pText, _Date);
  *pText++ = ' ';
  pText = bin2hex(pText, _Month_Century);
  *pText++ = ' ';
  pText = bin2hex(pText, _Year);
  Serial.println(text);

  pText = text;
  pText = bin2hex(pText, _Alarm_1_Seconds);
  *pText++ = ' ';
  pText = bin2hex(pText, _Alarm_1_Minutes);
  *pText++ = ' ';
  pText = bin2hex(pText, _Alarm_1_Hours);
  *pText++ = ' ';
  pText = bin2hex(pText, _Alarm_1_Day_Date);
  Serial.println(text);
  
  pText = text;
  pText = bin2hex(pText, _Alarm_2_Minutes);
  *pText++ = ' ';
  pText = bin2hex(pText, _Alarm_2_Hours);
  *pText++ = ' ';
  pText = bin2hex(pText, _Alarm_2_Day_Date);
  Serial.println(text);
  
  pText = text;
  pText = bin2hex(pText, _Control);
  *pText++ = ' ';
  pText = bin2hex(pText, _Control_Status);
  *pText++ = ' ';
  pText = bin2hex(pText, _Aging_Offset);
  *pText++ = ' ';
  pText = bin2hex(pText, _MSB_of_Temp);
  *pText++ = ' ';
  pText = bin2hex(pText, _LSB_of_Temp);
  Serial.println(text);
  
  Serial.println();
}

char* bin2hex(char* pText, uint8_t value)
{
    for (int i = 0; i < 2; i++)
    {
        byte v = (byte)((value & 0xF0) >> 4);
        v = (v > 9) ? v + 55 : v + 48;
        *pText++ = (char)v;
        value <<= 4;
    }
    *pText = '\0';
    return pText;
}

char* bin2hex(char* pText, uint16_t value)
{
  pText = bin2hex(pText, highByte(value));
  pText = bin2hex(pText, lowByte(value));
  return pText;
}

uint8_t dec2bcd(uint8_t n)
{
  byte b = (n * 103) >> 10;
  return (b * 16 + n-(b*10));  
}    
