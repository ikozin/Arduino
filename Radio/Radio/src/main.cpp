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
#include "RTClib.h"                 //https://microsin.net/adminstuff/hardware/ds3231-extremely-accurate-rtc.html
#include "strings.h"
#include "menu_strings.h"

#ifndef ARDUINO_AVR_PRO
#error Select board: Arduino Pro Mini 
#endif

#define DEBUG_CONSOLE

 #ifdef DEBUG_CONSOLE
    void LOG(const char* str, ...) {
        va_list args;
        va_start(args, str);
        while (*str) {
            if (*str == '$' && str[1]) {
                ++str;
                switch (*str) {
                    case 'i': Serial.print(va_arg(args, int)); break;
                    case 'l': Serial.print(va_arg(args, long)); break;
                    case 'x': Serial.print("0x");Serial.print(va_arg(args, int), HEX); break;
                }
            } else {
                Serial.print(*str);
            }
            ++str;
        }

        va_end(args);
        Serial.println();
        return;
    }    
#else
    #define LOG(...)
#endif

unsigned long lasttime = 0; // время последнего срабатывания прерывания, для исключения дребезга и мнгновенного срабатывания несколько раз.
String24 text;
volatile uint8_t mode  = MODE_SETTING;

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

const char* months[12] = {
  month01,  //"\xC7\xBD\xB3\x61\x70\xC4",
  month02,  //"\xE4\x65\xB3\x70\x61\xBB\xC4",
  month03,  //"\xBC\x61\x70\xBF",
  month04,  //"\x61\xBE\x70\x65\xBB\xC4",
  month05,  //"\xBC\x61\xB9",
  month06,  //"\xB8\xC6\xBD\xC4",
  month07,  //\xB8\xC6\xBB\xC4",
  month08,  //"\x61\xB3\xB4\x79\x63\xBF",
  month09,  //"\x63\x65\xBD\xBF\xC7\xB2\x70\xC4",
  month10,  //"\x6F\xBA\xBF\xC7\xB2\x70\xC4",
  month11,  //"\xBD\x6F\xC7\xB2\x70\xC4",
  month12,  //\xE3\x65\xBA\x61\xB2\x70\xC4",
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

const RadioItem radioList[] PROGMEM = {
  { 87500, radio01 },
  { 87900, radio02 },
  { 88300, radio03 },
  { 88700, radio04 },
  { 89100, radio05 },
  { 89500, radio06 },
  { 89900, radio07 },
  { 90300, radio08 },
  { 90800, radio09 },
  { 91200, radio10 },
  { 91600, radio11 },
  { 92000, radio12 },
  { 92400, radio13 },
  { 92800, radio14 },
  { 93200, radio15 },
  { 93600, radio16 },
  { 94000, radio17 },
  { 94400, radio18 },
  { 94800, radio19 },
  { 95200, radio20 },
  { 95600, radio21 },
  { 96000, radio22 },
  { 96400, radio23 },
  { 96800, radio24 },
  { 97200, radio25 },
  { 97600, radio26 },
  { 98000, radio27 },
  { 98400, radio28 },
  { 98800, radio29 },
  { 99200, radio30 },
  { 99600, radio31 },
  {100100, radio32 },
  {100500, radio33 },
  {101200, radio34 },
  {101800, radio35 },
  {102100, radio36 },
  {102500, radio37 },
  {103000, radio38 },
  {103400, radio39 },
  {103700, radio40 },
  {104200, radio41 },
  {104700, radio42 },
  {105000, radio43 },
  {105300, radio44 },
  {105700, radio45 },
  {106200, radio46 },
  {106600, radio47 },
  {107000, radio48 },
  {107400, radio49 },
  {107800, radio50 },
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
    song25,
};
const int playListSize = sizeof(playList) / sizeof(char*);

LiquidCrystal_I2C lcd(0);
GyverMenu menu(lcdRows, lcdLines);
//GyverDS3231Min  rtc;
RTC_DS3231 rtc;
Storage<listSize, playListSize, 15> storage; 

// Маппинг: PB0=D8=Down, PB1=D9=Control, PB2=D10=Up, PB3=D11=Right, PB4=D12=Left

enum ButtonPin : uint8_t {
    BTN_DOWN = 0,   // PB0 (D8)
    BTN_CONTROL,    // PB1 (D9)
    BTN_UP,         // PB2 (D10)
    BTN_LEFT,       // PB3 (D11)
    BTN_RIGHT,      // PB4 (D12)
    BTN_COUNT
};

#define ButtonControl   (values[BTN_CONTROL])
#define ButtonUp        (values[BTN_UP])
#define ButtonDown      (values[BTN_DOWN])
#define ButtonLeft      (values[BTN_LEFT])
#define ButtonRight     (values[BTN_RIGHT])

volatile uint8_t values[BTN_COUNT] = { 0, 0, 0, 0, 0 };
static uint8_t oldPINB = 0xFF;

// Обработчик запросов прерывания от пинов D8..D12 (PB0..PB4)
ISR(PCINT0_vect) {
    uint8_t value = PINB;
    uint8_t changedbits = value ^ oldPINB;
    oldPINB = value;

    for (uint8_t i = 0; i < BTN_COUNT; i++) {
        if (changedbits & bit(i)) {
            values[i] = value & bit(i);
        }
    }
}

volatile int delayLoopCnt = 0;

#define UPDATE_TIME_PERIOD  (60)
volatile uint8_t    updatetime = UPDATE_TIME_PERIOD;
// Обработчик прерывания на D2
void isr_time() { updatetime ++; }

void error(const char *info) {
    LOG(info);
    lcd.clear();
    lcd.home();
    lcd.print(info);
    for (;;);
}

void displayDate(uint8_t day, uint8_t month, uint16_t year) {
    text.clear();
    text.add("  ");
    text.add(day);
    text.add(' ');
    text.add(months[month - 1]);
    text.add(' ');
    text.add(year);
    text.add("  ");
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

void setRadioVolume(uint8_t volume) {
    if (storage.SetVolume(volume)) {
        storage.save();
        MP1090S::SetVolume(storage.GetVolume());
    }
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
}

void setRadioStation(uint8_t index) {
    uint8_t *p_item = nullptr;
    if (storage.SetIndex(index)) {
        p_item = (uint8_t *)(radioList + storage.GetIndex());
        long wave = (long)pgm_read_dword_near(p_item);
        MP1090S::SetStation(wave);
        storage.save();
    } else {
        p_item = (uint8_t *)(radioList + storage.GetIndex());
    }
    if (mode == MODE_RADIO) {
        uint8_t *p_name = p_item + sizeof(long);

        lcd.setCursor(0, 0);
        char c;
        while ((c = (char)pgm_read_byte_near(p_name++)) != '\0') {
            lcd.print(c);
        }

        lcd.setCursor(0, 2);
        text.clear();
        text.add(ui_station1);                  // "Станция "
        text.add(storage.GetIndex() + 1);
        text.add(ui_station2);                  // " из "
        text.add(listSize);
        lcd.print(text);
    }
}



void radioButtons() {
    if (ButtonControl > 0) {
        LOG("ButtonControl");
        ButtonControl = 0;
        switchmode();
        return;
    }
    if (ButtonUp > 0) {
        LOG("ButtonUp");
        ButtonUp = 0;
        setRadioVolume(storage.GetVolume() + 1);
        return;
    }
    if (ButtonDown > 0) {
        LOG("ButtonDown");
        ButtonDown = 0;
        setRadioVolume(storage.GetVolume() - 1);
        return;
    }
    if (ButtonLeft > 0) {
        LOG("ButtonLeft");
        ButtonLeft = 0;
        setRadioStation(storage.GetIndex() - 1);
        return;
    }
    if (ButtonRight > 0) {
        LOG("ButtonRight");
        ButtonRight = 0;
        setRadioStation(storage.GetIndex() + 1);
        return;
    }    
}

bool checkAlarm() {
    // LOG("checkAlarm");
    DateTime now = rtc.now();
    uint8_t dayOfWeek = now.dayOfTheWeek();
    dayOfWeek = (dayOfWeek == 0) ? 6 : dayOfWeek - 1;

    for (uint16_t i = 0; i < storage.GetAlarmSize(); i++) {
        AlarmItem *pAlarmData = storage.GetAlarm(i);
        if (pAlarmData->state == ALARM_STATE::Off) break;
        if (checkAlarmTime(pAlarmData, now, dayOfWeek)) {
            if (pAlarmData->mode == ALARM_MODE::Mute) {
                if (storage.GetVolume() > 0) {
                    setRadioVolume(0);
                }
            }
            if (pAlarmData->mode == ALARM_MODE::Voice) {
                pCurrentAlarm = pAlarmData;
                mode = MODE_ALARM;
                setRadioStation(pCurrentAlarm->radio);
                setRadioVolume(pCurrentAlarm->volume);
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
    LOG("CLOCK");
    lcd.clear();
    updatetime = UPDATE_TIME_PERIOD;
    while (mode == MODE_CLOCK) {
        radioButtons();
        if ((delayLoopCnt >= 10) && checkAlarm()) {
            delayLoopCnt = 0;
            break;
        }
        if (updatetime >= UPDATE_TIME_PERIOD) {
            updatetime = 0;
            DateTime now = rtc.now();
            displayDate(now.day(), now.month(), now.year());
            if (checkAlarm()) break;
            displayTime(now.hour(), now.minute());
        } else {
            delay(100);
        }
        delayLoopCnt++;
    }
}

void loopRadio() {
    LOG("RADIO");
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print(F("--------------------"));
    lcd.setCursor(0, 3);
    lcd.print(ui_volume);    // "Гром:"
    setRadioStation(storage.GetIndex());
    if (checkAlarm()) return;
    setRadioVolume(storage.GetVolume());
    if (checkAlarm()) return;
    while (mode == MODE_RADIO) {
        if ((delayLoopCnt >= 10) && checkAlarm()) {
            delayLoopCnt = 0;
            break;
        }
        radioButtons();
        delay(100);
        delayLoopCnt++;
    }
}

void loopAlarm() {
    lcd.clear();

    AlarmItem *pAlarmData = pCurrentAlarm;
    lcd.setCursor(6, 0);
    lcd.print(F(ui_alarm));  // "БУДИЛЬНИК"
    displayTime(pAlarmData->hour, pAlarmData->minute);
    
    int play = storage.GetCurrentPlay();
    const char *song = playList[play];
    play_rtttl(song);

    storage.SetNextPlay();
    storage.save();
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
    switchmode();
    //menu.home();
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
    storage.save();
    menu.back();
}

char* getAlarmTitle(DEVICE_SETTING_ALARM* value) {
    text.clear();
    if (!value->state) {
        text.add(F(menu_empty));
        return text.c_str();
    }
    text.add(value->mode ? F("[B\xBA\xBB]  ") : F("[B\xC3\xBA\xBB] "));
    if (value->hour < 10) text.add(' ');
    text.add(value->hour);
    text.add(':');
    if (value->minute < 10) text.add('0');
    text.add(value->minute);
    return text.c_str();
}

void loopMenu() {
    LOG("MENU");
    showMenu();
    while (mode == MODE_SETTING) {
        if (ButtonControl > 0) {
            ButtonControl = 0;
            menu.set();
        }
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
        delay(100);
    }
}

void MenuAlarm (gm::Builder& b, DEVICE_SETTING_ALARM* alarm){
    const __FlashStringHelper* empty = F("");
    const __FlashStringHelper* line = S_SEPARATOR;
    if (b.Switch(S_ON, &alarm->state)) b.refresh();
    b.Label(line);
    if (alarm->state) {
        b.ValueInt<uint8_t>(S_HOUR, &alarm->hour, 1, 23, 1, DEC, empty);
        b.ValueInt<uint8_t>(S_MINUTE, &alarm->minute, 1, 59, 1, DEC, empty);
        b.Label(line);
        b.Switch(S_MONDAY, &alarm->Monday);
        b.Switch(S_TUESDAY, &alarm->Tuesday);
        b.Switch(S_WEDNESDAY, &alarm->Wednesday);
        b.Switch(S_THURSDAY, &alarm->Thursday);
        b.Switch(S_FRIDAY, &alarm->Friday);
        b.Switch(S_SATURDAY, &alarm->Saturday);
        b.Switch(S_SUNDAY, &alarm->Sunday);
        b.Label(line);
        if (b.Select(S_RADIO, &alarm->mode, S_MODE)) b.refresh();
        if (alarm->mode == 1) {
            b.ValueInt<uint8_t>(S_VOLUME, &alarm->volume, 1, 15, 1, DEC, empty);
            b.ValueInt<uint8_t>(S_STATION, &alarm->radio, 0, 30, 1, DEC, empty);
        }
        b.Label(line);
    }    
}

void setup() {
    #ifdef DEBUG_CONSOLE
    Serial.begin(115200);
    #endif

    Wire.begin();
    Wire.setClock(400000);

    LOG("EEPROM");
    // storage.clear();
    // storage.save();
    storage.begin();
    LOG("Addr=$x", storage.GetAddress());
    storage.load();
    LOG("Addr=$x", storage.GetAddress());
    
    #ifdef DEBUG_CONSOLE
    LOG("Addr=$x, Ind=$i Vol=$i Cor=$i Cur=$i", storage.GetAddress(), storage.GetIndex(), storage.GetVolume(), storage.GetCorrSec(), storage.GetCurrentPlay());
    for (uint16_t i = 0; i < storage.GetAlarmSize(); i++) {
        AlarmItem* alarm = storage.GetAlarm(i);
        LOG("$x, $i:$i:$i, $x, $i, $i[$i]", 
            (int)alarm->state, 
            (int)alarm->hour, 
            (int)alarm->minute, 
            (int)alarm->second, 
            (int)alarm->week, 
            (int)alarm->mode,
            (int)alarm->radio,
            (int)alarm->volume);
    }
    #endif

    LOG("Initialize Buttons");
    // Разрешаем PCINT для указанных пинов
    PCMSK0 |= bit(PB0) | bit(PB1) | bit(PB2) | bit(PB3) | bit(PB4);
    // Очищаем признак запроса прерывания для соответствующей группы пинов
    PCIFR  |= 1;    //bit(PCIF0)
    // Разрешаем PCINT для соответствующей группы пинов
    PCICR  |= 1;    //bit(PCIE0)

    LOG("Initialize Video");
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
    
    LOG("Initialize Radio");
    MP1090S::InitI2C(radio_RST, radio_SEN);
    MP1090S::SetBand(MHz87_5_108);
    uint8_t *p_item = (uint8_t *)(radioList + storage.GetIndex());
    long wave = (long)pgm_read_dword_near(p_item);
    MP1090S::SetStation(wave);
    MP1090S::SetVolume(storage.GetVolume());

    LOG("Initialize Date/Time");
    rtc.begin(&Wire);
    if (rtc.lostPower()) {
        rtc.adjust(DateTime(2026, 1, 1, 0, 0, 0));
    }
    rtc.writeSqwPinMode(Ds3231SqwPinMode::DS3231_SquareWave1Hz);
    rtc.enable32K();
    attachInterrupt(digitalPinToInterrupt(2), isr_time, FALLING);

    LOG("Initialize Buzzer");
    pinMode(TONE_PIN, OUTPUT);

    LOG("Initialize Menu");
    menu.setBackSign(mune_back);
    menu.onPrint([](const char* str, size_t len) {
        if (str) lcd.Print::write(str, len);
    });
    menu.onCursor([](uint8_t row, bool chosen, bool active) -> uint8_t {
        lcd.setCursor(0, row);
        lcd.print(chosen && !active ? '>' : ' ');
        return 1;
    });
    menu.onBuild([](gm::Builder& b) {
        b.Button(S_EXIT, actionExit);  // "Выход"
        b.Page(GM_NEXT, S_DATE, [](gm::Builder& b) {  // "Дата"
            const __FlashStringHelper* S_EMPTY = F("");
            b.ValueInt<uint16_t>(S_YEAR, &setting.year, 2020, 2090, 1, DEC, S_EMPTY);
            b.ValueInt<uint8_t>(S_MONTH, &setting.month, 1, 12, 1, DEC, S_EMPTY);
            b.ValueInt<uint8_t>(S_DAY, &setting.day, 1, 31, 1, DEC, S_EMPTY);
            b.Button(S_SAVE, actionDateSave);  // "Сохранить"
        });
        b.Page(GM_NEXT, S_TIME, [](gm::Builder& b) {     // "Время"
            const __FlashStringHelper* S_EMPTY = F("");
            b.ValueInt<uint8_t>(S_HOUR, &setting.hour, 1, 23, 1, DEC, S_EMPTY);
            b.ValueInt<uint8_t>(S_MINUTE, &setting.minute, 1, 59, 1, DEC, S_EMPTY);
            b.ValueInt<uint8_t>(S_SECOND, &setting.second, 1, 59, 1, DEC, S_EMPTY);
            b.Button(S_SAVE, actionTimeSave);  // "Сохранить"
        });
        b.Page(GM_NEXT, S_ALARM, [](gm::Builder& b) {   // "Будильник"
            b.Page(GM_NEXT, getAlarmTitle(alarm1), [](gm::Builder& b) {
                MenuAlarm(b, alarm1);
            });
            b.Page(GM_NEXT, getAlarmTitle(alarm2), [](gm::Builder& b) {
                MenuAlarm(b, alarm2);
            });
            b.Page(GM_NEXT, getAlarmTitle(alarm3), [](gm::Builder& b) {
                MenuAlarm(b, alarm3);
            });
            b.Page(GM_NEXT, getAlarmTitle(alarm4), [](gm::Builder& b) {
                MenuAlarm(b, alarm4);
            });
            b.Page(GM_NEXT, getAlarmTitle(alarm5), [](gm::Builder& b) {
                MenuAlarm(b, alarm5);
            });
            b.Page(GM_NEXT, getAlarmTitle(alarm6), [](gm::Builder& b) {
                MenuAlarm(b, alarm6);
            });
            b.Button(S_SAVE, actionAlarmSave);  // "Сохранить"
        });       
    });
    menu.refresh();

    LOG("Start");
}

void loop() {
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
