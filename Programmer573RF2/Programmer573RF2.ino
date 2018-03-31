/*
//////////////////////////////////////////
КР1533ИР24 x 2

       -----------------
 16 --|                 |
 15 --|   X    X    X   |-- GND
 14 --|   X    X    X   |-- VCC  (+5V)
 13 --|   DL   SL   E   |
 12 --|                 |
 11 --|                 |
 10 --|                 |-- PR
 9  --|                 |-- PL
 8  --|                 |-- C
 7  --|                 |-- E   (pullup)
 6  --|                 |-- R   (pullup)
 5  --|                 |-- SR  (pullup)
 4  --|                 |-- SL  (pullup)
 3  --|  DR    R    SR  |-- DL  (pullup)
 2  --|   X    X    X   |-- DR  (pullup)
 1  --|   X    X    X   |
       -----------------

К573РФ2
http://www.inp.nsk.su/~kozak/mem/mem18.htm
http://www.eandc.ru/pdf/mikroskhema/k573rf2.pdf
http://vip-cxema.org/index.php/home/mikrokontrollery/357-prostoj-kopirovshchik-rpzu-k573rf2-5

            CE OE
             |  |
        ------------------------
 A10 --|                        |
 A9  --|                        |
 A8  --|                        |
 A7  --|                        |
 A6  --|                        |-- GND
 A5  --|                        |-- VCC
 A4  --|                        |
 A3  --|                        |
 A2  --|                        |
 A1  --|                        |
 A0  --|                        |
        ------------------------
         |  |  |   |   |   |  |
        D0 D1 D2 D3 D4 D5 D6 D7

Vpp завязан на OE
OE = L, Vpp = 5v
OE = H, Vpp = 25v		
------------------------------------------------------------------------
Входы                      Выходы     Режим работы
------------------------------------------------------------------------
A0...A10  -CE  -OE  Vpp    D0...D7   
------------------------------------------------------------------------
  L/H      L    L    5v      Out      Считывание
  L/H      H    H   24v      L/H      Запись
   X       L    H    5v       Z       Невыбор
   X       H    X    5v       Z       Хранение(пониженная мощность)
   X       L    H   24v       Z       Запрет записи
  L/H      L    L   24v      Out      Проверка записи
------------------------------------------------------------------------

PCF8574A
https://static.chipdip.ru/lib/205/DOC000205430.pdf

    Плата
    --------------------
   |                    |
   |    A0 A1 A2        |
   |                    |
   | (X) 0x01  0x80 (X) |
   | (X) 0x02  0x40 (X) |
   | (X) 0x04  0x20 (X) |
   | (X) 0x08  0x10 (X) |
    --------------------
      |   |     |   |
     VCC GND   SCL SDA

Arduino
 SCL   A5
 SDA   A4
Адрес, базовый 0x38
 00 00 01 01 01 A2 A1 A0
*/

#include <SPI.h>
#include <SD.h>
#include <Wire.h>

#define DR  A0
#define C   A1
#define CE  A2
#define OE  A3

#define D0  2
#define D1  3
#define D2  4
#define D3  5
#define D4  6
#define D5  7
#define D6  8
#define D7  9

#define SD_CS 10

#define ADDRESS_KEYBOARD  0x38
#define ADDRESS_LEDBOARD  0x39

#define LED_READY  0x10
#define LED_READ   0x20
#define LED_WRITE  0x40
#define LED_ERROR  0x80

#define BUFFER_SIZE   16
uint8_t dataRow[BUFFER_SIZE];
#define textLen       64
char text[textLen];


void setup()
{
  // К573РФ2
  pinMode(CE, OUTPUT);
  pinMode(OE, OUTPUT);
  SetDisableMode();
  InitReadMode();

  // КР1533ИР24 x 2
  pinMode(DR, OUTPUT);
  pinMode(C,  OUTPUT);
  digitalWrite(C,  LOW);
  digitalWrite(DR, LOW);
  registerWriteData(0);

  // PCF8574A
  Wire.begin();
  Wire.beginTransmission(ADDRESS_KEYBOARD);
  Wire.write(B11111111);    //Конфигурация всех порты PCF8574A как вход
  Wire.endTransmission();
  Wire.beginTransmission(ADDRESS_LEDBOARD);
  Wire.write(B00000000);    //Конфигурация всех порты PCF8574A как выход (не совсем корректно, можно вообще ничего не писать, но так мы сбрасываем индикацию)
  Wire.endTransmission();

  // Serial
  Serial.begin(9600);
  while (!Serial) {}
  Serial.println(F("Start"));

  // SD
  Wire.begin();
  if (!SD.begin(SD_CS))
  {
    Serial.println(F("Initialization failed!"));
    for (;;);
  }
  Serial.println(F("SD card initialized."));

  Serial.println(F("Check"));
  Serial.println(F("Read"));
  Serial.println(F("Write"));
  Serial.println(F("Comapre"));
  Serial.println();
  
  setLed(LED_READY);
}


