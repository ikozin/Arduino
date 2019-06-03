#include "DS3231.h"
#include "Wire.h"

void DS3231::begin()
{
  Wire.begin();
}
 
void DS3231::setDate(uint8_t day, uint8_t month, uint16_t year)
{
  int a = (14 - month) / 12;
  int y = year - a;
  int m = month + 12 * a - 2;
  uint8_t dayOfWeek = 1 + (7000 + (day + y + y / 4 - y / 100 + y / 400 + (31 * m) / 12)) % 7;
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

void DS3231::setTime(uint8_t second, uint8_t minute, uint8_t hour)
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

char* DS3231::getTextDate()
{
  Wire.beginTransmission(DS3231_RTC);
  Wire.write(3);
  Wire.endTransmission();
  Wire.requestFrom(DS3231_RTC, 4);
  uint8_t dayOfWeek = Wire.read() - 1;
  uint8_t day = Wire.read();
  uint8_t month = Wire.read() - 1;
  uint16_t year = 0x2000U + Wire.read();
  char* pText = data;
  strcpy(pText, _daysOfWeek[dayOfWeek]);
  pText += strlen(_daysOfWeek[dayOfWeek]);  
  *pText++ = ' ';
  pText = bin2hex(pText, day);
  *pText++ = ' ';
  strcpy(pText, _months[month]);
  pText += strlen(_months[month]);
  *pText++ = ' ';
  pText = bin2hex(pText, year);
  return data;
}

char* DS3231::getTextTime()
{
  Wire.beginTransmission(DS3231_RTC);
  Wire.write(0);
  Wire.endTransmission();
  Wire.requestFrom(DS3231_RTC, 3);
  uint8_t second = Wire.read();
  uint8_t minute = Wire.read();
  uint8_t hour = Wire.read();
  char* pText = data;
  pText = bin2hex(pText, hour);
  *pText++ = ':';
  pText = bin2hex(pText, minute);
  *pText++ = ':';
  pText = bin2hex(pText, second);
  return data;
}

uint16_t DS3231::getTime()
{
  Wire.beginTransmission(DS3231_RTC);
  Wire.write(1);
  Wire.endTransmission();
  Wire.requestFrom(DS3231_RTC, 2);
  uint8_t minute = Wire.read();
  uint8_t hour = Wire.read();
  return makeWord(hour, minute);
}

char* DS3231::bin2hex(char* pText, uint8_t value)
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

char* DS3231::bin2hex(char* pText, uint16_t value)
{
  pText = bin2hex(pText, highByte(value));
  pText = bin2hex(pText, lowByte(value));
  return pText;
}

uint8_t DS3231::dec2bcd(uint8_t value)
{
  byte b = (value * 103) >> 10;
  return (b * 16 + value - (b * 10));  
}
