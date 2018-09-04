/*
I2C EEPROM 24LC32 - 24LC512
24LC32   https://static.chipdip.ru/lib/761/DOC000761242.pdf
24LC64   https://static.chipdip.ru/lib/204/DOC000204746.pdf
24LC128  https://static.chipdip.ru/lib/302/DOC000302152.pdf
24LC256  https://static.chipdip.ru/lib/204/DOC000204529.pdf
24LC512  https://static.chipdip.ru/lib/238/DOC000238406.pdf

Распиновка 24LC32 - 24LC512
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

A0   адрес устройства на шине I2C
A1   адрес устройства на шине I2C
A2   адрес устройства на шине I2C
GND  общий
SDA  шина I2C
SCL  шина I2C
WP   защита от записи (Если подключить к "плюсу" - нельзя записывать, к "минусу" - можно записывать)
VCC  +5V

Базовый адрес 0x50 !!!
В двоичной системе адрес устройства выглядит так: 01010xxx (A2, A1, A0), если A2, A1, A0 подключить к GND, то адрес 001010000 = 0x50

Arduino
 SCL   A5
 SDA   A4

Размер памяти
24LC32 = 4096
24LC64 = 8192
24LC128 = 16384
24LC256 = 32768
24LC512 = 65536

Размер буфера для записи
24LC32 = 32
24LC64 = 32
24LC128 = 64
24LC256 = 64
24LC512 = 128
*/
#include <Wire.h>

//Адрес устройства
#define DEVICE_EEPROM 0x50
//Размер буфера для записи/чтения
#define BUFFER_SIZE   16
byte data[BUFFER_SIZE];
//Размер памяти
#define MEMORY_SIZE 8192

void fillBuffer(uint8_t* buffer, byte value)
{
  for (int i = 0; i < BUFFER_SIZE; i++) buffer[i] = value;
}

void EEPROM_Write(uint8_t device, int address, uint8_t* buffer)
{
    Wire.beginTransmission(address);
    Wire.write(highByte(address));
    Wire.write(lowByte(address));
    for (int i = 0; i < BUFFER_SIZE; i++)
      Wire.write(buffer[i]);
    Wire.endTransmission();
    delay(5);
}

void EEPROM_Read(uint8_t device, int address, uint8_t* buffer)
{
  Wire.beginTransmission(device);
  Wire.write(highByte(address));
  Wire.write(lowByte(address));
  Wire.endTransmission();
  Wire.requestFrom(device,(uint8_t)BUFFER_SIZE);
  for (int i = 0; i < BUFFER_SIZE; i++ )
    if (Wire.available()) buffer[i] = Wire.read();
}

char text[32];

void setup()
{
  Wire.begin();
  Serial.begin(9600);
  while (!Serial) {}

  Serial.println(F("Start 24L64 Writing"));
  byte value = 0;
  for (int addr = 0; addr < MEMORY_SIZE; addr += BUFFER_SIZE)
  {
    fillBuffer(data, value++);
    EEPROM_Write(DEVICE_EEPROM, addr, data);
  }
  delay(100);

  Serial.println(F("Start 24LC64 Reading"));
  fillBuffer(data, 0x00);
  for (int addr = 0; addr < MEMORY_SIZE; addr += BUFFER_SIZE)
  {
    Serial.println();      
    sprintf(text, "%04X ", addr);
    Serial.print(text);      
    EEPROM_Read(DEVICE_EEPROM, addr, data);
    for (int i = 0; i < BUFFER_SIZE; i++)
    {
      sprintf(text, "%02X ", data[i]);
      Serial.print(text);      
    }
  }
  delay(100);
}

void loop()
{
}
