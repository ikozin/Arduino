/*
RAM:   [==        ]  21.0% (used 430 bytes from 2048 bytes)
Flash: [==        ]  20.2% (used 6204 bytes from 30720 bytes)

RAM:   [==        ]  21.0% (used 430 bytes from 2048 bytes)
Flash: [==        ]  19.8% (used 6086 bytes from 30720 bytes)
*/

/*
Arduino Pro Mini
 -----------------------
| *   *   *   *   *   * |
|GND CTS VCC RXI TXD DTR|
 -----------------------

I2C
MP1090S_ADDRESS     0x10
MCP23008_ADDRESS    0x20
DS3231              0x68


AUDIO 
1 - GND
2 - LEFT
3 - MIC
4 - RIGHT

MP1090S
         ___ ___
 SDA SCL SEN RST
 ---------------------------------------
| X | X | X | X |   |   |   |   |   |   |
 ---------------------------------------

 VCC GND RGT GNF LFT
 --------------------
| X | X | X | X | X |
 -------------------
*/
#include <Arduino.h>
#include <Wire.h>
#include <MP1090S.h>

const int radio_RST = 8;
const int radio_SEN = 9;

typedef struct _radioItem {
	long wave;
	char name[21];
} RadioItem;

// Важно: русские буквы, видимо в unicode, так как массив с ними переполнен, да и вывод их не совпадает (кодировка)
const RadioItem radioList[] PROGMEM = {
  { 87500, "Business FM     87,5"},                                       // 0 - Business FM
  { 87900, "Like FM         87,9"},                                       // 1 - Like FM
  { 88300, "Pe\xBFpo FM        88,3"},                                    // 2 - Ретро FM
  { 88700, "\xB0\xBCop FM         88,7"},                                 // 3 - Юмор FM
  { 89100, "Pa\xE3\xB8o Jazz      89,1"},                                 // 4 - Радио Jazz
  { 89500, "Ka\xBB\xB8\xBD""a Kpac\xBD""a\xC7  89,5"},                    // 5 - Радио Калина Красная
  { 89900, "Pa\xE3\xB8o Pe\xBAop\xE3    89,9"},                           // 6 - Радио Рекорд
  { 90300, "A\xB3\xBFopa\xE3\xB8o       90,3"},                           // 7 - Авторадио
  { 90800, "Relax FM        90,8"},                                       // 8 - Relax FM
  { 91200, "Pa\xE3\xB8o Sputnik   91,2"},                                 // 9 - Радио Sputnik
  { 91600, "Pa\xE3\xB8o Ky\xBB\xC4\xBFypa  91,6"},                        //10 - Радио Культура
  { 92000, "Moc\xBA\xB3""a FM       92,0"},                               //11 - Москва FM
  { 92400, "Pa\xE3\xB8o \xE0""a\xC0""a      92,4"},                       //12 - Радио Дача
  { 92800, "Pa\xE3\xB8o Kap\xBD""a\xB3""a\xBB  92,8"},                    //13 - Радио Карнавал
  { 93200, "STUDIO 21       93,2"},                                       //14 - STUDIO 21
  { 93600, "Ko\xBC\xBC""epca\xBD\xBF\xC2 FM  93,6"},                      //15 - Коммерсант FM
  { 94000, "Boc\xBFo\xBA FM       94,0"},                                 //16 - Восток FM
  { 94400, "C\xBEop\xBF\xB8\xB3\xBDoe Pa\xE3\xB8o94,4"},                  //17 - Первое Спортивное Радио
  { 94800, "\xA1o\xB3op\xB8\xBF Moc\xBA\xB3""a  94,8"},                   //18 - Говорит Москва
  { 95200, "Rock FM         95,2"},                                       //19 - Rock FM
  { 95600, "Pa\xE3\xB8o \xA4\xB3""e\xB7\xE3""a    95,6"},                 //20 - Радио Звезда
  { 96000, "\xE0opo\xB6\xBDoe pa\xE3\xB8o  96,0"},                        //21 - Дорожное радио
  { 96400, "Ta\xBA""c\xB8 FM        96,4"},                               //22 - Такси FM
  { 96800, "\xE0""e\xBF""c\xBAoe pa\xE3\xB8o   96,8"},                    //23 - Детское радио
  { 97200, "Pa\xE3\xB8o K\xA8        97,2"},                              //24 - Радио КП
  { 97600, "Bec\xBF\xB8 FM        97,6"},                                 //25 - Вести FM
  { 98000, "Pa\xE3\xB8o \xACo\xBAo\xBB""a\xE3   98,0"},                   //26 - Радио Шоколад
  { 98400, "Ho\xB3oe Pa\xE3\xB8o     98,4"},                              //27 - Новое Радио
  { 98800, "Pa\xE3\xB8o Romantika 98,8"},                                 //28 - Радио Romantika
  { 99200, "Pa\xE3\xB8o Op\xAA""e\xB9     99,2"},                         //29 - Радио Орфей
  { 99600, "Pycc\xB8\xA6 X\xB8\xBF      99,6"},                           //30 - Радио Русский Хит
  {100100, "Cepe\xB2p\xC7\xBD\xC3\xB9 \xE3o\xB6\xE3\xC4    "},            //31 - Серебряннй дождь
  {100500, "\xA3""apa FM        100,5"},                                  //32 - Жара FM
  {101200, "DFM            101,2"},                                       //33 - DFM
  {101800, "Ha\xC1""e pa\xE3\xB8o     101,7"},                            //34 - Наше Радио
  {102100, "Mo\xBD\xBF""e-Kap\xBBo    102,1"},                            //35 - Монте-Карло
  {102500, "Comedy Radio   102,5"},                                       //36 - Comedy Radio
  {103000, "\xAC""a\xBD""co\xBD         103,0"},                          //37 - Шансон
  {103400, "Ma\xC7\xBA           103,4"},                                 //38 - Маяк
  {103700, "Maximum        103,7"},                                       //39 - Maximum
  {104200, "Pa\xE3\xB8o ENERGY   104,2"},                                 //40 - Радио ENERGY
  {104700, "Pa\xE3\xB8o 7        104,7"},                                 //41 - Радио 7
  {105000, "Pa\xE3\xB8o \xA1op\xE3oc\xBF\xC4 105,2"},                     //42 - Радио Гордость
  {105300, "Capital FM     105,2"},                                       //43 - Capital FM
  {105700, "Pycc\xBAoe pa\xE3\xB8o  105,7"},                              //44 - Русское радио
  {106200, "E\xB3po\xBE""a \xA8\xBB\xC6""c    106,2"},                    //45 - Европа Плюс
  {106600, "Love Radio     106,6"},                                       //46 - Love Radio
  {107000, "KIS FM         107,0"},                                       //47 - KISS FM
  {107400, "X\xB8\xBF FM         107,4"},                                 //48 - Хит FM
  {107800, "M\xB8\xBB\xB8\xE5""e\xB9""c\xBA""a\xC7 \xB3o\xBB\xBD""a   "}, //49 - Милицейская волна
};
const int listSize = sizeof(radioList) / sizeof(RadioItem);

int index = 0;

void setup() {
    Serial.begin(115200);

    Wire.begin();
    Wire.setClock(400000);

    Serial.println(F("Initialize Radio"));
    MP1090S::InitI2C(radio_RST, radio_SEN);
    MP1090S::SetBand(MHz87_5_108);
    uint8_t *p_item = (uint8_t *)(radioList + 34);
    long wave = (long)pgm_read_dword_near(p_item);
    MP1090S::SetStation(wave);
    MP1090S::SetVolume(8);
}

void loop() {
    delay(3000);

    if (index >= listSize) index = 0;

    uint8_t *p_item = (uint8_t *)(radioList + index);
    long wave = (long)pgm_read_dword_near(p_item);
    MP1090S::SetStation(wave);
    MP1090S::SetVolume(10);
    index++;
}
