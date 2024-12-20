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


AUDUIO 
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
// #define RELOCATE

#include "Radio.h"

#ifndef ARDUINO_AVR_PRO
#error Select board: Arduino Pro Mini 
#endif

#define ALARM_VOLUME    (5)

#define sizeofarray(a)  (sizeof(a)/sizeof(a[0]))

unsigned long lasttime = 0; // время последнего срабатывания прерывания, для исключения дребезга и мнгновенного срабатывания несколько раз.

LiquidCrystal_I2C lcd(0);

RTC_DS3231  rtc;

volatile uint8_t mode  = MODE_CLOCK;

byte _L1[8] = { B00000, B00000, B00000, B00000, B00000, B11111, B11111, B11111 };
byte _L2[8] = { B11111, B11111, B11111, B00000, B00000, B00000, B00000, B00000 };
byte _L3[8] = { B11111, B11111, B11111, B00000, B00000, B00000, B11111, B11111 };
byte _B1[8] = { B00111, B01111, B11111, B11111, B11111, B11111, B11111, B11111 };
byte _B2[8] = { B11100, B11110, B11111, B11111, B11111, B11111, B11111, B11111 };
byte _B3[8] = { B11111, B11111, B11111, B11111, B11111, B11111, B01111, B00111 };
byte _B4[8] = { B11111, B11111, B11111, B11111, B11111, B11111, B11110, B11100 };

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


/*
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

*/

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

int volume = 10;  // громкость
int index = 35;   // индекс радиостанции

AlarmItem *pCurrentAlarm = NULL;
AlarmItem alarmOn[4] = { {
        .week = FLAG_WORK_WEEK,
        .hour = 7,
        .minute = 10,
        .second = 0
    }, {
        .week = FLAG_SATURDAY | FLAG_SUNDAY,
        .hour = 9,
        .minute = 0,
        .second = 0
    }, {
        .week = 0,
        .hour = 0,
        .minute = 0,
        .second = 0
    }, {
        .week = 0,
        .hour = 0,
        .minute = 0,
        .second = 0
    },
};

AlarmItem alarmOff[4] = { {
        .week = FLAG_WORK_WEEK | FLAG_SATURDAY | FLAG_SUNDAY,
        .hour = 23,
        .minute = 0,
        .second = 0
    }, {
        .week = FLAG_WORK_WEEK,
        .hour = 7,
        .minute = 20,
        .second = 0
    }, {
        .week = FLAG_SATURDAY | FLAG_SUNDAY,
        .hour = 10,
        .minute = 0,
        .second = 0
    }, {
        .week = 0,
        .hour = 0,
        .minute = 0,
        .second = 0
    },
};

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

// Melodies.h
const int playListSize = sizeof(playList) / sizeof(char*);
int currentPlay = 0;

int8_t corrSec = 0;
bool corrApplied = 0;

void error(const char *text) {
    Serial.println(text);
    lcd.clear();
    lcd.home();
    lcd.print(text);
    for (;;);
}

void dumpInfoAlarm(const AlarmItem *pAlarmData) {
    char text[21];
    sprintf(text, "%02X, %02d:%02d:%02d", pAlarmData->week, pAlarmData->hour, pAlarmData->minute, pAlarmData->second);
    Serial.println(text);
}

void dumpInfo() {
    Serial.print(F("index = "));
    Serial.println(index);
    Serial.print(F("volume = "));
    Serial.println(volume);
    Serial.print(F("corrSec = "));
    Serial.println(corrSec);
    Serial.print(F("currentPlay = "));
    Serial.println(currentPlay);

    dumpInfoAlarm(&alarmOn[0]);
    dumpInfoAlarm(&alarmOn[1]);
    dumpInfoAlarm(&alarmOn[2]);
    dumpInfoAlarm(&alarmOn[3]);

    dumpInfoAlarm(&alarmOff[0]);
    dumpInfoAlarm(&alarmOff[1]);
    dumpInfoAlarm(&alarmOff[2]);
    dumpInfoAlarm(&alarmOff[3]);
}

#define isdigit(n) (n >= '0' && n <= '9')

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

void intToStr(String &text, uint8_t value) {
    uint8_t cnt = 0;
    while (value >= 10) {
        cnt += 1;
        value -= 10;
    }
    text += (cnt == 0)? ' ' : cnt + '0';
    text += value;
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
    volume = constrain(volume, 0, 15);
    if (mode == MODE_RADIO) {
        int i;
        lcd.setCursor(5, 3);
        for (i = 0; i < volume; i++) {
            lcd.print("\xFF");
        }
        for (; i < 15; i++) {
            lcd.print(" ");
        }
    }
    MP1090S::SetVolume(volume);
    EEPROM.write(EEPROM_ADDR_RADIO_VOLUME, volume);
}

