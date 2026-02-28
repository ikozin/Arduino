/*

Arduino UNO  - Flash Memory  32 KB (ATmega328P) of which 0.5 KB used by bootloader
Arduino Mega - Flash Memory  256 KB of which 8 KB used by bootloader

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

         Arduino MEGA2560
   -----------------------------
  |       |             |D21/SCL|-- SCL
  |       |             |D20/SDA|-- SDA
  |       |   Arduino   | AREF  |
  |       |  MEGA 2560  |  GND  |--
  |-------|             | AREF  |
  |  NC   |             |  D13  |
  | IOREF |             |  D12  |
  |  RST  |             |  D11  |
  |  3V3  |             |  D10  |
--|  +5V  |             |  D9   |
--|  GND  |             |  D8   |
--|  GND  |             |-------|
  |  VIN  |             |  D7   |
  |-------|             |  D6   |
  |  A0   |             |  D5   |
  |  A1   |             |  D4   |
  |  A2   |             |  D3   |
  |  A3   |             |  D2   |
  |  A4   |             |  D1   |
  |  A5   |             |  D0   |
  |  A6   |             |-------|
  |  A7   |             |  D14  |
  |-------|             |  D15  |
  |  A8   |             |  D16  |
  |  A9   |             |  D17  |
  |  A10  |             |  D18  |
  |  A11  |             |  D19  |
  |  A12  |             |D20/SDA|-- SDA
  |  A13  |             |D21/SCL|-- SCL
  |  A14  |             |-------|
  |  A15  |             |       |
  |-----------------------------|
  | ||||||||||||||||||||||||||| |
   -----------------------------
*/

#include <Arduino.h>
#include <Wire.h>
#define COLOR_DEBTH 3
#include <microLED.h>   // подключаем библу
#include <color_utility.h>

//#define _24LC32_
//#define _24LC64_
//#define _24LC128_
//#define _24LC256_
#define _24LC512_

#if !defined(_24LC32_) && !defined(_24LC64_) && !defined(_24LC128_) && !defined(_24LC256_) && !defined(_24LC512_)
#error Необходимо раскоментировать тип платы
#endif

#if defined(_24LC32_)
  #define MEMORY_SIZE 4096  //Размер памяти
  #define BUFFER_SIZE 32    //Размер буфера для записи/чтения
#elif defined(_24LC64_)
  #define MEMORY_SIZE 8192  //Размер памяти
  #define BUFFER_SIZE 32    //Размер буфера для записи/чтения
#elif defined(_24LC128_)
  #define MEMORY_SIZE 16384 //Размер памяти
  #define BUFFER_SIZE 64    //Размер буфера для записи/чтения
#elif defined(_24LC256_)
  #define MEMORY_SIZE 32768 //Размер памяти
  #define BUFFER_SIZE 64    //Размер буфера для записи/чтения
#elif defined(_24LC512_)
  #define MEMORY_SIZE 65536 //Размер памяти
  #define BUFFER_SIZE 128   //Размер буфера для записи/чтения
#endif

#if (defined(_24LC256_) || defined(_24LC512_)) && !defined(__AVR_ATmega2560__)
#error Select board ATMEGA2560
#endif


// константы для удобства
#define NUMLEDS 4      // кол-во светодиодов
//Адрес устройства
#define DEVICE_EEPROM 0x50

typedef struct __attribute__((packed)) {
  uint8_t r;
  uint8_t g;
  uint8_t b;
} COLOR_LED;

typedef struct __attribute__((packed)) {
  uint16_t  time;
  COLOR_LED LED[NUMLEDS];
} STRIP_DATA;

STRIP_DATA  strip_data = { .time = 0 };
//Буфер для чтения
uint8_t data[BUFFER_SIZE];

void EEPROM_Write(uint16_t address, uint8_t* buffer, uint8_t size) {
    Wire.beginTransmission(DEVICE_EEPROM);
    Wire.write(highByte(address));
    Wire.write(lowByte(address));
    for (uint8_t i = 0; i < (uint8_t)size; i++) {
      Wire.write(buffer[i]);
    }
    Wire.endTransmission();
    delay(5);
}

void EEPROM_Read(uint8_t device, uint16_t address, uint8_t* buffer, uint8_t size) {
  Wire.beginTransmission(device);
  Wire.write(highByte(address));
  Wire.write(lowByte(address));
  Wire.endTransmission();
  Wire.requestFrom(device, size);
  for (uint8_t i = 0; i < size; i++ ) {
    if (Wire.available()) buffer[i] = Wire.read();
  }
}

void EEPROM_Clear() {
  memset(data, 0xFF, sizeof(data));
  for (uint16_t addr = 0; addr < MEMORY_SIZE; addr += sizeof(data)) {
    EEPROM_Write(addr, data, sizeof(data)); 
  }
  delay(5);
}

char text[32];

/*

      3
     / \
5---4   2---1
  \   0   /
   6     10
  / / 8 \ \
  7       9
0          - центр
2 4 6 8 10 - вершины
1 3 5 7 9  - вершины

*/

uint16_t runningLight(uint16_t address, uint16_t delay, mData color) {
  uint16_t size = 0;
  uint8_t index = 0;  
  for (uint8_t i = 0; i < NUMLEDS; i++) {
    memset(&strip_data, 0, sizeof(strip_data));
    strip_data.time = delay;
    strip_data.LED[index].r = color.r;
    strip_data.LED[index].g = color.g;
    strip_data.LED[index].b = color.b;
    EEPROM_Write(address, reinterpret_cast<uint8_t*>(&strip_data), sizeof(strip_data));
    size += sizeof(strip_data);
    address += sizeof(strip_data);
    index++;
  }
  return size;
}

void setup() {
  Wire.begin();
  Serial.begin(115200);
  while (!Serial) {}
  Serial.print(F("Start"));
  EEPROM_Clear();

  Serial.print(F("Memory size:"));
  Serial.println(MEMORY_SIZE);
  Serial.println(F("Start Writing"));
  uint16_t start = 0;
  start += runningLight(start, 200, mData(COLORS::mRed));
  start += runningLight(start, 200, mData(COLORS::mGreen));
  start += runningLight(start, 200, mData(COLORS::mBlue));
  memset(&strip_data, 0, sizeof(strip_data));
  EEPROM_Write(start, reinterpret_cast<uint8_t*>(&strip_data), sizeof(strip_data));

  Serial.println(F("Start Reading"));
  for (uint16_t addr = 0; addr < 2*1024; addr += sizeof(strip_data)) {
    EEPROM_Read(DEVICE_EEPROM, addr, (uint8_t*)&strip_data, sizeof(strip_data));
    sprintf(text, "%5d:", strip_data.time);
    Serial.print(text);
    for (uint16_t i = 0; i < NUMLEDS; i++) {
      if (strip_data.LED[i].r == 0) sprintf(text, "(,"); else sprintf(text, "(%02X,", strip_data.LED[i].r); Serial.print(text);
      if (strip_data.LED[i].g == 0) sprintf(text, ","); else sprintf(text, "%02X,", strip_data.LED[i].g);   Serial.print(text);
      if (strip_data.LED[i].b == 0) sprintf(text, ")"); else sprintf(text, "%02X)", strip_data.LED[i].b);   Serial.print(text);
    }
    Serial.println();
  }
  Serial.println();
  delay(100);
  Serial.println(F("Stoped"));
}

void loop() {
}