void loop()
{
  switch (GetCommnad())
  {
    case 1:
      CheckMemoryMode();
      break;
    case 2:
      ReadMemoryMode();
      break;
    case 3:
      WriteMemoryMode();
      break;
    case 4:
      ComapreMemoryMode();
      break;
    default:
      break;
  }
  delay(100);
}


//////////////////////////////////////////
// Хранение(пониженная мощность) К573РФ2
//////////////////////////////////////////
void SetDisableMode()
{
  digitalWrite(OE, LOW);
  digitalWrite(CE, HIGH);
}


//////////////////////////////////////////
// Считывание К573РФ2
//////////////////////////////////////////
void SetReadMode()
{
  digitalWrite(OE, LOW);
  digitalWrite(CE, LOW);
}


//////////////////////////////////////////
// Запись К573РФ2
//////////////////////////////////////////
void SetWriteMode()
{
  digitalWrite(OE, HIGH);
  digitalWrite(CE, HIGH);
}


//////////////////////////////////////////
// Данные на считывание
//////////////////////////////////////////
void InitReadMode()
{
  pinMode(D0, INPUT_PULLUP);
  pinMode(D1, INPUT_PULLUP);
  pinMode(D2, INPUT_PULLUP);
  pinMode(D3, INPUT_PULLUP);
  pinMode(D4, INPUT_PULLUP);
  pinMode(D5, INPUT_PULLUP);
  pinMode(D6, INPUT_PULLUP);
  pinMode(D7, INPUT_PULLUP);
}


//////////////////////////////////////////
// Данные для записи
//////////////////////////////////////////
void InitWriteMode()
{
  pinMode(D0, OUTPUT);
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D4, OUTPUT);
  pinMode(D5, OUTPUT);
  pinMode(D6, OUTPUT);
  pinMode(D7, OUTPUT);
}


//////////////////////////////////////////
// Получаем нажатую кнопку (PCF8574A)
//////////////////////////////////////////
int GetCommnad()
{
  Wire.requestFrom(ADDRESS_KEYBOARD,1);
  while (!Wire.available());
  byte data = Wire.read();  //читаем состояние портов PCF8574P(кнопок)

  switch (data)
  {
    case 0x01:
    case 0x80:
      return 1;
    case 0x02:
    case 0x40:
      return 2;
    case 0x04:
    case 0x20:
      return 3;
    case 0x08:
    case 0x10:
      return 4;
  default:
      return 0;
  }
}


//////////////////////////////////////////
// Управляем индикацией (PCF8574A)
//////////////////////////////////////////
void setLed(uint8_t value)
{
  Wire.beginTransmission(ADDRESS_LEDBOARD);
  Wire.write(value);
  Wire.endTransmission();
}


//////////////////////////////////////////
// Читаем данные побитно
//////////////////////////////////////////
uint8_t ReadData()
{
  uint8_t data = 0;
  if (digitalRead(D0) == HIGH) bitSet(data, 0);
  if (digitalRead(D1) == HIGH) bitSet(data, 1);
  if (digitalRead(D2) == HIGH) bitSet(data, 2);
  if (digitalRead(D3) == HIGH) bitSet(data, 3);
  if (digitalRead(D4) == HIGH) bitSet(data, 4);
  if (digitalRead(D5) == HIGH) bitSet(data, 5);
  if (digitalRead(D6) == HIGH) bitSet(data, 6);
  if (digitalRead(D7) == HIGH) bitSet(data, 7);
  return data;
}


