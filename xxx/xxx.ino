/*
//https://arduinoplus.ru/wp-content/uploads/2018/02/mega-1.jpg

К573РФ2
http://www.inp.nsk.su/~kozak/mem/mem18.htm
http://www.eandc.ru/pdf/mikroskhema/k573rf2.pdf
http://vip-cxema.org/index.php/home/mikrokontrollery/357-prostoj-kopirovshchik-rpzu-k573rf2-5

Распиновка платы К573РФ2

                     ключ
                      ^
                  CE OE
                   |  |
              ------------------------
       A10 --|                        |
       A9  --|                        |
       A8  --|                        |
       A7  --|                        |
       A6  --|                        |-- GND   
       A5  --|                        |-- VCC  < ключ
       A4  --|                        |
       A3  --|                        |
       A2  --|                        |
       A1  --|                        |
ключ > A0  --|                        |
              ------------------------
               |  |  |   |   |   |  |
              D0 D1 D2 D3 D4 D5 D6 D7
               ^
              ключ

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

Распиновка К573РФ2
      -------------
  1 -| A7      +5V |- 24
  2 -| A6       A8 |- 23
  3 -| A5       A9 |- 22
  4 -| A4      Vpp |- 21
  5 -| A3      ~OE |- 20
  6 -| A2      A10 |- 19
  7 -| A1      ~CE |- 18
  8 -| A0       D7 |- 17
  9 -| D0       D6 |- 16
 10 -| D1       D5 |- 15
 11 -| D2       D4 |- 14
 12 -| GND      D3 |- 13
      -------------

*/
#ifndef __AVR_ATmega2560__
#error "Select board ATMEG2560"
#endif

#include <SPI.h>
#include <SD.h>

#define MAX_SIZE   (2048)
/*
#define ADDR0      (22)   //PA0
#define ADDR1      (23)   //PA1
#define ADDR2      (24)   //PA2
#define ADDR3      (25)   //PA3
#define ADDR4      (26)   //PA4
#define ADDR5      (27)   //PA5
#define ADDR6      (28)   //PA6
#define ADDR7      (29)   //PA7
#define ADDR8      (37)   //PC0
#define ADDR9      (36)   //PC1
#define ADDR10     (35)   //PC2
#define ADDR11     (34)   //PC3
#define ADDR12     (33)   //PC4
#define ADDR13     (33)   //PC5
#define ADDR14     (31)   //PC6
#define ADDR15     (30)   //PC7

#define D0         (49)   //PL0
#define D1         (48)   //PL1
#define D2         (47)   //PL2
#define D3         (46)   //PL3
#define D4         (45)   //PL4
#define D5         (44)   //PL5
#define D6         (43)   //PL6
#define D7         (42)   //PL7
*/
#define CE         (40)   //PG1
#define OE         (41)   //PG0

#define SD_CS      (53)

#define BUFFER_SIZE   16
uint8_t dataRow[BUFFER_SIZE];
#define textLen       64
char text[textLen];

void setup()
{
  // Адрес,  контакты 22-39, порты A и C
  DDRA =  B11111111;
  DDRC =  B11111111;
  // Данные, контакты 42-49, порт L
  DDRL  = B00000000;

  // К573РФ2
  pinMode(CE, OUTPUT);
  pinMode(OE, OUTPUT);
  SetDisableMode();
  InitReadMode();

  // Serial
  Serial.begin(9600);
  while (!Serial) {}
  Serial.println(F("Start"));

  // SD
  if (!SD.begin(SD_CS))
  {
    Serial.println(F("Initialization failed!"));
    for (;;);
  }
  Serial.println(F("SD card initialized."));

  showMenu();  
}

void showMenu()
{
    Serial.println();
    Serial.println(F("K573RF2"));
    Serial.println(F("Reset Arduino after insert SD card"));
    Serial.println(F("Enter commnad:"));
    Serial.println();
    Serial.println(F("1 - Check   2048 KB (CHECK.TXT)"));
    Serial.println(F("3 - Read    2048 KB (DUMP.TXT)"));
    Serial.println(F("5 - Compare 2048 KB (DUMP.TXT)"));
    Serial.println(F("7 - Write   2048 KB (DUMP.TXT)"));
    Serial.println();
}

void loop()
{
  int cmd = Serial.read();
  switch (cmd)
  {
    case '1':
      CheckMemoryMode();
      showMenu();  
      break;
    case '3':
      ReadMemoryMode();
      showMenu();  
      break;
    case '5':
      ComapreMemoryMode();
      showMenu();  
      break;
    case '7':
      WriteMemoryMode();
      showMenu();  
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
  DDRL  = B00000000;
}

//////////////////////////////////////////
// Данные для записи
//////////////////////////////////////////
void InitWriteMode()
{
  DDRL =  B11111111;
}

//////////////////////////////////////////
// Читаем данные
//////////////////////////////////////////
uint8_t ReadData()
{
  return PORTL;
}

//////////////////////////////////////////
// Записваем данные
//////////////////////////////////////////
void WriteData(uint8_t data)
{
  PORTL = data;
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
    for (uint16_t address = 0; address < MAX_SIZE; address++)
    {
      SetAddress(address);
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
    if (error) Serial.println("\nError!");
  }
  else
  {
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
    for (uint16_t address = 0; address < MAX_SIZE; address += BUFFER_SIZE)
    {
      bin2hex(text, address);
      dataFile.print(text);
      Serial.print(text);

      for (int i = 0; i < BUFFER_SIZE; i++)
      {
        uint16_t addr = address + i;
        SetAddress(addr);
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
  }
  else
  {
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
        SetAddress(addr);
        WriteData(dataRow[i]);
        delay(2);
        SetWriteMode(); 
        delay(50);
        SetDisableMode();
      }
    }
    dataFile.close();
    if (error) Serial.println("\nError!");
    InitReadMode();    
  }
  else
  {
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
        SetAddress(addr);
        SetReadMode();
        delay(2);
        uint8_t data = ReadData();
        SetDisableMode();
        error = dataRow[i] != data;
        if (error) break;
      }
    }
    dataFile.close();
    if (error) Serial.println("\nError!");
  }
  else
  {
    Serial.println(F("Error open file: DUMP.TXT"));
  }
}

//////////////////////////////////////////
// Адрес для ППЗУ.
//////////////////////////////////////////
void SetAddress(uint16_t data)
{
  PORTA = lowByte(data);
  PORTC = highByte(data);
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
