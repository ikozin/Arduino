#ifndef DS3231_H
#define DS3231_H

#include <Arduino.h>

//Адрес устройства
#define DS3231_ROM  0x57
#define DS3231_RTC  0x68

class DS3231
{
  public:
    void begin();
    void setDate(uint8_t day, uint8_t month, uint16_t year);
    void setTime(uint8_t second, uint8_t minute, uint8_t hour);
    void setAgingOffset(int8_t value);
    char* getTextDate();
    char* getTextTime();
    uint16_t getTime();
  private:
    char data[128];
    const char* _months[12] = { "января", "февраля", "марта", "апреля", "мая", "июня", "июля", "августа", "сентября", "октября", "ноября", "декабря" };
    const char* _daysOfWeek[7] = { "ВС", "ПН", "ВТ", "СР", "ЧТ", "ПТ", "CБ" };    

    char* bin2hex(char* pText, uint8_t value);
    char* bin2hex(char* pText, uint16_t value);
    uint8_t dec2bcd(uint8_t value);
};

#endif