//////////////////////////////////////////
// Проверяем ППЗУ на чистоту.
// У чистой все байты должны быть 0xFF
//////////////////////////////////////////
void CheckMemoryMode()
{
  Serial.println(F("Start Check"));
  SD.remove("CHECK.TXT");
  File dataFile = SD.open("CHECK.TXT", FILE_WRITE);
  if (dataFile)
  {
    bool error = false;
    for (uint16_t address = 0; address < 2048; address++)
    {
      setLed(LED_READ | (error ? LED_ERROR: 0));
      registerWriteData(address);
      SetReadMode();
      delay(2);
      uint8_t data = ReadData();
      SetDisableMode();
      if (data != 0xFF)
      {
        error = true;
        char* pdata = bin2hex(text, address);
        *pdata++ = ' ';
        bin2hex(pdata, data);
        dataFile.println(text);
        Serial.println(text);
      }
    }
    dataFile.close();
    setLed(LED_READY | (error ? LED_ERROR: 0));
    if (error) Serial.println("\nError!");
  }
  else
  {
    setLed(LED_READY | LED_ERROR);
    Serial.println(F("Error create file: CHECK.TXT"));
  }
}


//////////////////////////////////////////
// Читаем ППЗУ.
// Считываем данные с ППЗУ и записываем их на SD в файл DUMP.TXT
//////////////////////////////////////////
void ReadMemoryMode()
{
  Serial.println(F("Start Read"));
  SD.remove("DUMP.TXT");
  File dataFile = SD.open("DUMP.TXT", FILE_WRITE);
  if (dataFile)
  {
    setLed(LED_READ);
    for (uint16_t address = 0; address < 2048; address += BUFFER_SIZE)
    {
      bin2hex(text, address);
      dataFile.print(text);
      Serial.print(text);

      for (int i = 0; i < BUFFER_SIZE; i++)
      {
        uint16_t addr = address + i;
        registerWriteData(addr);
        SetReadMode();
        delay(2);
        uint8_t data = ReadData();
        SetDisableMode();
        dataRow[i] = data;
      }
      char* pdata = text;
      for (int i = 0; i < BUFFER_SIZE; i++)
      {
        *pdata++ = ' ';
        pdata = bin2hex(pdata, dataRow[i]);
      }
      dataFile.println(text);
      Serial.println(text);
    }
    dataFile.close();
    setLed(LED_READY);
  }
  else
  {
    setLed(LED_READY | LED_ERROR);
    Serial.println(F("Error create file: DUMP.TXT"));
  }
}


//////////////////////////////////////////
// Пишем ППЗУ.
// Считываем данные из SD из файла DUMP.TXT и записываем их в ППЗУ
//////////////////////////////////////////
void WriteMemoryMode()
{
  Serial.println(F("Start Write"));
  File dataFile = SD.open("DUMP.TXT");
  if (dataFile)
  {
    bool error = false;
    setLed(LED_WRITE);
    InitWriteMode();
    while (!error)
    {
      int result;
      result = readLine(&dataFile, text, textLen);
      if (result == 0) break;
      Serial.println(text);
      int address, hex0, hex1, hex2, hex3, hex4, hex5, hex6, hex7, hex8, hex9, hexA, hexB, hexC, hexD, hexE, hexF;
      result = sscanf(text, "%04X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X", 
          &address, &hex0, &hex1, &hex2, &hex3, &hex4, &hex5, &hex6, &hex7, &hex8, &hex9, &hexA, &hexB, &hexC, &hexD, &hexE, &hexF);
      if (result != 17)
      {
        error = true;
        break;
      }
      dataRow[0x00] = hex0;// & 0xFF;
      dataRow[0x01] = hex1;// & 0xFF;
      dataRow[0x02] = hex2;// & 0xFF;
      dataRow[0x03] = hex3;// & 0xFF;
      dataRow[0x04] = hex4;// & 0xFF;
      dataRow[0x05] = hex5;// & 0xFF;
      dataRow[0x06] = hex6;// & 0xFF;
      dataRow[0x07] = hex7;// & 0xFF;
      dataRow[0x08] = hex8;// & 0xFF;
      dataRow[0x09] = hex9;// & 0xFF;
      dataRow[0x0A] = hexA;// & 0xFF;
      dataRow[0x0B] = hexB;// & 0xFF;
      dataRow[0x0C] = hexC;// & 0xFF;
      dataRow[0x0D] = hexD;// & 0xFF;
      dataRow[0x0E] = hexE;// & 0xFF;
      dataRow[0x0F] = hexF;// & 0xFF;

      for (int i = 0; i < BUFFER_SIZE; i++)
      {
        uint16_t addr = address + i;
        registerWriteData(addr);

        uint8_t data = dataRow[i];
        digitalWrite(D0, bitRead(data, 0));
        digitalWrite(D1, bitRead(data, 1));
        digitalWrite(D2, bitRead(data, 2));
        digitalWrite(D3, bitRead(data, 3));
        digitalWrite(D4, bitRead(data, 4));
        digitalWrite(D5, bitRead(data, 5));
        digitalWrite(D6, bitRead(data, 6));
        digitalWrite(D7, bitRead(data, 7));

        SetWriteMode(); 
        delay(50);
        SetDisableMode();
      }
    }
    dataFile.close();
    setLed(LED_READY | (error ? LED_ERROR: 0));
    if (error) Serial.println("\nError!");
    InitReadMode();    
  }
  else
  {
    setLed(LED_READY | LED_ERROR);
    Serial.println(F("Error open file: DUMP.TXT"));
  }
}


