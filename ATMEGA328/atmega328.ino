/*
http://codius.ru/articles/Arduino_UNO_4%D1%80%D0%B0%D0%B7%D1%80%D1%8F%D0%B4%D0%BD%D1%8B%D0%B9_7%D1%81%D0%B5%D0%B3%D0%BC%D0%B5%D0%BD%D1%82%D0%BD%D1%8B%D0%B9_%D0%B8%D0%B4%D0%B8%D0%BA%D0%B0%D1%82%D0%BE%D1%80_12_pin_3641BS_red
https://masterkit.ru/images/sets_scheme/nm7039box_sx.jpg
https://ecs7.tokopedia.net/img/product-1/2016/11/17/2550072/2550072_fa6ef4d0-76c7-4839-b123-9a678cd10d10.jpg
       
       4-разрядный 7-сегментный индикатор с общим анодом
            1  A  F   2  3  B
 ___________|__|__|___|__|__|____________
|         |         |         |         |
|    A    |    A    |    A    |    A    |
| F     B | F     B | F     B | F     B |
|    G    |    G    |    G    |    G    |
| E     C | E     C | E     C | E     C |
|    D    |    D    |    D    |    D    |
|_______dp|_______dp|_______dp|_______dp|
            |  |  |   |  |  |
            E  D dp   C  G  4

                     ------
      RESET - PC6 --| *    |-- PC5 -  SCL  - A5
 0 -   RXD  - PD0 --|      |-- PC4 -  SDA  - A4
 1 -   TXD  - PD1 --|      |-- PC3 -       - A3
 2 -        - PD2 --|      |-- PC2 -       - A2
 3 -        - PD3 --|      |-- PC1 -       - A1
 4 -        - PD4 --|      |-- PC0 -       - A0
   -   VCC  -     --|      |-- GND -  
   -   GND  -     --|      |-- AREF-  
   -  XTAL1 - PB6 --|      |-- VCC
   -  XTAL2 - PB7 --|      |-- PB5 -  SCK  - 13
 5 -        - PD5 --|      |-- PB4 - MISO  - 12
 6 -        - PD6 --|      |-- PB3 - MOSI  - 11
 7 -        - PD7 --|      |-- PB2 -  SS   - 10
 8 -        - PB0 --|      |-- PB1 -       - 9
                     ------
 
*/

const byte digits[10] =
{
  B10111111,    //dp G F E D C B A
  B00000110,    //dp G F E D C B A
  B11011011,    //dp G F E D C B A
  B01001111,    //dp G F E D C B A
  B11100110,    //dp G F E D C B A
  B01101101,    //dp G F E D C B A
  B11111101,    //dp G F E D C B A
  B00000111,    //dp G F E D C B A
  B11111111,    //dp G F E D C B A
  B01101111     //dp G F E D C B A
};

byte numbers[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2 };

byte timer = 0;
int cnt = 0;

const byte digitPin[] = { A0, A1, A2, A3 };
const int digitPinLength = sizeof(digitPin)/sizeof(digitPin[0]);

void setup()
{
  Serial.begin(9600);
  timer = 0;
  
  DDRB = B11111111;
  PORTB = B11111111;
  for (int i = 0; i < digitPinLength; i++)
  {
    pinMode(digitPin[i], OUTPUT);
    digitalWrite(digitPin[i], HIGH); // для S8550 HIGH = выключено, при прямом подключении LOW = выключено
  }
}

void showDigit(int index, byte value)
{
  for (int i = 0; i < digitPinLength; i++)
  {
    digitalWrite(digitPin[i], HIGH); // для S8550 HIGH = выключено, при прямом подключении LOW = выключено
  }
  PORTB = ~digits[value];
  digitalWrite(digitPin[index], LOW); // для S8550 LOW = включено, при прямом подключении HIGH = включено
  delay(5);
}

void loop() {
  showDigit(0, numbers[cnt + 0]);
  showDigit(1, numbers[cnt + 1]);
  showDigit(2, numbers[cnt + 2]);
  showDigit(3, numbers[cnt + 3]);

  timer++;
  if (timer > 16)
  {
    timer = 0;
    cnt ++;
  }

  if (cnt > 9)
  {
    cnt = 0;
  }
}