void showRadioStation() {
    index = constrain(index, 0, listSize - 1);
    uint8_t *p_item = (uint8_t *)(radioList + index);
    if (mode == MODE_RADIO) {
        uint8_t *p_name = p_item + sizeof(long);

        lcd.setCursor(0, 0);
        char c;
        while ((c = (char)pgm_read_byte_near(p_name++)) != '\0') {
            lcd.print(c);
        }

        lcd.setCursor(0, 2);
        char text[20];
        sprintf(text, "C\xBF""a\xBD\xE5\xB8\xC7 %2d \xB8\xB7 %d ", index + 1, listSize);
        lcd.print(text);
    }
    long wave = (long)pgm_read_dword_near(p_item);
    MP1090S::SetStation(wave);
    EEPROM.write(EEPROM_ADDR_RADIO_INDEX, index);
}

void radioButtons() {
    if (digitalRead(pinVolumeUp) == LOW) {
        volume --;
        showRadioVolume();
    }
    if (digitalRead(pinVolumeDown) == LOW) {
        volume ++;
        showRadioVolume();
    }
    if (digitalRead(pinStationUp) == LOW) {
        index --;
        showRadioStation();
    }
    if (digitalRead(pinStationDown) == LOW) {
        index ++;
        showRadioStation();
    }
}

