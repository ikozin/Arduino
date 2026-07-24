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


           ┌──────────┬─────────────┬──────────┐
          ─┤ PD1 (D1) │ Arduino Pro │   RAW    ├─
           ├──────────┤     Mini    ├──────────┤
          ─┤ PD0 (D0) │             │   GND    ├─
           ├──────────┤             ├──────────┤
          ─┤  RESET   │             │  RESET   ├─
           ├──────────┤             ├──────────┤
          ─┤   GND    │             │   VCC    ├─
           ├──────────┤             ├──────────┤
          ─┤ PD2 (D2) │             │ PC3 (A3) ├─
           ├──────────┤             ├──────────┤
          ─┤ PD3 (D3) │             │ PC2 (A2) ├─   BUZZER
           ├──────────┤             ├──────────┤
          ─┤ PD4 (D4) │             │ PC1 (A1) ├─   (~RST~) MP1090S
           ├──────────┤             ├──────────┤
          ─┤ PD5 (D5) │             │ PC0 (A0) ├─   (~SEN~) MP1090S
           ├──────────┤             ├──────────┤
          ─┤ PD6 (D6) │             │ PB5 (D13)├─
           ├──────────┤             ├──────────┤
          ─┤ PD7 (D7) │             │ PB4 (D12)├─   TTP223
           ├──────────┤             ├──────────┤
 TTP223   ─┤ PB0 (D8) │             │ PB3 (D11)├─   TTP223
           ├──────────┤             ├──────────┤
 TTP223   ─┤ PB1 (D9) │             │ PB2 (D10)├─   TTP223
           └──────────┴─────────────┴──────────┘

  

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

 http://robotosha.ru/wp-content/uploads/2015/03/hd44780_char_table.png
    | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | A | B | C | D | E | F |
