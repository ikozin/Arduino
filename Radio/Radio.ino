#include <Wire.h>
#include <Adafruit_LiquidCrystal.h>
#include <MP1090S.h>
#include <RTClib.h>
#include <EEPROM.h>

unsigned long lasttime = 0; // время последнего срабатывания прерывания, для исключения дребезга и мнгновенного срабатывания несколько раз.
const int controlPin = 3; // 3 or 2 only!!! так как используется прерывание
const int buttonPin1 = 4;
const int buttonPin2 = 5;
const int buttonPin3 = 6;
const int buttonPin4 = 7;

const int radioSEN = 8;
const int radioRST = 9;

const int lcdLines = 4;
const int lcdRows = 20;

Adafruit_LiquidCrystal lcd(0);

RTC_DS1307 rtc;

const byte MODE_CLOCK   = 0;
const byte MODE_ALARM   = 1;
const byte MODE_RADIO   = 2;
const byte MODE_SETTING = 3;

volatile byte mode  = MODE_CLOCK;

byte _L1[8] =
{
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B11111,
  B11111,
  B11111
};
byte _L2[8] =
{
  B11111,
  B11111,
  B11111,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000
};
byte _L3[8] =
{
  B11111,
  B11111,
  B11111,
  B00000,
  B00000,
  B00000,
  B11111,
  B11111
};
byte _B1[8] =
{
  B00111,
  B01111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111
};
byte _B2[8] =
{
  B11100,
  B11110,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111
};
byte _B3[8] =
{
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B01111,
  B00111
};
byte _B4[8] =
{
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11110,
  B11100
};

