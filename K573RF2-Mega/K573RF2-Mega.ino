/*
К573РФ2
http://www.inp.nsk.su/~kozak/mem/mem18.htm
http://www.eandc.ru/pdf/mikroskhema/k573rf2.pdf
http://vip-cxema.org/index.php/home/mikrokontrollery/357-prostoj-kopirovshchik-rpzu-k573rf2-5

Распиновка платы К573РФ2

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

#define ADDR0      (22)		//PA0
#define ADDR1      (23)		//PA1
#define ADDR2      (24)		//PA2
#define ADDR3      (25)		//PA3
#define ADDR4      (26)		//PA4
#define ADDR5      (27)		//PA5
#define ADDR6      (28)		//PA6
#define ADDR7      (29)		//PA7
#define ADDR8      (37)     //PC0
#define ADDR9      (36)     //PC1
#define ADDR10     (35)     //PC2
//#define ADDR11     (34)     //PC3
//#define ADDR12     (33)     //PC4
//#define ADDR13     (33)     //PC5
//#define ADDR14     (31)     //PC6
//#define ADDR15     (30)     //PC7

#define D0         (49)     //PL0
#define D1         (48)     //PL1
#define D2         (47)     //PL2
#define D3         (46)     //PL3
#define D4         (45)     //PL4
#define D5         (44)     //PL5
#define D6         (43)     //PL6
#define D7         (42)     //PL7

#define CE         (40)     //PL0
#define OE         (41)     //PL1


void  setup ( )
{
  Serial.begin(9600);

  DDRA  = B11111111;
  DDRC  = B11111111;

  DDRL  = B00000000;

  // К573РФ2
  pinMode(CE, OUTPUT);
  pinMode(OE, OUTPUT);
  SetDisableMode();
  InitReadMode();
}

void  loop ( )
{
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
	PORTL = B11111111;
}

//////////////////////////////////////////
// Данные для записи
//////////////////////////////////////////
void InitWriteMode()
{
	DDRL  = B11111111;
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