| 0 |   |   |   | 0 | @ | P | ` | p |   |   | Б | Ю | ч |   | Д |   |
| 1 |   |   | ! | 1 | A | Q | a | q |   |   | Г | Я | ш |   | Ц |   |
| 2 |   |   | " | 2 | B | R | b | r |   |   | Ё | б | ъ |   | Щ |   |
| 3 |   |   | # | 3 | C | S | c | s |   |   | Ж | в | ы |   | д |   |
| 4 |   |   | $ | 4 | D | T | d | t |   |   | З | г | ь |   | ф |   |
| 5 |   |   | % | 5 | E | U | e | u |   |   | И | ё | э |   | ц |   |
| 6 |   |   | & | 6 | F | V | f | v |   |   | Й | ж | ю |   | щ |   |
| 7 |   |   | ' | 7 | G | W | g | w |   |   | Л | з | я |   |   |   |
| 8 |   |   | ( | 8 | H | X | h | x |   |   | П | и |   |   |   |   |
| 9 |   |   | ) | 9 | I | Y | i | y |   |   | У | й |   |   |   |   |
| A |   |   | * | : | J | Z | j | z |   |   | Ф | к |   |   |   |   |
| B |   |   | + | ; | K | [ | k |   |   |   | Ч | л |   |   |   |   |
| C |   |   | , | < | L |   | l |   |   |   | Ш | м |   |   |   |   |
| D |   |   | - | = | M | ] | m |   |   |   | Ъ | н |   |   |   |   |
| E |   |   | . | > | N | ^ | n |   |   |   | Ы | п |   |   |   |   |
| F |   |   | / | ? | O | _ | o |   |   |   | Э | т |   |   |   |   |


https://microsin.net/adminstuff/hardware/ds3231-extremely-accurate-rtc.html
*/

#include <Arduino.h>
#include "Radio.h"
#include "Storage.h"
#include "StringN.h"
#include "GyverIO.h"
#include "GyverMenu.h"
#include "RTClib.h"

#ifndef ARDUINO_AVR_PRO
#error Select board: Arduino Pro Mini 
#endif

unsigned long lasttime = 0; // время последнего срабатывания прерывания, для исключения дребезга и мнгновенного срабатывания несколько раз.

LiquidCrystal_I2C lcd(0);
GyverMenu menu(lcdRows, lcdLines);
//GyverDS3231Min  rtc;
RTC_DS3231 rtc;
Storage storage; 

String24 text; 
volatile uint8_t mode  = MODE_CLOCK;

const byte _L1[8] = { B00000, B00000, B00000, B00000, B00000, B11111, B11111, B11111 };
const byte _L2[8] = { B11111, B11111, B11111, B00000, B00000, B00000, B00000, B00000 };
const byte _L3[8] = { B11111, B11111, B11111, B00000, B00000, B00000, B11111, B11111 };
const byte _B1[8] = { B00111, B01111, B11111, B11111, B11111, B11111, B11111, B11111 };
const byte _B2[8] = { B11100, B11110, B11111, B11111, B11111, B11111, B11111, B11111 };
const byte _B3[8] = { B11111, B11111, B11111, B11111, B11111, B11111, B01111, B00111 };
const byte _B4[8] = { B11111, B11111, B11111, B11111, B11111, B11111, B11110, B11100 };

const char digit_0_top[] = "\x04""\x02""\x05 ";
const char digit_1_top[] = "\x02""\x05""\x20 ";
const char digit_2_top[] = "\x02""\x03""\x05 ";
const char digit_3_top[] = "\x02""\x03""\x07 ";
const char digit_4_top[] = "\x04""\x01""\xFF ";
const char digit_5_top[] = "\x06""\x03""\x02 ";
const char digit_6_top[] = "\x04""\x03""\x02 ";
const char digit_7_top[] = "\x02""\x02""\x05 ";
const char digit_8_top[] = "\x06""\x03""\x07 ";
const char digit_9_top[] = "\x06""\x03""\x05 ";

const char *const digits_top[] = {
    digit_0_top,
    digit_1_top,
    digit_2_top,
    digit_3_top,
    digit_4_top,
    digit_5_top,
    digit_6_top,
    digit_7_top,
    digit_8_top,
    digit_9_top,
};

const char digit_0_bottom[] = "\x06""\x01""\x07 ";
const char digit_1_bottom[] = "\x01""\xFF""\x01 ";
const char digit_2_bottom[] = "\x04""\x03""\x01 ";
const char digit_3_bottom[] = "\x01""\x03""\x05 ";
const char digit_4_bottom[] = "\x20""\x20""\xFF ";
const char digit_5_bottom[] = "\x01""\x03""\x05 ";
const char digit_6_bottom[] = "\x06""\x03""\x05 ";
const char digit_7_bottom[] = "\x20""\x20""\xFF ";
const char digit_8_bottom[] = "\x04""\x03""\x05 ";
const char digit_9_bottom[] = "\x01""\x03""\x07 ";

const char *const digits_bottom[] = {
    digit_0_bottom,
    digit_1_bottom,
    digit_2_bottom,
    digit_3_bottom,
    digit_4_bottom,
    digit_5_bottom,
    digit_6_bottom,
    digit_7_bottom,
    digit_8_bottom,
    digit_9_bottom,
};

const char months[12][9] = {
  "\xC7\xBD\xB3""ap\xC4",
  "\xE4""e\xB3pa\xBB\xC4",
  "\xBC""ap\xBF",
  "a\xBEpe\xBB\xC4",
  "\xBC""a\xB9",
  "\xB8\xC6\xBD\xC4",
  "\xB8\xC6\xBB\xC4",
  "a\xB3\xB4yc\xBF",
  "ce\xBD\xBF\xC7\xB2p\xC4",
  "o\xBA\xBF\xC7\xB2p\xC4",
  "\xBDo\xC7\xB2p\xC4",
  "\xE3""e\xBA""a\xB2p\xC4",
};

typedef struct {
    uint16_t year;
    uint8_t month;
    uint8_t day;
    uint8_t hour;
    uint8_t minute;
    uint8_t second;
} DEVICE_DATE_TIME;
DEVICE_DATE_TIME setting = { .year = 2026, .month = 1, .day = 1, .hour = 0, .minute = 0, .second = 0 };

typedef struct {
    bool state;
    bool Monday;
    bool Tuesday;
    bool Wednesday;
    bool Thursday;
    bool Friday;
    bool Saturday;
    bool Sunday;
    uint8_t mode;
    uint8_t hour;
    uint8_t minute;
    uint8_t volume;
    uint8_t radio;
} DEVICE_SETTING_ALARM;
#define ALARM_SIZE  (6)
DEVICE_SETTING_ALARM    alarm[ALARM_SIZE] = {{
        .state = true,
        .Monday = true, .Tuesday = true, .Wednesday = true, .Thursday = true, .Friday = true, .Saturday = true, .Sunday = true,
        .mode = 0, .hour = 23, .minute = 0, .volume = 0, .radio = 0,
    }, {
        .state = true,
        .Monday = true, .Tuesday = true, .Wednesday = true, .Thursday = true, .Friday = true, .Saturday = false, .Sunday = false,
        .mode = 1, .hour = 8, .minute = 0, .volume = 4, .radio = 30    
    }, {
        .state = true,
        .Monday = false, .Tuesday = false, .Wednesday = false, .Thursday = false, .Friday = false, .Saturday = true, .Sunday = true,
        .mode = 1, .hour = 10, .minute = 0, .volume = 4, .radio = 30    
    }
};

DEVICE_SETTING_ALARM* alarm1 = &alarm[0];
DEVICE_SETTING_ALARM* alarm2 = &alarm[1];
DEVICE_SETTING_ALARM* alarm3 = &alarm[2];
DEVICE_SETTING_ALARM* alarm4 = &alarm[3];
DEVICE_SETTING_ALARM* alarm5 = &alarm[4];
DEVICE_SETTING_ALARM* alarm6 = &alarm[5];

typedef struct {
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

AlarmItem *pCurrentAlarm = NULL;

const char *playList[] = {
    song01,
    song02,
    song03,
    song04,
    song05,
    song06,
    song07,
    song08,
    song09,
    song10,
    song11,
    song12,
    song13,
    song14,
    song15,
    song16,
    song18,
    song19,
    song20,
    song21,
    song22,
    song23,
    song24,
};
const int playListSize = sizeof(playList) / sizeof(char*);

#define ButtonControl   (values[0])
#define ButtonUp        (values[1])
#define ButtonDown      (values[2])
#define ButtonLeft      (values[3])
#define ButtonRight     (values[4])
volatile uint8_t values[5] = { 0, 0, 0, 0, 0 };
uint8_t oldPINB = 0xFF;
// Обработчик запросов прерывания от пинов D8..D13
ISR (PCINT0_vect) {
    uint8_t value = PINB;
    uint8_t changedbits = value ^ oldPINB;
    oldPINB = value;

    if (changedbits & bit(PB0)) { // Изменился D8
        values[PB0] = value & bit(PB0);
    }

    if (changedbits & bit(PB1)) { // Изменился D9
        values[PB1] = value & bit(PB1);
    }

    if (changedbits & bit(PB2)) { // Изменился D10
        values[PB2] = value & bit(PB2);
    }

    if (changedbits & bit(PB3)) { // Изменился D11
        values[PB3] = value & bit(PB3);
    }

    if (changedbits & bit(PB4)) { // Изменился D12
        values[PB4] = value & bit(PB4);
    }
}

#define UPDATE_TIME_PERIOD  (60)
volatile uint8_t    updatetime = UPDATE_TIME_PERIOD;
// Обработчик прерывания на D2
void isr_time() { updatetime ++; }

void error(const char *text) {
    Serial.println(text);
    lcd.clear();
    lcd.home();
    lcd.print(text);
    for (;;);
}

void displayDate(uint8_t day, uint8_t month, uint16_t year) {
    text = "  ";
    text += day;
    text += ' ';
    text += months[month - 1];
    text += ' ';
    text += year;
    text += "  ";
    lcd.setCursor((lcdRows - text.length()) >> 1, 0);
    lcd.print(text);
}

void displayTime(uint8_t hour, uint8_t minute) {
    uint8_t cnt;

    cnt = 0;
    while (hour >= 10) {
        cnt += 1;
        hour -= 10;
    }
    lcd.setCursor(2, 2);
    lcd.print(digits_top[cnt]);
    lcd.print(digits_top[hour]);
    lcd.setCursor(2, 3);
    lcd.print(digits_bottom[cnt]);
    lcd.print(digits_bottom[hour]);

    cnt = 0;
    while (minute >= 10) {
        cnt += 1;
        minute -= 10;
    }    
    lcd.setCursor(10, 2);
    lcd.print(digits_top[cnt]);
    lcd.print(digits_top[minute]);
    lcd.setCursor(10, 3);
    lcd.print(digits_bottom[cnt]);
    lcd.print(digits_bottom[minute]);
}

// void dumpInfoAlarm(const AlarmItem *pAlarmData) {
//     text.clear();
//     text.add(pAlarmData->week, 16);
//     text.add(" ,");
//     if (pAlarmData->hour < 10) text.add('0');
//     text.add(pAlarmData->hour);
//     text.add(":");
//     if (pAlarmData->minute < 10) text.add('0');
//     text.add(pAlarmData->minute);
//     text.add(":");
//     if (pAlarmData->second < 10) text.add('0');
//     text.add(pAlarmData->second);
//     Serial.println(text);
// }

// void dumpInfo() {
//     Serial.print(F("index = "));
//     Serial.println(storage.GetIndex());
//     Serial.print(F("volume = "));
//     Serial.println(storage.GetVolume());
//     Serial.print(F("corrSec = "));
//     Serial.println(storage.GetCorrSec());
//     Serial.print(F("currentPlay = "));
//     Serial.println(storage.GetCurrentPlay());
//     for (int i = 0; i < storage.GetAlarmOnSize(); i++) dumpInfoAlarm(storage.GetAlarmOn(i));
//     for (int i = 0; i < storage.GetAlarmOffSize(); i++) dumpInfoAlarm(storage.GetAlarmOff(i));
// }

void play_rtttl(const char *song) {
    char *ptr = (char *)song;
    byte default_dur = 4;
    byte default_oct = 6;
    int bpm = 63;
    int num;
    long wholenote;
    long duration;
    byte note;
    byte scale;

    // format: d=N,o=N,b=NNN:
    // find the start (skip name, etc)

    while (pgm_read_byte_near(ptr) != ':') ptr++;   // ignore name
    ptr++;                     // skip ':'

    // get default duration
    if (pgm_read_byte_near(ptr) == 'd') {
        ptr++; ptr++;              // skip "d="
        num = 0;
        while (isdigit(pgm_read_byte_near(ptr))) {
            num = (num * 10) + (pgm_read_byte_near(ptr++) - '0');
        }
        if (num > 0) default_dur = num;
        ptr++;                   // skip comma
    }

    // get default octave
    if (pgm_read_byte_near(ptr) == 'o') {
        ptr++; ptr++;              // skip "o="
        num = pgm_read_byte_near(ptr++) - '0';
        if (num >= 3 && num <= 7) default_oct = num;
        ptr++;                   // skip comma
    }

    // get BPM
    if (pgm_read_byte_near(ptr) == 'b') {
        ptr++; ptr++;              // skip "b="
        num = 0;
        while (isdigit(pgm_read_byte_near(ptr))) {
            num = (num * 10) + (pgm_read_byte_near(ptr++) - '0');
        }
        bpm = num;
        ptr++;                   // skip colon
    }

    // BPM usually expresses the number of quarter notes per minute
    wholenote = (60 * 1000L / bpm) * 4;  // this is the time for whole note (in milliseconds)

    // now begin note loop
    while (mode == MODE_ALARM && pgm_read_byte_near(ptr)) {
        // first, get note duration, if available
        num = 0;
        while (isdigit(pgm_read_byte_near(ptr))) {
            num = (num * 10) + (pgm_read_byte_near(ptr++) - '0');
        }

        if (num) duration = wholenote / num;
        else duration = wholenote / default_dur;  // we will need to check if we are a dotted note after

        // now get the note
        note = 0;

        switch (pgm_read_byte_near(ptr)) {
            case 'c':
                note = 1;
                break;
            case 'd':
                note = 3;
                break;
            case 'e':
                note = 5;
                break;
            case 'f':
                note = 6;
                break;
            case 'g':
                note = 8;
                break;
            case 'a':
                note = 10;
                break;
            case 'b':
                note = 12;
                break;
            case 'p':
            default:
                note = 0;
        }
        ptr++;

        // now, get optional '#' sharp
        if (pgm_read_byte_near(ptr) == '#') {
            note++;
            ptr++;
        }

        // now, get optional '.' dotted note
        if (pgm_read_byte_near(ptr) == '.') {
            duration += duration / 2;
            ptr++;
        }

        // now, get scale
        if (isdigit(pgm_read_byte_near(ptr))) {
            scale = pgm_read_byte_near(ptr) - '0';
            ptr++;
        }
        else {
            scale = default_oct;
        }

        scale += OCTAVE_OFFSET;

        if (pgm_read_byte_near(ptr) == ',')
            ptr++;       // skip comma for next note (or we may be at the end)

        // now play the note

        if (note) {
            tone(TONE_PIN, notes[(scale - 4) * 12 + note]);
            delay(duration);
            noTone(TONE_PIN);
        }
        else {
            delay(duration);
        }
    }
}

void switchmode() {
    noInterrupts();
    unsigned long t = millis();
    if (t - lasttime > 500) {
        switch (mode) {
            case MODE_CLOCK:
                mode = MODE_RADIO;
                break;
            case MODE_ALARM:
                mode = MODE_CLOCK;
                break;
            case MODE_RADIO:
                mode = MODE_SETTING;
                break;
            case MODE_SETTING:
                mode = MODE_CLOCK;
                    break;
            default:
                error("MODE ERROR");
        }
        lasttime = t;
    }
    interrupts();
}

bool checkAlarmTime(AlarmItem *pAlarmData, DateTime now, int dayOfWeek) {
    if (pAlarmData->week & (1 << dayOfWeek)) {
        if (now.hour() == pAlarmData->hour 
            && now.minute() == pAlarmData->minute
            && now.second() == pAlarmData->second) {
            return true;
        }
    }
    return false;
}

void showRadioVolume() {
    if (mode == MODE_RADIO) {
        int i;
        lcd.setCursor(5, 3);
        for (i = 0; i < storage.GetVolume(); i++) {
            lcd.print("\xFF");
        }
        for (; i < 15; i++) {
            lcd.print(" ");
        }
    }
    MP1090S::SetVolume(storage.GetVolume());
}

void showRadioStation() {
    storage.SetIndex(constrain(storage.GetIndex(), 0, listSize - 1));
    uint8_t *p_item = (uint8_t *)(radioList + storage.GetIndex());
    if (mode == MODE_RADIO) {
        uint8_t *p_name = p_item + sizeof(long);

        lcd.setCursor(0, 0);
        char c;
        while ((c = (char)pgm_read_byte_near(p_name++)) != '\0') {
            lcd.print(c);
        }

        lcd.setCursor(0, 2);
        text.clear();
        text.add("C\xBF""a\xBD\xE5\xB8\xC7 ");  // "Станция "
        text.add(storage.GetIndex() + 1);
        text.add(" \xB8\xB7 ");                 // " из "
        text.add(listSize);
        // sprintf(text, "C\xBF""a\xBD\xE5\xB8\xC7 %2d \xB8\xB7 %d ", storage.GetIndex() + 1, listSize);
        lcd.print(text);
    }
    long wave = (long)pgm_read_dword_near(p_item);
    MP1090S::SetStation(wave);
    storage.Save();
}

void radioButtons() {
    if (ButtonUp > 0) {
        ButtonUp = 0;
        storage.SetVolume(storage.GetVolume() + 1);
        showRadioVolume();
        storage.Save();
    }
    if (ButtonDown > 0) {
        ButtonDown = 0;
        storage.SetVolume(storage.GetVolume() - 1);
        showRadioVolume();
        storage.Save();
    }
    if (ButtonLeft > 0) {
        ButtonLeft = 0;
        storage.SetIndex(storage.GetIndex() - 1);
        showRadioStation();
        storage.Save();
    }
    if (ButtonRight > 0) {
        ButtonRight = 0;
        storage.SetIndex(storage.GetIndex() + 1);
        showRadioStation();
        storage.Save();
    }    
}

bool checkAlarm() {
    DateTime now = rtc.now();
    uint8_t dayOfWeek = now.dayOfTheWeek();
    dayOfWeek = (dayOfWeek == 0) ? 6 : dayOfWeek - 1;

    for (uint16_t i = 0; i < storage.GetAlarmSize(); i++) {
        AlarmItem *pAlarmData = storage.GetAlarm(i);
        if (pAlarmData->state != ALARM_STATE::Off) break;
        if (checkAlarmTime(pAlarmData, now, dayOfWeek)) {
            if (pAlarmData->mode == ALARM_MODE::Voice) {
                if (storage.GetVolume() > 0) {
                    storage.SetVolume(0);
                    showRadioVolume();
                    storage.Save();
                }
            }
            if (pAlarmData->mode == ALARM_MODE::Mute) {
                pCurrentAlarm = pAlarmData;
                mode = MODE_ALARM;
            }
            return true;
        }
    }

//   // коррекция времени
//   if (corrSec != 0)
//   {
//     if (corrApplied)
//     {
//       if (now.hour() == 0 && now.minute() == 1 && now.second() == 0)
//         corrApplied = 0;
//     }
//     else
//     {
//       if (corrSec > 0)
//       {
//         if (now.hour() == 0 && now.minute() == 0 && now.second() == 0)
//         {
//           rtc.adjust(DateTime(now.year(), now.month(), now.day(), now.hour(), now.minute(), corrSec));
//           corrApplied = 1;
//         }
//       }
//       else
//       {
//         if (now.hour() == 23 && now.minute() == 59 && now.second() == 59)
//         {
//           rtc.adjust(DateTime(now.year(), now.month(), now.day(), now.hour(), now.minute(), now.second() + corrSec));
//           corrApplied = 1;
//         }
//       }
//     }
//   }

    return false;
}

void loopClock() {
    lcd.clear();
    while (mode == MODE_CLOCK) {
        if (updatetime >= UPDATE_TIME_PERIOD) {
            if (checkAlarm()) {
                break;
            }
            radioButtons();
            DateTime now = rtc.now();
            displayDate(now.year(), now.month(), now.day());
            if (checkAlarm()) {
                break;
            }
            radioButtons();
            displayTime(now.hour(), now.minute());
            updatetime = 0;
        } else {
            delay(500);
        }
    }
}

void loopRadio() {
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print(F("--------------------"));
    lcd.setCursor(0, 3);
    lcd.print(F("\xA1po\xBC:"));    // "Гром:"
    showRadioStation();
    showRadioVolume();
    while (mode == MODE_RADIO) {
        if (checkAlarm()) break;
        radioButtons();
    }
}

void loopAlarm() {
    lcd.clear();

    AlarmItem *pAlarmData = pCurrentAlarm;
    lcd.setCursor(6, 0);
    lcd.print(F("\xA0\xA9\xE0\xA5\xA7""bH\xA5K"));  // "БУДИЛЬНИК"
    displayTime(pAlarmData->hour, pAlarmData->minute);

    for (int count = 0; count < 1 && mode == MODE_ALARM; count ++) {
        int play = storage.GetCurrentPlay();
        const char *song = playList[play++];

        play_rtttl(song);
        // Пауза в 1 секунду
        for (int i = 0; i < 10 && mode == MODE_ALARM; i++) delay(100);
        // Сохраняем номер след. музыки
        if (play >= playListSize) play = 0;
        storage.SetCurrentPlay(play);
    }
    if (mode == MODE_ALARM) {
        if (storage.GetVolume() == 0) {
            storage.SetVolume(pAlarmData->volume);
        }
        showRadioVolume();
    }
    storage.Save();
    mode = MODE_CLOCK;
}

void showMenu() {
    DateTime now = rtc.now();
    setting.year = now.year();
    setting.month = now.month();
    setting.day = now.day();
    setting.hour = now.hour();
    setting.minute = now.minute();
    setting.second = now.second();

    memset(alarm, 0, sizeof(alarm));
    for (int i = 0; i < ALARM_SIZE; i++) {
        auto src = storage.GetAlarm(i);
        auto dst = &alarm[i];
        if (src->state == ALARM_STATE::Off) break;
        dst->state = true;
        dst->Monday = src->week & FLAG_MONDAY;
        dst->Tuesday = src->week & FLAG_TUESDAY;
        dst->Wednesday = src->week & FLAG_WEDNESDAY;
        dst->Thursday = src->week & FLAG_THURSDAY;
        dst->Friday = src->week & FLAG_FRIDAY;
        dst->Saturday = src->week & FLAG_SATURDAY;
        dst->Sunday = src->week & FLAG_SUNDAY;
        dst->mode = src->mode == ALARM_MODE::Voice ? 1: 0;
        dst->volume = src->volume;
        dst->radio = src->radio;
    }
    menu.refresh();
    menu.home();
}

void actionExit() {
    mode = MODE_CLOCK;
}

void actionDateSave() {
    DateTime now = rtc.now();
    DateTime date = DateTime(setting.year, setting.month, setting.day, now.hour(), now.minute(), now.second());
    rtc.adjust(date);
    menu.back();
}

void actionTimeSave() {
    DateTime now = rtc.now();
    DateTime date = DateTime(now.year(), now.month(), now.day(), setting.hour, setting.minute, setting.second);
    rtc.adjust(date);
    menu.back();
}

void actionAlarmSave() {
    storage.AlarmClear();
    for (int i = 0; i < ALARM_SIZE; i++) {
        auto src = &alarm[i];
        auto dst = storage.GetAlarm(i);
        if (!src->state) continue;
        dst->state = ALARM_STATE::On;
        dst->week = 0;
        dst->week |= src->Monday ? FLAG_MONDAY: 0;
        dst->week |= src->Tuesday ? FLAG_TUESDAY: 0;
        dst->week |= src->Wednesday ? FLAG_WEDNESDAY: 0;
        dst->week |= src->Thursday ? FLAG_THURSDAY: 0;
        dst->week |= src->Friday ? FLAG_FRIDAY: 0;
        dst->week |= src->Saturday ? FLAG_SATURDAY: 0;
        dst->week |= src->Sunday ? FLAG_SUNDAY: 0;
        dst->mode = src->mode ? ALARM_MODE::Voice : ALARM_MODE::Mute;
        dst->hour = src->hour;
        dst->minute = src->minute;
        dst->second = 0;
        dst->volume = src->mode ? src->volume : 0;
        dst->radio = src->mode ? src->radio : 0;
    }
    storage.Save();
    menu.back();
}

char* getAlarmTitle(DEVICE_SETTING_ALARM* value) {
    text.clear();
    if (!value->state) {
        text = F("[\xBEyc\xBFo]");
        return text.c_str();
    }
    text = value->mode ? F("[B\xBA\xBB]  ") : F("[B\xC3\xBA\xBB] ");
    if (value->hour < 10) text += ' ';
    text += value->hour;
    text += ':';
    if (value->minute < 10) text += '0';
    text += value->minute;
    return text;
}

void loopMenu() {
    showMenu();
    while (ButtonControl == 0 && mode == MODE_SETTING) {
        if (ButtonUp > 0) {
            ButtonUp = 0;
            menu.up();
        }
        if (ButtonDown > 0) {
            ButtonDown = 0;
            menu.down();
        }
        if (ButtonLeft > 0) {
            ButtonLeft = 0;
            menu.left();
        }
        if (ButtonRight > 0) {
            ButtonRight = 0;
            menu.right();
        }
    }
}

void setup() {
    Serial.begin(115200);

    Wire.begin();
    Wire.setClock(400000);

    Serial.println(F("Initialize variables from EEPROM"));
    storage.begin();
    storage.Load();

    Serial.println(F("Initialize Buttons"));
    // Разрешаем PCINT для указанных пинов
    PCMSK0 |= bit(PB0) | bit(PB1) | bit(PB2) | bit(PB3) | bit(PB4);
    // Очищаем признак запроса прерывания для соответствующей группы пинов
    PCIFR  |= 1;    //bit(PCIF0)
    // Разрешаем PCINT для соответствующей группы пинов
    PCICR  |= 1;    //bit(PCIE0)

    Serial.println(F("Initialize Video"));
    lcd.begin(lcdRows, lcdLines);
    lcd.setBacklight(1);
    lcd.clear();
    // для того чтобы использовать print, кодируем ситмволы с 1, а не с 0, так как 0 признак конца строки
    lcd.createChar(1, _L1);
    lcd.createChar(2, _L2);
    lcd.createChar(3, _L3);
    lcd.createChar(4, _B1);
    lcd.createChar(5, _B2);
    lcd.createChar(6, _B3);
    lcd.createChar(7, _B4);

    Serial.println(F("Initialize Menu"));

    menu.setBackSign("Ha\xB7""a\xE3");
    menu.onPrint([](const char* str, size_t len) {
        if (str) lcd.Print::write(str, len);
    });
    menu.onCursor([](uint8_t row, bool chosen, bool active) -> uint8_t {
        lcd.setCursor(0, row);
        lcd.print(chosen && !active ? '>' : ' ');
        return 1;
    });
    menu.onBuild([](gm::Builder& b) {
        b.Button(F("B\xC3""xo\xE3"), actionExit);  // "Выход"
        b.Page(GM_NEXT, F("\xE0""a\xBF""a"), [](gm::Builder& b) {  // Дата
            b.ValueInt<uint16_t>("\xA1""o\xE3", &setting.year, 2020, 2090, 1, DEC, "");
            b.ValueInt<uint8_t>("Mec\xC7\xE5", &setting.month, 1, 12, 1, DEC, "");
            b.ValueInt<uint8_t>("\xE0""e\xBD\xC4", &setting.day, 1, 31, 1, DEC, "");
            b.Button(F("Coxpa\xBD\xB8\xBF\xC4"), actionDateSave);  // "Сохранить"
        });
        b.Page(GM_NEXT, F("Bpe\xBC\xC7"), [](gm::Builder& b) {     // Время
            b.ValueInt<uint8_t>("\xAB""ac", &setting.hour, 1, 23, 1, DEC, "");
            b.ValueInt<uint8_t>("M\xB8\xBDy\xBF""a", &setting.minute, 1, 59, 1, DEC, "");
            b.ValueInt<uint8_t>("Ce\xBAy\xBD\xE3""a", &setting.second, 1, 59, 1, DEC, "");
            b.Button(F("Coxpa\xBD\xB8\xBF\xC4"), actionTimeSave);  // "Сохранить"
        });
        b.Page(GM_NEXT, F("\xA0y\xE3\xB8\xBB\xC4\xBD\xB8\xBA"), [](gm::Builder& b) {   // Будильник
            b.Page(GM_NEXT, getAlarmTitle(alarm1), [](gm::Builder& b) {
                if (b.Switch(F("B\xBA\xBB\xC6\xC0\xB8\xBF\xC4"), &alarm1->state)) b.refresh();
                b.Label(F("----------------"));
                if (alarm1->state) {
                    b.ValueInt<uint8_t>("\xAB""ac", &alarm1->hour, 1, 23, 1, DEC, "");
                    b.ValueInt<uint8_t>("M\xB8\xBDy\xBF""a", &alarm1->minute, 1, 59, 1, DEC, "");
                    b.Label(F("----------------"));
                    b.Switch(F("\xA8o\xBD""e\xE3""e\xBB\xC4\xBD\xB8\xBA"), &alarm1->Monday);
                    b.Switch(F("B\xBFop\xBD\xB8\xBA"), &alarm1->Tuesday);
                    b.Switch(F("Cpe\xE3""a"), &alarm1->Wednesday);
                    b.Switch(F("\xAB""e\xBF\xB3""ep\xB4"), &alarm1->Thursday);
                    b.Switch(F("\xA8\xC7\xBF\xBD\xB8\xE5""a"), &alarm1->Friday);
                    b.Switch(F("Cy\xB2\xB2o\xBF""a"), &alarm1->Saturday);
                    b.Switch(F("Boc\xBApece\xBD\xC4""e"), &alarm1->Sunday);
                    b.Label(F("----------------"));
                    if (b.Select("Pa\xE3\xB8o", &alarm1->mode, "B\xC3\xBA\xBB;B\xBA\xBB")) b.refresh();
                    if (alarm1->mode == 1) {
                        b.ValueInt<uint8_t>("\xA1po\xBC\xBAoc\xBF\xC4", &alarm1->volume, 1, 15, 1, DEC, "");
                        b.ValueInt<uint8_t>("C\xBF""a\xBD\xE5\xC7", &alarm1->radio, 0, 30, 1, DEC, "");
                    }
                    b.Label(F("----------------"));
                }
            });
            b.Page(GM_NEXT, getAlarmTitle(alarm2), [](gm::Builder& b) {
                if (b.Switch(F("B\xBA\xBB\xC6\xC0\xB8\xBF\xC4"), &alarm2->state)) b.refresh();
                b.Label(F("----------------"));
                if (alarm2->state) {
                    b.ValueInt<uint8_t>("\xAB""ac", &alarm2->hour, 1, 23, 1, DEC, "");
                    b.ValueInt<uint8_t>("M\xB8\xBDy\xBF""a", &alarm2->minute, 1, 59, 1, DEC, "");
                    b.Label(F("----------------"));
                    b.Switch(F("\xA8o\xBD""e\xE3""e\xBB\xC4\xBD\xB8\xBA"), &alarm2->Monday);
                    b.Switch(F("B\xBFop\xBD\xB8\xBA"), &alarm2->Tuesday);
                    b.Switch(F("Cpe\xE3""a"), &alarm2->Wednesday);
                    b.Switch(F("\xAB""e\xBF\xB3""ep\xB4"), &alarm2->Thursday);
                    b.Switch(F("\xA8\xC7\xBF\xBD\xB8\xE5""a"), &alarm2->Friday);
                    b.Switch(F("Cy\xB2\xB2o\xBF""a"), &alarm2->Saturday);
                    b.Switch(F("Boc\xBApece\xBD\xC4""e"), &alarm2->Sunday);
                    b.Label(F("----------------"));
                    if (b.Select("Pa\xE3\xB8o", &alarm2->mode, "B\xC3\xBA\xBB;B\xBA\xBB")) b.refresh();
                    if (alarm2->mode == 1) {
                        b.ValueInt<uint8_t>("\xA1po\xBC\xBAoc\xBF\xC4", &alarm2->volume, 1, 15, 1, DEC, "");
                        b.ValueInt<uint8_t>("C\xBF""a\xBD\xE5\xC7", &alarm2->radio, 0, 30, 1, DEC, "");
                    }
                    b.Label(F("----------------"));
                }
            });
            b.Page(GM_NEXT, getAlarmTitle(alarm3), [](gm::Builder& b) {
                if (b.Switch(F("B\xBA\xBB\xC6\xC0\xB8\xBF\xC4"), &alarm3->state)) b.refresh();
                b.Label(F("----------------"));
                if (alarm3->state) {
                    b.ValueInt<uint8_t>("\xAB""ac", &alarm3->hour, 1, 23, 1, DEC, "");
                    b.ValueInt<uint8_t>("M\xB8\xBDy\xBF""a", &alarm3->minute, 1, 59, 1, DEC, "");
                    b.Label(F("----------------"));
                    b.Switch(F("\xA8o\xBD""e\xE3""e\xBB\xC4\xBD\xB8\xBA"), &alarm3->Monday);
                    b.Switch(F("B\xBFop\xBD\xB8\xBA"), &alarm3->Tuesday);
                    b.Switch(F("Cpe\xE3""a"), &alarm3->Wednesday);
                    b.Switch(F("\xAB""e\xBF\xB3""ep\xB4"), &alarm3->Thursday);
                    b.Switch(F("\xA8\xC7\xBF\xBD\xB8\xE5""a"), &alarm3->Friday);
                    b.Switch(F("Cy\xB2\xB2o\xBF""a"), &alarm3->Saturday);
                    b.Switch(F("Boc\xBApece\xBD\xC4""e"), &alarm3->Sunday);
                    b.Label(F("----------------"));
                    if (b.Select("Pa\xE3\xB8o", &alarm3->mode, "B\xC3\xBA\xBB;B\xBA\xBB")) b.refresh();
                    if (alarm3->mode == 1) {
                        b.ValueInt<uint8_t>("\xA1po\xBC\xBAoc\xBF\xC4", &alarm3->volume, 1, 15, 1, DEC, "");
                        b.ValueInt<uint8_t>("C\xBF""a\xBD\xE5\xC7", &alarm3->radio, 0, 30, 1, DEC, "");
                    }
                    b.Label(F("----------------"));
                }
            });
            b.Page(GM_NEXT, getAlarmTitle(alarm4), [](gm::Builder& b) {
                if (b.Switch(F("B\xBA\xBB\xC6\xC0\xB8\xBF\xC4"), &alarm4->state)) b.refresh();
                b.Label(F("----------------"));
                if (alarm4->state) {
                    b.ValueInt<uint8_t>("\xAB""ac", &alarm4->hour, 1, 23, 1, DEC, "");
                    b.ValueInt<uint8_t>("M\xB8\xBDy\xBF""a", &alarm4->minute, 1, 59, 1, DEC, "");
                    b.Label(F("----------------"));
                    b.Switch(F("\xA8o\xBD""e\xE3""e\xBB\xC4\xBD\xB8\xBA"), &alarm4->Monday);
                    b.Switch(F("B\xBFop\xBD\xB8\xBA"), &alarm4->Tuesday);
                    b.Switch(F("Cpe\xE3""a"), &alarm4->Wednesday);
                    b.Switch(F("\xAB""e\xBF\xB3""ep\xB4"), &alarm4->Thursday);
                    b.Switch(F("\xA8\xC7\xBF\xBD\xB8\xE5""a"), &alarm4->Friday);
                    b.Switch(F("Cy\xB2\xB2o\xBF""a"), &alarm4->Saturday);
                    b.Switch(F("Boc\xBApece\xBD\xC4""e"), &alarm4->Sunday);
                    b.Label(F("----------------"));
                    if (b.Select("Pa\xE3\xB8o", &alarm4->mode, "B\xC3\xBA\xBB;B\xBA\xBB")) b.refresh();
                    if (alarm4->mode == 1) {
                        b.ValueInt<uint8_t>("\xA1po\xBC\xBAoc\xBF\xC4", &alarm4->volume, 1, 15, 1, DEC, "");
                        b.ValueInt<uint8_t>("C\xBF""a\xBD\xE5\xC7", &alarm4->radio, 0, 30, 1, DEC, "");
                    }
                    b.Label(F("----------------"));
                }
            });
            b.Page(GM_NEXT, getAlarmTitle(alarm5), [](gm::Builder& b) {
                if (b.Switch(F("B\xBA\xBB\xC6\xC0\xB8\xBF\xC4"), &alarm5->state)) b.refresh();
                b.Label(F("----------------"));
                if (alarm5->state) {
                    b.ValueInt<uint8_t>("\xAB""ac", &alarm5->hour, 1, 23, 1, DEC, "");
                    b.ValueInt<uint8_t>("M\xB8\xBDy\xBF""a", &alarm5->minute, 1, 59, 1, DEC, "");
                    b.Label(F("----------------"));
                    b.Switch(F("\xA8o\xBD""e\xE3""e\xBB\xC4\xBD\xB8\xBA"), &alarm5->Monday);
                    b.Switch(F("B\xBFop\xBD\xB8\xBA"), &alarm5->Tuesday);
                    b.Switch(F("Cpe\xE3""a"), &alarm5->Wednesday);
                    b.Switch(F("\xAB""e\xBF\xB3""ep\xB4"), &alarm5->Thursday);
                    b.Switch(F("\xA8\xC7\xBF\xBD\xB8\xE5""a"), &alarm5->Friday);
                    b.Switch(F("Cy\xB2\xB2o\xBF""a"), &alarm5->Saturday);
                    b.Switch(F("Boc\xBApece\xBD\xC4""e"), &alarm5->Sunday);
                    b.Label(F("----------------"));
                    if (b.Select("Pa\xE3\xB8o", &alarm5->mode, "B\xC3\xBA\xBB;B\xBA\xBB")) b.refresh();
                    if (alarm5->mode == 1) {
                        b.ValueInt<uint8_t>("\xA1po\xBC\xBAoc\xBF\xC4", &alarm5->volume, 1, 15, 1, DEC, "");
                        b.ValueInt<uint8_t>("C\xBF""a\xBD\xE5\xC7", &alarm5->radio, 0, 30, 1, DEC, "");
                    }
                    b.Label(F("----------------"));
                }
            });
            b.Page(GM_NEXT, getAlarmTitle(alarm6), [](gm::Builder& b) {
                if (b.Switch(F("B\xBA\xBB\xC6\xC0\xB8\xBF\xC4"), &alarm6->state)) b.refresh();
                b.Label(F("----------------"));
                if (alarm6->state) {
                    b.ValueInt<uint8_t>("\xAB""ac", &alarm6->hour, 1, 23, 1, DEC, "");
                    b.ValueInt<uint8_t>("M\xB8\xBDy\xBF""a", &alarm6->minute, 1, 59, 1, DEC, "");
                    b.Label(F("----------------"));
                    b.Switch(F("\xA8o\xBD""e\xE3""e\xBB\xC4\xBD\xB8\xBA"), &alarm6->Monday);
                    b.Switch(F("B\xBFop\xBD\xB8\xBA"), &alarm6->Tuesday);
                    b.Switch(F("Cpe\xE3""a"), &alarm6->Wednesday);
                    b.Switch(F("\xAB""e\xBF\xB3""ep\xB4"), &alarm6->Thursday);
                    b.Switch(F("\xA8\xC7\xBF\xBD\xB8\xE5""a"), &alarm6->Friday);
                    b.Switch(F("Cy\xB2\xB2o\xBF""a"), &alarm6->Saturday);
                    b.Switch(F("Boc\xBApece\xBD\xC4""e"), &alarm6->Sunday);
                    b.Label(F("----------------"));
                    if (b.Select("Pa\xE3\xB8o", &alarm6->mode, "B\xC3\xBA\xBB;B\xBA\xBB")) b.refresh();
                    if (alarm6->mode == 1) {
                        b.ValueInt<uint8_t>("\xA1po\xBC\xBAoc\xBF\xC4", &alarm6->volume, 1, 15, 1, DEC, "");
                        b.ValueInt<uint8_t>("C\xBF""a\xBD\xE5\xC7", &alarm6->radio, 0, 30, 1, DEC, "");
                    }
                    b.Label(F("----------------"));
                }
            });
            b.Button(F("Coxpa\xBD\xB8\xBF\xC4"), actionAlarmSave);  // "Сохранить"
        });       
    });
    
    Serial.println(F("Initialize Radio"));
    MP1090S::InitI2C(radio_RST, radio_SEN);
    MP1090S::SetBand(MHz87_5_108);
    uint8_t *p_item = (uint8_t *)(radioList + 34);
    long wave = (long)pgm_read_dword_near(p_item);
    MP1090S::SetStation(wave);
    MP1090S::SetVolume(storage.GetVolume());

    Serial.println(F("Initialize Date/Time"));
    rtc.begin(&Wire);
    if (rtc.lostPower()) {
        rtc.adjust(DateTime(2026, 1, 1, 0, 0, 0));
    }
    rtc.writeSqwPinMode(Ds3231SqwPinMode::DS3231_SquareWave1Hz);
    rtc.enable32K();
    attachInterrupt(digitalPinToInterrupt(2), isr_time, FALLING);

    Serial.println(F("Initialize buzzer"));
    pinMode(TONE_PIN, OUTPUT);
}

void loop() {
    if (ButtonControl > 0) {
        ButtonControl = 0;
        switchmode();
    }
    switch (mode) {
        case MODE_CLOCK:
            loopClock();
            return;
        case MODE_ALARM:
            loopAlarm();
            return;
        case MODE_RADIO:
            loopRadio();
            return;
        case MODE_SETTING:
            loopMenu();
            return;
        default:
            error("MODE ERROR");
    }
}
