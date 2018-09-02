/*
К573РФ2
http://www.inp.nsk.su/~kozak/mem/mem18.htm
http://www.eandc.ru/pdf/mikroskhema/k573rf2.pdf
http://vip-cxema.org/index.php/home/mikrokontrollery/357-prostoj-kopirovshchik-rpzu-k573rf2-5

Распиновка платы
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
#define ADDR0   2
#define ADDR1   3
#define ADDR2   4
#define ADDR3   5
#define ADDR4   6
#define ADDR5   7
#define ADDR6   8
#define ADDR7   9
#define ADDR8   10
#define ADDR9   11
#define ADDR10  X

#define D0  A0
#define D1  A1
#define D2  A2
#define D3  A3
#define D4  A4
#define D5  A5
#define D6  12
#define D7  13

void  setup ( )
{
  Serial.begin(9600);     // Status message will be sent to PC at 9600 baud
  pinMode(ADDR0, OUTPUT);
  pinMode(ADDR1, OUTPUT);
  pinMode(ADDR2, OUTPUT);
  pinMode(ADDR3, OUTPUT);
  pinMode(ADDR4, OUTPUT);
  pinMode(ADDR5, OUTPUT);
  pinMode(ADDR6, OUTPUT);
  pinMode(ADDR7, OUTPUT);
  pinMode(ADDR8, OUTPUT);
  pinMode(ADDR9, OUTPUT);
  
  pinMode(D0, INPUT_PULLUP);
  pinMode(D1, INPUT_PULLUP);
  pinMode(D2, INPUT_PULLUP);
  pinMode(D3, INPUT_PULLUP);
  pinMode(D4, INPUT_PULLUP);
  pinMode(D5, INPUT_PULLUP);
  pinMode(D6, INPUT_PULLUP);
  pinMode(D7, INPUT_PULLUP);
}

void  loop ( )
{
  char text[32];
  short addr = 0;

  // Читаем только 1 кБ, так как на 2кБ нехватает выходов
  for (int n = 0; n < 64; n++)
  {
    sprintf(text, "%04X ", addr);
    Serial.print(text);
    for (int i = 0; i < 16; i++)
    {
      byte data = 0;
      digitalWrite(ADDR9, bitRead(addr, 9));
      digitalWrite(ADDR8, bitRead(addr, 8));
      digitalWrite(ADDR7, bitRead(addr, 7));
      digitalWrite(ADDR6, bitRead(addr, 6));
      digitalWrite(ADDR5, bitRead(addr, 5));
      digitalWrite(ADDR4, bitRead(addr, 4));
      digitalWrite(ADDR3, bitRead(addr, 3));
      digitalWrite(ADDR2, bitRead(addr, 2));
      digitalWrite(ADDR1, bitRead(addr, 1));
      digitalWrite(ADDR0, bitRead(addr, 0));
      delay(5);
      if (digitalRead(D0) == HIGH) bitSet(data, 0);
      if (digitalRead(D1) == HIGH) bitSet(data, 1);
      if (digitalRead(D2) == HIGH) bitSet(data, 2);
      if (digitalRead(D3) == HIGH) bitSet(data, 3);
      if (digitalRead(D4) == HIGH) bitSet(data, 4);
      if (digitalRead(D5) == HIGH) bitSet(data, 5);
      if (digitalRead(D6) == HIGH) bitSet(data, 6);
      if (digitalRead(D7) == HIGH) bitSet(data, 7);
      sprintf(text, " %02X", data);
      Serial.print(text);
      addr++;
    }
    Serial.println("");
  }
  delay(10000);
  Serial.println("");
  Serial.println("");
  Serial.println("");
  Serial.println("");
}