const char months[12][9] =
{
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

typedef struct _radioItem
{
  long wave;
  char name[21];
} RadioItem;

// Важно: русские буквы, видимо в unicode, так как массив с ними переполнен, да и вывод их не совпадает (кодировка)
const RadioItem radioList[] PROGMEM =
{
  { 87500, "Business FM     87,5"},
  { 87900, "C\xB8\xBF\xB8-FM         87,9"},
  { 88300, "Pe\xBFpo FM        88,3"},
  { 88700, "\xB0\xBCop FM         88,7"},
  { 89100, "Pa\xE3\xB8o Jazz      89,1"},
  { 89500, "Megapolis FM    89,5"},
  { 89900, "Ke\xBA""c FM         89,9"},
  { 90300, "A\xB3\xBFopa\xE3\xB8o       90,3"},
  { 90800, "Relax FM        90,8"},
  { 91200, "\xAFxo Moc\xBA\xB3\xC3      91,2"},
  { 91600, "Pa\xE3\xB8o Ky\xBB\xC4\xBFypa  91,6"},
  { 92000, "Moc\xBA\xB3""a FM       92,0"},
  { 92400, "Pa\xE3\xB8o \xE0""a\xC0""a      92,4"},
  { 92800, "Pa\xE3\xB8o Kap\xBD""a\xB3""a\xBB  92,8"},
  { 93200, "C\xBEop\xBF FM        93,2"},
  { 93600, "Ko\xBC\xBC""epca\xBD\xBF\xC2 FM  93,6"},
  { 94000, "Boc\xBFo\xBA FM       94,0"},
  { 94400, "Bec\xBD""a FM        94,4"},
  { 94800, "\xA1o\xB3op\xB8\xBF Moc\xBA\xB3""a  94,8"},
  { 95200, "Rock FM         95,2"},
  { 95600, "Pa\xE3\xB8o \xA4\xB3""e\xB7\xE3""a    95,6"},
  { 96000, "\xE0opo\xB6\xBDoe pa\xE3\xB8o  96,0"},
  { 96400, "Ta\xBA""c\xB8 FM        96,4"},
  { 96800, "\xE0""e\xBF""c\xBAoe pa\xE3\xB8o   96,8"},
  { 97200, "Pa\xE3\xB8o K\xA8        97,2"},
  { 97600, "Bec\xBF\xB8 FM        97,6"},
  { 98000, "Pa\xE3\xB8o \xACo\xBAo\xBB""a\xE3   98,0"},
  { 98400, "Pa\xE3\xB8o Pe\xBAop\xE3    98,4"},
  { 98800, "Pa\xE3\xB8o Romantika 98,8"},
  { 99200, "Pa\xE3\xB8o Op\xAA""e\xB9     99,2"},
  { 99600, "C\xBFo\xBB\xB8\xE5""a FM      99,6"},
  {100100, "Cepe\xB2p\xC7\xBD\xC3\xB9 \xE3o\xB6\xE3\xC4    "},
  {100500, "Best FM        100,5"},
  {100900, "Pa\xE3\xB8o Classic  100,9"},
  {101200, "DFM            101,2"},
  {101700, "Ha\xC1""e pa\xE3\xB8o     101,7"},
  {102100, "Mo\xBD\xBF""e-Kap\xBBo    102,1"},
  {102500, "Comedy Radio   102,5"},
  {103000, "\xAC""a\xBD""co\xBD         103,0"},
  {103400, "Ma\xC7\xBA           103,4"},
  {103700, "Maximum        103,7"},
  {104200, "NRJ            104,2"},
  {104700, "Pa\xE3\xB8o 7        104,7"},
  {105200, "Moscow FM      105,2"},
  {105700, "Pycc\xBAoe pa\xE3\xB8o  105,7"},
  {106200, "E\xB3po\xBE""a \xA8\xBB\xC6""c    106,2"},
  {106600, "Love Radio     106,6"},
  {107000, "PCH            107,0"},
  {107400, "X\xB8\xBF FM         107,4"},
  {107800, "M\xB8\xBB\xB8\xE5""e\xB9""c\xBA""a\xC7 \xB3o\xBB\xBD""a   "},
};
const int listSize = sizeof(radioList) / sizeof(RadioItem);

int volume = 10;  // громкость
int index = 32;   //

byte      alertWeek = 1 | 2 | 4 | 8 | 16;// | 32 | 64;
DateTime  alertTime = DateTime(2000, 1, 1, 11, 0, 0);

const int TONE_PIN = 10;

#define OCTAVE_OFFSET 0
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951

const int notes[] = { 0,
                      NOTE_C4, NOTE_CS4, NOTE_D4, NOTE_DS4, NOTE_E4, NOTE_F4, NOTE_FS4, NOTE_G4, NOTE_GS4, NOTE_A4, NOTE_AS4, NOTE_B4,
                      NOTE_C5, NOTE_CS5, NOTE_D5, NOTE_DS5, NOTE_E5, NOTE_F5, NOTE_FS5, NOTE_G5, NOTE_GS5, NOTE_A5, NOTE_AS5, NOTE_B5,
                      NOTE_C6, NOTE_CS6, NOTE_D6, NOTE_DS6, NOTE_E6, NOTE_F6, NOTE_FS6, NOTE_G6, NOTE_GS6, NOTE_A6, NOTE_AS6, NOTE_B6,
                      NOTE_C7, NOTE_CS7, NOTE_D7, NOTE_DS7, NOTE_E7, NOTE_F7, NOTE_FS7, NOTE_G7, NOTE_GS7, NOTE_A7, NOTE_AS7, NOTE_B7
                    };

/*
  http://ez4mobile.com/nokiatone/rtttf.htm
*/

const char song01[] PROGMEM = "Indiana:d=4,o=5,b=250:e,8p,8f,8g,8p,1c6,8p.,d,8p,8e,1f,p.,g,8p,8a,8b,8p,1f6,p,a,8p,8b,2c6,2d6,2e6,e,8p,8f,8g,8p,1c6,p,d6,8p,8e6,1f.6,g,8p,8g,e.6,8p,d6,8p,8g,e.6,8p,d6,8p,8g,f.6,8p,e6,8p,8d6,2c6";
const char song02[] PROGMEM = "Entertainer:d=4,o=5,b=140:8d,8d#,8e,c6,8e,c6,8e,2c.6,8c6,8d6,8d#6,8e6,8c6,8d6,e6,8b,d6,2c6,p,8d,8d#,8e,c6,8e,c6,8e,2c.6,8p,8a,8g,8f#,8a,8c6,e6,8d6,8c6,8a,2d6";
const char song03[] PROGMEM = "Bond:d=4,o=5,b=80:32p,16c#6,32d#6,32d#6,16d#6,8d#6,16c#6,16c#6,16c#6,16c#6,32e6,32e6,16e6,8e6,16d#6,16d#6,16d#6,16c#6,32d#6,32d#6,16d#6,8d#6,16c#6,16c#6,16c#6,16c#6,32e6,32e6,16e6,8e6,16d#6,16d6,16c#6,16c#7,c.7,16g#6,16f#6,g#.6";
const char song04[] PROGMEM = "MahnaMahna:d=16,o=6,b=125:c#,c.,b5,8a#.5,8f.,4g#,a#,g.,4d#,8p,c#,c.,b5,8a#.5,8f.,g#.,8a#.,4g,8p,c#,c.,b5,8a#.5,8f.,4g#,f,g.,8d#.,f,g.,8d#.,f,8g,8d#.,f,8g,d#,8c,a#5,8d#.,8d#.,4d#,8d#.";
const char song05[] PROGMEM = "MissionImp:d=16,o=6,b=95:32d,32d#,32d,32d#,32d,32d#,32d,32d#,32d,32d,32d#,32e,32f,32f#,32g,g,8p,g,8p,a#,p,c7,p,g,8p,g,8p,f,p,f#,p,g,8p,g,8p,a#,p,c7,p,g,8p,g,8p,f,p,f#,p,a#,g,2d,32p,a#,g,2c#,32p,a#,g,2c,a#5,8c,2p,32p,a#5,g5,2f#,32p,a#5,g5,2f,32p,a#5,g5,2e,d#,8d";
const char song06[] PROGMEM = "Pacman:d=4,o=5,b=112:32b,32p,32b6,32p,32f#6,32p,32d#6,32p,32b6,32f#6,16p,16d#6,16p,32c6,32p,32c7,32p,32g6,32p,32e6,32p,32c7,32g6,16p,16e6,16p,32b,32p,32b6,32p,32f#6,32p,32d#6,32p,32b6,32f#6,16p,16d#6,16p,32d#6,32e6,32f6,32p,32f6,32f#6,32g6,32p,32g6,32g#6,32a6,32p,32b.6";
const char song07[] PROGMEM = "Terminator II:d=4,o=5,b=90:32d6,16e6,2f6,8e6,8c6,2f,16p,32d6,16e6,2f6,8e6,8c6,2a6,2g6";
const char song08[] PROGMEM = "Toccata:d=4,o=5,b=160:16a4,16g4,1a4,16g4,16f4,16d4,16e4,2c#4,16p,d.4,2p,16a4,16g4,1a4,8e.4,8f.4,8c#.4,2d4";
const char song09[] PROGMEM = "Flinstones:d=4,o=5,b=40:32p,16f6,16a#,16a#6,32g6,16f6,16a#.,16f6,32d#6,32d6,32d6,32d#6,32f6,16a#,16c6,d6";
const char song10[] PROGMEM = "Tetris:d=4,o=5,b=160:e6,8b,8c6,8d6,16e6,16d6,8c6,8b,a,8a,8c6,e6,8d6,8c6,b,8b,8c6,d6,e6,c6,a,2a,8p,d6,8f6,a6,8g6,8f6,e6,8e6,8c6,e6,8d6,8c6,b,8b,8c6,d6,e6,c6,a,a";
const char song11[] PROGMEM = "AxelF:d=4,o=5,b=125:32p,8g,8p,16a#.,8p,16g,16p,16g,8c6,8g,8f,8g,8p,16d.6,8p,16g,16p,16g,8d#6,8d6,8a#,8g,8d6,8g6,16g,16f,16p,16f,8d,8a#,2g,p,ss,16f6,8d6,8c6,8a#,g,8a#.,16g,16p,16g,8c6,8g,8f,g,8d.6,16g,16p,16g,8d#6,8d6,8a#,8g,8d6,8g6,16g,16f,16p,16f,8d,8a#,2g";
const char song12[] PROGMEM = "girl:d=4,o=5,b=125:8g#,8e,8g#,8c#6,a,p,8f#,8d#,8f#,8b,g#,8f#,8e,p,8e,8c#,f#,c#,p,8f#,8e,g#,f#";
const char song13[] PROGMEM = "careaboutus:d=4,o=5,b=125:16f,16e,16f,16e,16f,16e,8d,16e,16d,16e,16d,16e,16d,16c,16d,d";
const char song14[] PROGMEM = "Scatman:d=4,o=5,b=200:8b,16b,32p,8b,16b,32p,8b,2d6,16p,16c#.6,16p.,8d6,16p,16c#6,8b,16p,8f#,2p.,16c#6,8p,16d.6,16p.,16c#6,16b,8p,8f#,2p,32p,2d6,16p,16c#6,8p,16d.6,16p.,16c#6,16a.,16p.,8e,2p.,16c#6,8p,16d.6,16p.,16c#6,16b,8p,8b,16b,32p,8b,16b,32p,8b,2d6,16p,16c#.6,16p.,8d6,16p,16c#6,8b,16p,8f#,2p.,16c#6,8p,16d.6,16p.,16c#6,16b,8p,8f#,2p,32p,2d6,16p,16c#6,8p,16d.6,16p.,16c#6,16a.,16p.,8e,2p.,16c#6,8p,16d.6,16p.,16c#6,16a,8p,8e,2p,32p,16f#.6,16p.,16b.,16p.";
const char song15[] PROGMEM = "Smoke:d=4,o=5,b=112:c,d#,f.,c,d#,8f#,f,p,c,d#,f.,d#,c,2p,8p,c,d#,f.,c,d#,8f#,f,p,c,d#,f.,d#,c,p";
const char song16[] PROGMEM = "countdown:d=4,o=5,b=125:p,8p,16b,16a,b,e,p,8p,16c6,16b,8c6,8b,a,p,8p,16c6,16b,c6,e,p,8p,16a,16g,8a,8g,8f#,8a,g.,16f#,16g,a.,16g,16a,8b,8a,8g,8f#,e,c6,2b.,16b,16c6,16b,16a,1b";
//const char song17[] PROGMEM = "VanessaMae:d=4,o=6,b=70:32c7,32b,16c7,32g,32p,32g,32p,32d#,32p,32d#,32p,32c,32p,32c,32p,32c7,32b,16c7,32g#,32p,32g#,32p,32f,32p,16f,32c,32p,32c,32p,32c7,32b,16c7,32g,32p,32g,32p,32d#,32p,32d#,32p,32c,32p,32c,32p,32g,32f,32d#,32d,32c,32d,32d#,32c,32d#,32f,16g,8p,16d7,32c7,32d7,32a#,32d7,32a,32d7,32g,32d7,32d7,32p,32d7,32p,32d7,32p,16d7,32c7,32d7,32a#,32d7,32a,32d7,32g,32d7,32d7,32p,32d7,32p,32d7,32p,32g,32f,32d#,32d,32c,32d,32d#,32c,32d#,32f,16c";
const char song18[] PROGMEM = "Verve:d=4,o=5,b=180:e,g,e,f,d,2f,a#,f,2a#,a,f,2a,p,e,g,e,f,d,2f,a#,f,2a#,a,f,2a,p";
const char song19[] PROGMEM = "Wannabe:d=4,o=5,b=125:16g,16g,16g,16g,8g,8a,8g,8e,8p,16c,16d,16c,8d,8d,8c,e,p,8g,8g,8g,8a,8g,8e,8p,c6,8c6,8b,8g,8a,16b,16a,g";
const char song20[] PROGMEM = "Yaketysax:d=4,o=5,b=125:8d.,16e,8g,8g,16e,16d,16a4,16b4,16d,16b4,8e,16d,16b4,16a4,16b4,8a4,16a4,16a#4,16b4,16d,16e,16d,g,p,16d,16e,16d,8g,8g,16e,16d,16a4,16b4,16d,16b4,8e,16d,16b4,16a4,16b4,8d,16d,16d,16f#,16a,8f,d,p,16d,16e,16d,8g,16g,16g,8g,16g,16g,8g,8g,16e,8e.,8c,8c,8c,8c,16e,16g,16a,16g,16a#,8g,16a,16b,16a#,16b,16a,16b,8d6,16a,16b,16d6,8b,8g,8d,16e6,16b,16b,16d,8a,8g,g";
const char song21[] PROGMEM = "StarWars:d=4,o=5,b=45:32p,32f#,32f#,32f#,8b.,8f#.6,32e6,32d#6,32c#6,8b.6,16f#.6,32e6,32d#6,32c#6,8b.6,16f#.6,32e6,32d#6,32e6,8c#.6,32f#,32f#,32f#,8b.,8f#.6,32e6,32d#6,32c#6,8b.6,16f#.6,32e6,32d#6,32c#6,8b.6,16f#.6,32e6,32d#6,32e6,8c#6";
const char song22[] PROGMEM = "StWars:d=4,o=5,b=180:8f,8f,8f,2a#.,2f.6,8d#6,8d6,8c6,2a#.6,f.6,8d#6,8d6,8c6,2a#.6,f.6,8d#6,8d6,8d#6,2c6,p,8f,8f,8f,2a#.,2f.6,8d#6,8d6,8c6,2a#.6,f.6,8d#6,8d6,8c6,2a#.6,f.6,8d#6,8d6,8d#6,2c6";
const char song23[] PROGMEM = "Cantina:d=4,o=5,b=250:8a,8p,8d6,8p,8a,8p,8d6,8p,8a,8d6,8p,8a,8p,8g#,a,8a,8g#,8a,g,8f#,8g,8f#,f.,8d.,16p,p.,8a,8p,8d6,8p,8a,8p,8d6,8p,8a,8d6,8p,8a,8p,8g#,8a,8p,8g,8p,g.,8f#,8g,8p,8c6,a#,a,g";
const char song24[] PROGMEM = "SWEnd:d=4,o=5,b=225:2c,1f,2g.,8g#,8a#,1g#,2c.,c,2f.,g,g#,c,8g#.,8c.,8c6,1a#.,2c,2f.,g,g#.,8f,c.6,8g#,1f6,2f,8g#.,8g.,8f,2c6,8c.6,8g#.,8f,2c,8c.,8c.,8c,2f,8f.,8f.,8f,2f";

const char *playList[] =
{
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
int currentPlay = 0;

char corrSec = 0;
bool corrApplied = 0;

#define EEPROM_ADDR_RADIO_INDEX       0
#define EEPROM_ADDR_RADIO_VOLUME      1
#define EEPROM_ADDR_ALARM_INDEX       2
#define EEPROM_ADDR_ALARM_WEEK        3
#define EEPROM_ADDR_ALARM_TIME_HOUR   4
#define EEPROM_ADDR_ALARM_TIME_MIN    5
#define EEPROM_ADDR_ALARM_TIME_SEC    6
#define EEPROM_ADDR_CORRECTION_SEC    7

void setup()
{
  Wire.begin();
  Serial.begin(115200);
  Serial.println(F("Initialize variables from EEPROM"));
  index       = EEPROM.read(EEPROM_ADDR_RADIO_INDEX);
  volume      = EEPROM.read(EEPROM_ADDR_RADIO_VOLUME);
  currentPlay = EEPROM.read(EEPROM_ADDR_ALARM_INDEX);
  alertWeek   = EEPROM.read(EEPROM_ADDR_ALARM_WEEK);
  int hour    = EEPROM.read(EEPROM_ADDR_ALARM_TIME_HOUR);
  int minute  = EEPROM.read(EEPROM_ADDR_ALARM_TIME_MIN);
  int second  = EEPROM.read(EEPROM_ADDR_ALARM_TIME_SEC);
  corrSec     = (char)EEPROM.read(EEPROM_ADDR_CORRECTION_SEC);
  alertTime = DateTime(2000, 1, 1, hour, minute, second);
  Serial.println(F("Initialize Buttons"));
  pinMode(controlPin, INPUT_PULLUP);
  attachInterrupt(1, switchmode, FALLING);
  pinMode(buttonPin1, INPUT_PULLUP);
  pinMode(buttonPin2, INPUT_PULLUP);
  pinMode(buttonPin3, INPUT_PULLUP);
  pinMode(buttonPin4, INPUT_PULLUP);
  Serial.println(F("Initialize Video"));
  lcd.begin(lcdRows, lcdLines);
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
  byte *p_item = (byte *)(radioList + index);
  long wave = (long)pgm_read_dword_near(p_item);
  MP1090S::SetStation(wave);
  MP1090S::SetVolume(volume);

  Serial.println(F("Initialize Date/Time"));
  rtc.begin();
  //rtc.adjust(DateTime(2000, 1, 1, 0, 0, 0));
}

void switchmode()
{
  noInterrupts();
  unsigned long t = millis();
  if (t - lasttime > 500)
  {
    switch (mode)
    {
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

void loop()
{
  switch (mode)
  {
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

void error(const char *text)
{
  Serial.println(text);
  lcd.clear();
  lcd.home();
  lcd.print(text);
  for (;;);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////
void loopClock()
{
  lcd.clear();
  while (mode == MODE_CLOCK)
  {
    if (checkAlarm()) break;
    radioButtons();

    DateTime now = rtc.now();

    char text[20];
    int  length = sprintf(text, "%2d %s %4d", now.day(), months[now.month() - 1], now.year());
    lcd.setCursor((lcdRows - length) >> 1, 0);
    lcd.print(text);

    if (checkAlarm()) break;
    radioButtons();

    sprintf(text, "%02d %02d", now.hour(), now.minute());

    if (checkAlarm()) break;
    radioButtons();

    lcd.setCursor(2, 2);
    showDigit_top(text[0]);
    showDigit_top(text[1]);
    lcd.write(0x20);
    showDigit_top(text[3]);
    showDigit_top(text[4]);

    if (checkAlarm()) break;
    radioButtons();

    lcd.setCursor(2, 3);
    showDigit_bottom(text[0]);
    showDigit_bottom(text[1]);
    lcd.write(0x20);
    showDigit_bottom(text[3]);
    showDigit_bottom(text[4]);
  }
}

void showDigit_top(char value)
{
  switch (value)
  {
    case '0':
      lcd.print(F("\x04""\x02""\x05 "));
      break;
    case '1':
      lcd.print(F("\x02""\x05""\x20 "));
      break;
    case '2':
      lcd.print(F("\x02""\x03""\x05 "));
      break;
    case '3':
      lcd.print(F("\x02""\x03""\x07 "));
      break;
    case '4':
      lcd.print(F("\x04""\x01""\xFF "));
      break;
    case '5':
      lcd.print(F("\x06""\x03""\x02 "));
      break;
    case '6':
      lcd.print(F("\x04""\x03""\x02 "));
      break;
    case '7':
      lcd.print(F("\x02""\x02""\x05 "));
      break;
    case '8':
      lcd.print(F("\x06""\x03""\x07 "));
      break;
    case '9':
      lcd.print(F("\x06""\x03""\x05 "));
      break;
    default:
      lcd.print(F("\x20""\x20""\x20 "));
  }
}

void showDigit_bottom(char value)
{
  switch (value)
  {
    case '0':
      lcd.print(F("\x06""\x01""\x07 "));
      break;
    case '1':
      lcd.print(F("\x01""\xFF""\x01 "));
      break;
    case '2':
      lcd.print(F("\x04""\x03""\x01 "));
      break;
    case '3':
      lcd.print(F("\x01""\x03""\x05 "));
      break;
    case '4':
      lcd.print(F("\x20""\x20""\xFF "));
      break;
    case '5':
      lcd.print(F("\x01""\x03""\x05 "));
      break;
    case '6':
      lcd.print(F("\x06""\x03""\x05 "));
      break;
    case '7':
      lcd.print(F("\x20""\x20""\xFF "));
      break;
    case '8':
      lcd.print(F("\x04""\x03""\x05 "));
      break;
    case '9':
      lcd.print(F("\x01""\x03""\x07 "));
      break;
    default:
      lcd.print(F("\x20""\x20""\x20 "));
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////
void loopAlarm()
{
  lcd.clear();

  lcd.setCursor(6, 0);
  lcd.print(F("\xA0\xA9\xE0\xA5\xA7""bH\xA5K"));

  char text[20];
  sprintf(text, "%02d %02d", alertTime.hour(), alertTime.minute());

  lcd.setCursor(2, 2);
  showDigit_top(text[0]);
  showDigit_top(text[1]);
  lcd.write(0x20);
  showDigit_top(text[3]);
  showDigit_top(text[4]);

  lcd.setCursor(2, 3);
  showDigit_bottom(text[0]);
  showDigit_bottom(text[1]);
  lcd.write(0x20);
  showDigit_bottom(text[3]);
  showDigit_bottom(text[4]);

  for (int count = 0; count < 1 && mode == MODE_ALARM; count ++)
  {
    const char *song = playList[currentPlay++];
    play_rtttl(song);
    // Пауза в 1 секунду
    for (int i = 0; i < 10 && mode == MODE_ALARM; i++) delay(100);
    // Сохраняем номер след. музыки
    if (currentPlay >= playListSize) currentPlay = 0;
    EEPROM.write(EEPROM_ADDR_ALARM_INDEX, currentPlay);
  }
  if (mode == MODE_ALARM)
  {
    if (volume == 0) volume = 5;
    showRadioVolume();
  }
  mode = MODE_CLOCK;
}

bool checkAlarm()
{
  DateTime now = rtc.now();
  int dayOfWeek = now.dayOfWeek();
  dayOfWeek = (dayOfWeek == 0) ? 6 : dayOfWeek - 1;

  if (now.hour() == alertTime.hour() && now.minute() == alertTime.minute() && now.second() == alertTime.second())
  {
    if (alertWeek & (1 << dayOfWeek))
    {
      mode = MODE_ALARM;
      return true;
    }
  }
  /////////////////////////////////////////////////////////////////
  // служебные события
  if (now.hour() == 23 && now.minute() == 0 && now.second() == 0)
  {
    if (volume > 0)
    {
      volume = 0;
      showRadioVolume();
    }
  }

  // коррекция времени
  if (corrSec != 0)
  {
    if (corrApplied)
    {
      if (now.hour() == 0 && now.minute() == 1 && now.second() == 0)
        corrApplied = 0;
    }
    else
    {
      if (corrSec > 0)
      {
        if (now.hour() == 0 && now.minute() == 0 && now.second() == 0)
        {
          rtc.adjust(DateTime(now.year(), now.month(), now.day(), now.hour(), now.minute(), corrSec));
          corrApplied = 1;
        }
      }
      else
      {
        if (now.hour() == 23 && now.minute() == 59 && now.second() == 59)
        {
          rtc.adjust(DateTime(now.year(), now.month(), now.day(), now.hour(), now.minute(), now.second() + corrSec));
          corrApplied = 1;
        }
      }
    }
  }
  /*
    if (now.hour() == 7 && now.minute() == 20 && now.second() == 20)
    {
      if ((31 & (1 << dayOfWeek)) && volume == 0)
      {
        volume = 5;
        showRadioVolume();
      }
    }

    if (now.hour() == 8 && now.minute() == 0 && now.second() == 0)
    {
      if ((31 & (1 << dayOfWeek)) && volume > 0)
      {
        volume = 0;
        showRadioVolume();
      }
    }
  */
  /////////////////////////////////////////////////////////////////

  return false;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////
void loopRadio()
{
  lcd.clear();
  lcd.setCursor(0, 1);
  lcd.print(F("--------------------"));
  lcd.setCursor(0, 3);
  lcd.print(F("\xA1po\xBC:"));

  showRadioStation();
  showRadioVolume();

  while (mode == MODE_RADIO)
  {
    if (checkAlarm()) break;
    radioButtons();
  }
}

void radioButtons()
{
  if (digitalRead(buttonPin1) == LOW)
  {
    volume --;
    showRadioVolume();
  }
  if (digitalRead(buttonPin2) == LOW)
  {
    volume ++;
    showRadioVolume();
  }
  if (digitalRead(buttonPin3) == LOW)
  {
    index --;
    showRadioStation();
  }
  if (digitalRead(buttonPin4) == LOW)
  {
    index ++;
    showRadioStation();
  }
}

void showRadioVolume()
{
  volume = constrain(volume, 0, 15);
  if (mode == MODE_RADIO)
  {
    int i;
    lcd.setCursor(5, 3);
    for (i = 0; i < volume; i++)
      lcd.print("\xFF");
    for (; i < 15; i++)
      lcd.print(" ");
  }
  MP1090S::SetVolume(volume);
  EEPROM.write(EEPROM_ADDR_RADIO_VOLUME, volume);
}

void showRadioStation()
{
  index = constrain(index, 0, listSize - 1);
  byte *p_item = (byte *)(radioList + index);
  if (mode == MODE_RADIO)
  {
    char c;
    byte *p_name = p_item + sizeof(long);
    char text[20];

    lcd.setCursor(0, 0);
    while ((c = (char)pgm_read_byte_near(p_name++)) != '\0')
      lcd.print(c);

    lcd.setCursor(0, 2);
    sprintf(text, "C\xBF""a\xBD\xE5\xB8\xC7 %2d \xB8\xB7 %d ", index + 1, listSize);
    lcd.print(text);
  }
  long wave = (long)pgm_read_dword_near(p_item);
  MP1090S::SetStation(wave);
  EEPROM.write(EEPROM_ADDR_RADIO_INDEX, index);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////
void loopSettings()
{
  // 0 - установка даты
  // 1 - установка времени
  // 2 - коррекция времени
  // 3 - будильник
  int selected = 0;

  showSettingsInit(selected);
  while (mode == MODE_SETTING)
  {
    if (digitalRead(buttonPin1) == LOW)
    {
      selected ++;
      selected = constrain(selected, 0, 3);
      showSettingsSelected(selected);
    }
    if (digitalRead(buttonPin2) == LOW)
    {
      selected --;
      selected = constrain(selected, 0, 3);
      showSettingsSelected(selected);
    }

    if (digitalRead(buttonPin3) == LOW || digitalRead(buttonPin4) == LOW)
    {
      switch (selected)
      {
        case 0:
          subselect_date();
          break;
        case 1:
          subselect_time();
          break;
        case 2:
          subselect_correct();
          break;
        case 3:
          subselect_alarm();
          break;
        default:
          break;
      }
      mode = MODE_SETTING;
      showSettingsInit(selected);
    }
  }
}

void showSettingsSelected(int selected)
{
  lcd.setCursor(0, 0);
  lcd.write(0x20);
  lcd.setCursor(0, 1);
  lcd.write(0x20);
  lcd.setCursor(0, 2);
  lcd.write(0x20);
  lcd.setCursor(0, 3);
  lcd.write(0x20);
  lcd.setCursor(0, selected);
  lcd.write('*');
}

void showSettingsInit(int selected)
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F(" \xA9""c\xBF""a\xBDo\xB3\xBA""a \xE3""a\xBF\xC3"));
  lcd.setCursor(0, 1);
  lcd.print(F(" \xA9""c\xBF""a\xBDo\xB3\xBA""a \xB3pe\xBC""e\xBD\xB8"));
  lcd.setCursor(0, 2);
  lcd.print(F(" Koppe\xBA\xE5\xB8\xC7 \xB3pe\xBC""e\xBD\xB8"));
  lcd.setCursor(0, 3);
  lcd.print(F(" \xA0y\xE3\xB8\xBB\xC4\xBD\xB8\xBA"));
  lcd.setCursor(0, selected);
  lcd.write('*');
}

boolean showDigitalEditor(char *text, int length, char space)
{
  bool result = false;
  int index  = 0;
  int x = (lcdRows - length) >> 1;

  lcd.clear();
  lcd.setCursor(x, 1);
  lcd.print(text);
  lcd.setCursor(6, 3);
  lcd.print(F("coxpa\xBD\xB8\xBF\xC4"));

  lcd.setCursor(x, 1);
  lcd.blink();

  while (mode == MODE_SETTING)
  {
    delay(200);
    if (digitalRead(buttonPin1) == LOW)
    {
      if (index < 0 || index > length - 1)
      {
        result = true;
        break;
      }
      char c = text[index] - 1;
      c = constrain(c, '0', '9');
      text[index] = c;
      lcd.write(c);
      lcd.setCursor(x + index, 1);
    }
    if (digitalRead(buttonPin2) == LOW)
    {
      if (index < 0 || index > length - 1)
      {
        result = true;
        break;
      }
      char c = text[index] + 1;
      c = constrain(c, '0', '9');
      text[index] = c;
      lcd.write(c);
      lcd.setCursor(x + index, 1);
    }

    if (digitalRead(buttonPin3) == LOW)
    {
      index --;
      if (index < 0)
      {
        if (index == -1)
        {
          lcd.setCursor(6, 3);
          continue;
        }
        else index = 0;
      }
      else while (text[index] == space) index --;
      lcd.setCursor(x + index, 1);
    }
    if (digitalRead(buttonPin4) == LOW)
    {
      index ++;
      if (index >= length)
      {
        if (index == length)
        {
          lcd.setCursor(6, 3);
          continue;
        }
        else index = length - 1;
      }
      else while (text[index] == space) index ++;
      lcd.setCursor(x + index, 1);
    }
  }
  lcd.noBlink();
  return result;
}

void subselect_date()
{
  DateTime now = rtc.now();

  char text[16];
  int  length = sprintf(text, "%04d %02d %02d", now.year(), now.month(), now.day());
  if (showDigitalEditor(text, length, ' '))
  {
    int year  = (text[0] - '0') * 1000 + (text[1] - '0') * 100 + (text[2] - '0') * 10 + (text[3] - '0');
    int month = (text[5] - '0') * 10 + (text[6] - '0');
    int day   = (text[8] - '0') * 10 + (text[9] - '0');
    byte maxDays[12] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (year >= 1900 && year < 2100 && month >= 1 && month <= 12 && day >= 1 && day <= 31)
    {
      if (maxDays[month - 1] >= day)
      {
        if (month != 2)
        {
          now = rtc.now();
          rtc.adjust(DateTime(year, month, day, now.hour(), now.minute(), now.second()));
          return;
        }
        else
        {
          boolean isleap = ((year % 4 == 0 and year % 100 != 0) or (year % 400 == 0));
          if (isleap || (!isleap && day <= 28))
          {
            now = rtc.now();
            rtc.adjust(DateTime(year, month, day, now.hour(), now.minute(), now.second()));
            return;
          }
        }
      }
    }
    tone(TONE_PIN, notes[1], 500);
  }
}
void subselect_time()
{
  DateTime now = rtc.now();

  char text[16];
  int  length = sprintf(text, "%02d:%02d:%02d", now.hour(), now.minute(), now.second());
  if (showDigitalEditor(text, length, ':'))
  {
    int hour   = (text[0] - '0') * 10 + (text[1] - '0');
    int minute = (text[3] - '0') * 10 + (text[4] - '0');
    int second = (text[6] - '0') * 10 + (text[7] - '0');
    if (hour >= 0 && hour <= 23 && minute >= 0 && minute <= 59 && second >= 0 && second <= 59)
    {
      now = rtc.now();
      rtc.adjust(DateTime(now.year(), now.month(), now.day(), hour, minute, second));
      return;
    }
    tone(TONE_PIN, notes[1], 500);
  }
}

void subselect_correct()
{
  int x = 1;
  int selected  = 0;
  char c = abs(corrSec) + '0';
  char sign = ' ';
  sign = (corrSec > 0) ? '+' : sign;
  sign = (corrSec < 0) ? '-' : sign;

  lcd.clear();

  lcd.setCursor(0, 1);
  lcd.print(F("Koppe\xBA\xE5\xB8\xC7 \xBD\x61:"));
  lcd.print(sign);
  lcd.print(c);
  lcd.print(F(" ce\xBA."));
  lcd.setCursor(6, 3);
  lcd.print(F("coxpa\xBD\xB8\xBF\xC4"));
  lcd.setCursor(10, 1);

  lcd.blink();

  while (mode == MODE_SETTING)
  {
    if (digitalRead(buttonPin1) == LOW)
    {
      selected ++;
      selected = constrain(selected, 0, 1);
    }
    if (digitalRead(buttonPin2) == LOW)
    {
      selected --;
      selected = constrain(selected, 0, 1);
    }
    if (digitalRead(buttonPin3) == LOW)
    {
      if (selected == 0)
      {
        corrSec = constrain(corrSec - 1, -9, 9);
        c = abs(corrSec) + '0';
        sign = ' ';
        sign = (corrSec > 0) ? '+' : sign;
        sign = (corrSec < 0) ? '-' : sign;
        lcd.setCursor(13, 1);
        lcd.print(sign);
        lcd.write(c);
      }
      else
      {
        EEPROM.write(EEPROM_ADDR_CORRECTION_SEC, corrSec);
        break;
      }
    }
    if (digitalRead(buttonPin4) == LOW)
    {
      if (selected == 0)
      {
        corrSec = constrain(corrSec + 1, -9, 9);
        c = abs(corrSec) + '0';
        sign = ' ';
        sign = (corrSec > 0) ? '+' : sign;
        sign = (corrSec < 0) ? '-' : sign;
        lcd.setCursor(13, 1);
        lcd.print(sign);
        lcd.write(c);
      }
      else
      {
        EEPROM.write(EEPROM_ADDR_CORRECTION_SEC, corrSec);
        break;
      }
    }
    x = (selected == 0) ? 14 : 6;
    lcd.setCursor(x, (selected << 1) + 1);
    delay(200);
  }
  lcd.noBlink();
}

void subselect_alarm()
{
  char text[16];
  int  length = sprintf(text, "%02d:%02d:%02d", alertTime.hour(), alertTime.minute(), alertTime.second());
  if (showDigitalEditor(text, length, ':'))
  {
    int hour   = (text[0] - '0') * 10 + (text[1] - '0');
    int minute = (text[3] - '0') * 10 + (text[4] - '0');
    int second = (text[6] - '0') * 10 + (text[7] - '0');
    if (hour >= 0 && hour <= 23 && minute >= 0 && minute <= 59 && second >= 0 && second <= 59)
    {
      char text[21] = "                    ";
      for (int i = 0; i < 7; i++)
        if (alertWeek & (1 << i))
        {
          text[i * 3] = '*';
          text[i * 3 + 1] = '*';
        }
      if (showWeekEditor(text))
      {
        alertWeek = 0;
        for (int i = 0; i < 7; i++)
          if (text[i * 3] == '*')
            alertWeek |= (1 << i);

        alertTime = DateTime(2000, 1, 1, hour, minute, second);
        EEPROM.write(EEPROM_ADDR_ALARM_WEEK, alertWeek);
        EEPROM.write(EEPROM_ADDR_ALARM_TIME_HOUR, hour);
        EEPROM.write(EEPROM_ADDR_ALARM_TIME_MIN, minute);
        EEPROM.write(EEPROM_ADDR_ALARM_TIME_SEC, second);
      }
      return;
    }
    tone(TONE_PIN, notes[1], 500);
  }
}

boolean showWeekEditor(char *text)
{
  bool result = false;
  int index  = 0;

  lcd.setCursor(0, 0);
  lcd.print(F("\xA8H BT CP \xABT \xA8T C\xA0 BC"));
  lcd.setCursor(0, 1);
  lcd.print(text);
  lcd.setCursor(6, 3);
  lcd.print(F("coxpa\xBD\xB8\xBF\xC4"));
  lcd.setCursor(0, 1);
  lcd.blink();

  while (mode == MODE_SETTING)
  {
    delay(200);
    if (digitalRead(buttonPin1) == LOW || digitalRead(buttonPin2) == LOW)
    {
      if (index < 0 || index > 19)
      {
        result = true;
        break;
      }
      char c = text[index] == ' ' ? '*' : ' ';
      text[index] = c;
      text[index + 1] = c;
      lcd.write(c);
      lcd.write(c);
      lcd.setCursor(index, 1);
    }

    if (digitalRead(buttonPin3) == LOW)
    {
      index -= 3;
      if (index < 0)
      {
        if (index == -3)
        {
          lcd.setCursor(6, 3);
          continue;
        }
        else index = 0;
      }
      lcd.setCursor(index, 1);
    }
    if (digitalRead(buttonPin4) == LOW)
    {
      index += 3;
      if (index > 18)
      {
        if (index == 21)
        {
          lcd.setCursor(6, 3);
          continue;
        }
        else index = 18;
      }
      lcd.setCursor(index, 1);
    }
  }
  lcd.noBlink();
  return result;
}

#define isdigit(n) (n >= '0' && n <= '9')

void play_rtttl(const char *song)
{
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
  if (pgm_read_byte_near(ptr) == 'd')
  {
    ptr++; ptr++;              // skip "d="
    num = 0;
    while (isdigit(pgm_read_byte_near(ptr)))
    {
      num = (num * 10) + (pgm_read_byte_near(ptr++) - '0');
    }
    if (num > 0) default_dur = num;
    ptr++;                   // skip comma
  }

  // get default octave
  if (pgm_read_byte_near(ptr) == 'o')
  {
    ptr++; ptr++;              // skip "o="
    num = pgm_read_byte_near(ptr++) - '0';
    if (num >= 3 && num <= 7) default_oct = num;
    ptr++;                   // skip comma
  }

  // get BPM
  if (pgm_read_byte_near(ptr) == 'b')
  {
    ptr++; ptr++;              // skip "b="
    num = 0;
    while (isdigit(pgm_read_byte_near(ptr)))
    {
      num = (num * 10) + (pgm_read_byte_near(ptr++) - '0');
    }
    bpm = num;
    ptr++;                   // skip colon
  }

  // BPM usually expresses the number of quarter notes per minute
  wholenote = (60 * 1000L / bpm) * 4;  // this is the time for whole note (in milliseconds)

  // now begin note loop
  while (mode == MODE_ALARM && pgm_read_byte_near(ptr))
  {
    // first, get note duration, if available
    num = 0;
    while (isdigit(pgm_read_byte_near(ptr)))
    {
      num = (num * 10) + (pgm_read_byte_near(ptr++) - '0');
    }

    if (num) duration = wholenote / num;
    else duration = wholenote / default_dur;  // we will need to check if we are a dotted note after

    // now get the note
    note = 0;

    switch (pgm_read_byte_near(ptr))
    {
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
    if (pgm_read_byte_near(ptr) == '#')
    {
      note++;
      ptr++;
    }

    // now, get optional '.' dotted note
    if (pgm_read_byte_near(ptr) == '.')
    {
      duration += duration / 2;
      ptr++;
    }

    // now, get scale
    if (isdigit(pgm_read_byte_near(ptr)))
    {
      scale = pgm_read_byte_near(ptr) - '0';
      ptr++;
    }
    else
    {
      scale = default_oct;
    }

    scale += OCTAVE_OFFSET;

    if (pgm_read_byte_near(ptr) == ',')
      ptr++;       // skip comma for next note (or we may be at the end)

    // now play the note

    if (note)
    {
      tone(TONE_PIN, notes[(scale - 4) * 12 + note]);
      delay(duration);
      noTone(TONE_PIN);
    }
    else
    {
      delay(duration);
    }
  }
}

