 /*

Arduino UNO  - Flash Memory  32 KB (ATmega328P) of which 0.5 KB used by bootloader
Arduino Mega - Flash Memory  256 KB of which 8 KB used by bootloader

I2C EEPROM 24LC02 - 24LC16
24LC02  https://static.chipdip.ru/lib/204/DOC000204386.pdf
24LC04  https://static.chipdip.ru/lib/204/DOC000204591.pdf
24LC08  https://static.chipdip.ru/lib/204/DOC000204351.pdf
24LC16  https://static.chipdip.ru/lib/204/DOC000204466.pdf

Распиновка 24LC02 - 24LC16
    -----------
 1-| A0     +5V|-8
 2-| A1      WP|-7
 3-| A2     SCL|-6
 4-| GND    SDA|-5
    -----------

Распиновка платы
  -------------------
 |                   |
 |    A0 A1 A2       |
 |                   |
  -------------------
    |   |     |   |
   VCC GND   SCL SDA

A0   адрес устройства на шине I2C !!! НЕ ИСПОЛЬЗУЮТСЯ !!! НЕ ПОДКЛЮЧЕНЫ !!!
A1   адрес устройства на шине I2C !!! НЕ ИСПОЛЬЗУЮТСЯ !!! НЕ ПОДКЛЮЧЕНЫ !!!
A2   адрес устройства на шине I2C !!! НЕ ИСПОЛЬЗУЮТСЯ !!! НЕ ПОДКЛЮЧЕНЫ !!!
GND  общий
SDA  шина I2C
SCL  шина I2C
WP   защита от записи (Если подключить к "плюсу" - нельзя записывать, к "минусу" - можно записывать)
VCC  +5V

Базовый адрес 0x50 !!!
В двоичной системе адрес устройства выглядит так: 01010xxx

Arduino
 SCL   A5
 SDA   A4

Размер памяти
24LC02 = 256
24LC04 = 512
24LC08 = 1024
24LC16 = 2048

Размер буфера для записи
24LC02 = 8
24LC04 = 16
24LC08 = 16
24LC16 = 16
*/
#include <Wire.h>
#include "data.h"

//#define _24LC02_
//#define _24LC04_
//#define _24LC08_
#define _24LC16_

#if !defined(_24LC02_) && !defined(_24LC04_) && !defined(_24LC08_) && !defined(_24LC16_)
#error Необходимо раскоментировать тип платы
#endif

#if defined(_24LC02_)
  #define MEMORY_SIZE 256   //Размер памяти
  #define BUFFER_SIZE 16    //Размер буфера для записи/чтения
#elif defined(_24LC04_)
  #define MEMORY_SIZE 512   //Размер памяти
  #define BUFFER_SIZE 16    //Размер буфера для записи/чтения
#elif defined(_24LC08_)
  #define MEMORY_SIZE 1024  //Размер памяти
  #define BUFFER_SIZE 16    //Размер буфера для записи/чтения
#elif defined(_24LC16_)
  #define MEMORY_SIZE 2048  //Размер памяти
  #define BUFFER_SIZE 16    //Размер буфера для записи/чтения
#endif

//Адрес устройства
#define DEVICE_EEPROM 0x50

//Буфер для чтения
byte data[BUFFER_SIZE];

uint8_t makeDevAddress(uint8_t device, uint16_t address) {
    return (uint8_t)(device | (highByte(address) & 0x07));
}

void EEPROM_Write(uint8_t device, uint16_t address, uint8_t* buffer) {
    Wire.beginTransmission(makeDevAddress(device, address));
    Wire.write(lowByte(address));
    for (uint16_t i = 0; i < BUFFER_SIZE; i++) {
      Wire.write(buffer[i]);
    }
    Wire.endTransmission();
    delay(5);
}

void EEPROM_Read(uint8_t device, uint16_t address, uint8_t* buffer) {
  device = makeDevAddress(device, address);
  Wire.beginTransmission(device);
  Wire.write(lowByte(address));
  Wire.endTransmission();
  Wire.requestFrom(device,(uint8_t)BUFFER_SIZE);
  for (uint16_t i = 0; i < BUFFER_SIZE; i++ ) {
    if (Wire.available()) buffer[i] = Wire.read();
  }
}

char text[32];

void setup() {
  Wire.begin();
  Serial.begin(9600);
  while (!Serial) {}

  Serial.print(F("Memory size:"));
  Serial.println(MEMORY_SIZE);
  Serial.println(F("Start Writing"));
  for (uint16_t addr = 0; addr < MEMORY_SIZE; addr += BUFFER_SIZE) {
    EEPROM_Write(DEVICE_EEPROM, addr, &dataMemory[addr]);
  }
  delay(100);

  Serial.println(F("Start Reading"));
  for (uint16_t addr = 0; addr < MEMORY_SIZE; addr += BUFFER_SIZE) {
    Serial.println();      
    sprintf(text, "%04X", addr);
    Serial.print(text);      
    EEPROM_Read(DEVICE_EEPROM, addr, data);
    for (uint16_t i = 0; i < BUFFER_SIZE; i++) {
      sprintf(text, " %02X", data[i]);
      Serial.print(text);      
    }
  }
  delay(100);
  Serial.println(F("Stoped"));
}

void loop() {
}