bool checkAlarm() {
    DateTime now = rtc.now();
    uint8_t dayOfWeek = now.dayOfTheWeek();
    dayOfWeek = (dayOfWeek == 0) ? 6 : dayOfWeek - 1;

    for (uint16_t i = 0; i < sizeof(alarmOn)/sizeof(alarmOn[0]); i++) {
        AlarmItem *pAlarmData = alarmOn + i;
        if (checkAlarmTime(pAlarmData, now, dayOfWeek)) {
            pCurrentAlarm = pAlarmData;
            mode = MODE_ALARM;
            return true;
        }
    }
    for (uint16_t i = 0; i < sizeof(alarmOff)/sizeof(alarmOff[0]); i++) {
        AlarmItem *pAlarmData = alarmOff + i;
        if (checkAlarmTime(pAlarmData, now, dayOfWeek)) {
            if (volume > 0) {
                volume = 0;
                showRadioVolume();
            }
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
        if (checkAlarm()) {
            break;
        }

        radioButtons();

        DateTime now = rtc.now();

        String text;
        text.reserve(24);
        text += now.day();
        text += ' ';
        text += months[now.month() - 1];
        text += ' ';
        text += now.year();

        lcd.setCursor((lcdRows - text.length()) >> 1, 0);
        lcd.print(text);

        if (checkAlarm()) {
            break;
        }

        radioButtons();

        displayTime(now.hour(), now.minute());
    }
}

void loopRadio() {
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print(F("--------------------"));
    lcd.setCursor(0, 3);
    lcd.print(F("\xA1po\xBC:"));

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
    lcd.print(F("\xA0\xA9\xE0\xA5\xA7""bH\xA5K"));
    displayTime(pAlarmData->hour, pAlarmData->minute);

    for (int count = 0; count < 1 && mode == MODE_ALARM; count ++) {
        const char *song = playList[currentPlay++];
        play_rtttl(song);
        // Пауза в 1 секунду
        for (int i = 0; i < 10 && mode == MODE_ALARM; i++) delay(100);
        // Сохраняем номер след. музыки
        if (currentPlay >= playListSize) currentPlay = 0;
        EEPROM.write(EEPROM_ADDR_ALARM_INDEX, currentPlay);
    }
    if (mode == MODE_ALARM) {
        if (volume == 0) {
            volume = ALARM_VOLUME;
        }
        showRadioVolume();
    }
    mode = MODE_CLOCK;
}

void setup() {
    Serial.begin(115200);
    Serial.println(F("Initialize variables from EEPROM"));
    index       = EEPROM.read(EEPROM_ADDR_RADIO_INDEX);
    volume      = EEPROM.read(EEPROM_ADDR_RADIO_VOLUME);
    corrSec     = EEPROM.read(EEPROM_ADDR_CORRECTION_SEC);
    currentPlay = EEPROM.read(EEPROM_ADDR_ALARM_INDEX);

    loadAlarmData(EEPROM_ADDR_ALARM_ON1,  &alarmOn[0]);
    loadAlarmData(EEPROM_ADDR_ALARM_ON2,  &alarmOn[1]);
    loadAlarmData(EEPROM_ADDR_ALARM_ON3,  &alarmOn[2]);
    loadAlarmData(EEPROM_ADDR_ALARM_ON4,  &alarmOn[3]);

    loadAlarmData(EEPROM_ADDR_ALARM_OFF1, &alarmOff[0]);
    loadAlarmData(EEPROM_ADDR_ALARM_OFF2, &alarmOff[1]);
    loadAlarmData(EEPROM_ADDR_ALARM_OFF3, &alarmOff[2]);
    loadAlarmData(EEPROM_ADDR_ALARM_OFF4, &alarmOff[3]);

    Serial.println(F("Initialize Buttons"));
    pinMode(controlPin, INPUT_PULLUP);
    attachInterrupt(1, switchmode, FALLING);
    pinMode(pinVolumeUp, INPUT_PULLUP);
    pinMode(pinVolumeDown, INPUT_PULLUP);
    pinMode(pinStationUp, INPUT_PULLUP);
    pinMode(pinStationDown, INPUT_PULLUP);
    Serial.println(F("Initialize Video"));
    lcd.begin(lcdLines);
    lcd.clear();
    // для того чтобы использовать print, кодируем ситмволы с 1, а не с 0, так как 0 признак конца строки
    lcd.createChar(1, _L1);
    lcd.createChar(2, _L2);
    lcd.createChar(3, _L3);
    lcd.createChar(4, _B1);
    lcd.createChar(5, _B2);
    lcd.createChar(6, _B3);
    lcd.createChar(7, _B4);

    Serial.println(F("Initialize Radio"));
    pinMode(radioRST, OUTPUT);
    digitalWrite(radioRST, 1);
    pinMode(radioSEN, OUTPUT);
    MP1090S::InitI2C(radioSEN);
    MP1090S::SetBand(MHz87_5_108);
    uint8_t *p_item = (uint8_t *)(radioList + index);
    long wave = (long)pgm_read_dword_near(p_item);
    MP1090S::SetStation(wave);
    MP1090S::SetVolume(volume);

    Serial.println(F("Initialize Date/Time"));
    rtc.begin();
    if (rtc.lostPower()) {
        rtc.adjust(DateTime(2024, 1, 1, 0, 0, 0));
    }
    Serial.println(F("Initialize buzzer"));
    pinMode(TONE_PIN, OUTPUT);

#ifdef RELOCATE
    EEPROM_ADDR_RADIO_INDEX = 8;
    EEPROM.write(EEPROM_ADDR_RADIO_INDEX, index);         // 1 byte
    EEPROM.write(EEPROM_ADDR_RADIO_VOLUME, volume);       // 1 byte
    EEPROM.write(EEPROM_ADDR_CORRECTION_SEC, corrSec);    // 1 byte
    EEPROM.write(EEPROM_ADDR_ALARM_INDEX, currentPlay);   // 1 byte
    saveAlarmData(EEPROM_ADDR_ALARM_ON1,  &alarmOn[0]);   // 4 byte
    saveAlarmData(EEPROM_ADDR_ALARM_ON2,  &alarmOn[1]);   // 4 byte
    saveAlarmData(EEPROM_ADDR_ALARM_ON3,  &alarmOn[2]);   // 4 byte
    saveAlarmData(EEPROM_ADDR_ALARM_ON4,  &alarmOn[3]);   // 4 byte
    saveAlarmData(EEPROM_ADDR_ALARM_OFF1, &alarmOff[0]);  // 4 byte
    saveAlarmData(EEPROM_ADDR_ALARM_OFF2, &alarmOff[1]);  // 4 byte
    saveAlarmData(EEPROM_ADDR_ALARM_OFF3, &alarmOff[2]);  // 4 byte
    saveAlarmData(EEPROM_ADDR_ALARM_OFF4, &alarmOff[3]);  // 4 byte
#endif
    //dumpInfo();
}

void loop() {
    switch (mode) {
        case MODE_CLOCK:
            loopClock();
            break;
        case MODE_ALARM:
            loopAlarm();
            break;
        case MODE_RADIO:
            loopRadio();
            break;
        case MODE_SETTING:
            loopSettings();
            break;
        default:
            error("MODE ERROR");
    }
}