//////////////////////////////////////////
// Проверяем ППЗУ.
// Считываем данные из SD из файла DUMP.TXT и сравнимаем их с данными в ППЗУ
//////////////////////////////////////////
void ComapreMemoryMode()
{
  Serial.println(F("Start Compare"));
  File dataFile = SD.open("DUMP.TXT");
  if (dataFile)
  {
    bool error = false;
    setLed(LED_READ);
    while (!error)
    {
      int result;
      result = readLine(&dataFile, text, textLen);
      if (result == 0) break;
      Serial.println(text);
      int address, hex0, hex1, hex2, hex3, hex4, hex5, hex6, hex7, hex8, hex9, hexA, hexB, hexC, hexD, hexE, hexF;
      result = sscanf(text, "%04X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X", 
          &address, &hex0, &hex1, &hex2, &hex3, &hex4, &hex5, &hex6, &hex7, &hex8, &hex9, &hexA, &hexB, &hexC, &hexD, &hexE, &hexF);
      if (result != 17)
      {
        error = true;
        break;
      }
      dataRow[0x00] = hex0;// & 0xFF;
      dataRow[0x01] = hex1;// & 0xFF;
      dataRow[0x02] = hex2;// & 0xFF;
      dataRow[0x03] = hex3;// & 0xFF;
      dataRow[0x04] = hex4;// & 0xFF;
      dataRow[0x05] = hex5;// & 0xFF;
      dataRow[0x06] = hex6;// & 0xFF;
      dataRow[0x07] = hex7;// & 0xFF;
      dataRow[0x08] = hex8;// & 0xFF;
      dataRow[0x09] = hex9;// & 0xFF;
      dataRow[0x0A] = hexA;// & 0xFF;
      dataRow[0x0B] = hexB;// & 0xFF;
      dataRow[0x0C] = hexC;// & 0xFF;
      dataRow[0x0D] = hexD;// & 0xFF;
      dataRow[0x0E] = hexE;// & 0xFF;
      dataRow[0x0F] = hexF;// & 0xFF;

      for (int i = 0; i < BUFFER_SIZE; i++)
      {
        uint16_t addr = address + i;
        registerWriteData(addr);
        SetReadMode();
        delay(2);
        uint8_t data = ReadData();
        SetDisableMode();

        error = dataRow[i] != data;
        if (error) break;
      }
    }
    dataFile.close();
    setLed(LED_READY | (error ? LED_ERROR: 0));
    if (error) Serial.println("\nError!");
  }
  else
  {
    setLed(LED_READY | LED_ERROR);
    Serial.println(F("Error open file: DUMP.TXT"));
  }
}


//////////////////////////////////////////
// Запись в регистры (КР1533ИР24 x 2) адрес для ППЗУ.
//////////////////////////////////////////
void registerWriteData(uint16_t data)
{
  digitalWrite(C,  LOW);
  shiftOut(DR, C, MSBFIRST, highByte(data));
  digitalWrite(C,  LOW);
  shiftOut(DR, C, MSBFIRST, lowByte(data));
  delay(2);
}


//////////////////////////////////////////
// Читаем из файла строку.
//////////////////////////////////////////
int readLine(File* pFile, char* pText, int maxSize)
{
  maxSize --;
  int i = 0;
  while (i < maxSize)
  {
    char value = pFile->read();

    if (value == -1)     // Конец файла
    {
      break;
    }
    if (value == 13) //Конец строки = 13, 10
    {
      pFile->read(); // Вычитываем следом за символом 13 символ 10
      break;
    }
    pText[i++] = value;
  }
  pText[i] = 0;
  return i;
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


