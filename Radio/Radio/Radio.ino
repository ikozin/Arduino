/*
Arduino Pro Mini
 -----------------------
| *   *   *   *   *   * |
|GND CTS VCC RXI TXD DTR|
 -----------------------

I2C
MP1090S_ADDRESS     0x10
MCP23008_ADDRESS    0x20
DS1307_ADDRESS      0x68

*/
#include <Wire.h>
#include "MP1090S.h"
#include "Radio.h"


#define sizeofarray(a)  (sizeof(a)/sizeof(a[0]))

unsigned long lasttime = 0; // время последнего срабатывания прерывания, для исключения дребезга и мнгновенного срабатывания несколько раз.

const int radioSEN = 8;
const int radioRST = 9;

LiquidCrystal_I2C lcd(0);

RTC_DS1307 rtc;

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

// Важно: русские буквы, видимо в unicode, так как массив с ними переполнен, да и вывод их не совпадает (кодировка)
const RadioItem radioList[] PROGMEM =
{
  { 87500, "Business FM     87,5"},                                       // 0 - Business FM
  { 87900, "C\xB8\xBF\xB8-FM         87,9"},                              // 1 - Сити-FM
  { 88300, "Pe\xBFpo FM        88,3"},                                    // 2 - Ретро FM
  { 88700, "\xB0\xBCop FM         88,7"},                                 // 3 - Юмор FM
  { 89100, "Pa\xE3\xB8o Jazz      89,1"},                                 // 4 - Радио Jazz
  { 89500, "Megapolis FM    89,5"},                                       // 5 - Megapolis FM
  { 89900, "Ke\xBA""c FM         89,9"},                                  // 6 - Кекс FM
  { 90300, "A\xB3\xBFopa\xE3\xB8o       90,3"},                           // 7 - Авторадио
  { 90800, "Relax FM        90,8"},                                       // 8 - Relax FM
  { 91200, "\xAFxo Moc\xBA\xB3\xC3      91,2"},                           // 9 - Эхо Москвы
  { 91600, "Pa\xE3\xB8o Ky\xBB\xC4\xBFypa  91,6"},                        //10 - Радио Культура
  { 92000, "Moc\xBA\xB3""a FM       92,0"},                               //11 - Москва FM
  { 92400, "Pa\xE3\xB8o \xE0""a\xC0""a      92,4"},                       //12 - Радио Дача
  { 92800, "Pa\xE3\xB8o Kap\xBD""a\xB3""a\xBB  92,8"},                    //13 - Радио Карнавал
  { 93200, "C\xBEop\xBF FM        93,2"},                                 //14 - Спорт FM
  { 93600, "Ko\xBC\xBC""epca\xBD\xBF\xC2 FM  93,6"},                      //15 - Коммерсант FM
  { 94000, "Boc\xBFo\xBA FM       94,0"},                                 //16 - Восток FM
  { 94400, "Bec\xBD""a FM        94,4"},                                  //17 - Весна FM
  { 94800, "\xA1o\xB3op\xB8\xBF Moc\xBA\xB3""a  94,8"},                   //18 - Говорит Москва
  { 95200, "Rock FM         95,2"},                                       //19 - Rock FM
  { 95600, "Pa\xE3\xB8o \xA4\xB3""e\xB7\xE3""a    95,6"},                 //20 - Радио Звезда
  { 96000, "\xE0opo\xB6\xBDoe pa\xE3\xB8o  96,0"},                        //21 - Дорожное радио
  { 96400, "Ta\xBA""c\xB8 FM        96,4"},                               //22 - Такси FM
  { 96800, "\xE0""e\xBF""c\xBAoe pa\xE3\xB8o   96,8"},                    //23 - Детское радио
  { 97200, "Pa\xE3\xB8o K\xA8        97,2"},                              //24 - Радио КП
  { 97600, "Bec\xBF\xB8 FM        97,6"},                                 //25 - Вести FM
  { 98000, "Pa\xE3\xB8o \xACo\xBAo\xBB""a\xE3   98,0"},                   //26 - Радио Шоколад
  { 98400, "Pa\xE3\xB8o Pe\xBAop\xE3    98,4"},                           //27 - Радио Рекорд
  { 98800, "Pa\xE3\xB8o Romantika 98,8"},                                 //28 - Радио Romantika
  { 99200, "Pa\xE3\xB8o Op\xAA""e\xB9     99,2"},                         //29 - Радио Орфей
  { 99600, "C\xBFo\xBB\xB8\xE5""a FM      99,6"},                         //30 - Столица FM
  {100100, "Cepe\xB2p\xC7\xBD\xC3\xB9 \xE3o\xB6\xE3\xC4    "},            //31 - Серебряннй дождь
  {100500, "Best FM        100,5"},                                       //32 - Best FM
  {100900, "Pa\xE3\xB8o Classic  100,9"},                                 //33 - Радио Classic
  {101200, "DFM            101,2"},                                       //34 - DFM
  {101700, "Ha\xC1""e pa\xE3\xB8o     101,7"},                            //35 - Наше Радио
  {102100, "Mo\xBD\xBF""e-Kap\xBBo    102,1"},                            //36 - Монте-Карло
  {102500, "Comedy Radio   102,5"},                                       //37 - Comedy Radio
  {103000, "\xAC""a\xBD""co\xBD         103,0"},                          //38 - Шансон
  {103400, "Ma\xC7\xBA           103,4"},                                 //39 - Маяк
  {103700, "Maximum        103,7"},                                       //40 - Maximum
  {104200, "NRJ            104,2"},                                       //41 - NRJ
  {104700, "Pa\xE3\xB8o 7        104,7"},                                 //42 - Радио 7
  {105200, "Moscow FM      105,2"},                                       //43 - Moscow FM
  {105700, "Pycc\xBAoe pa\xE3\xB8o  105,7"},                              //44 - Русское радио
  {106200, "E\xB3po\xBE""a \xA8\xBB\xC6""c    106,2"},                    //45 - Европа Плюс
  {106600, "Love Radio     106,6"},                                       //46 - Love Radio
  {107000, "PCH            107,0"},                                       //47 - PCH
  {107400, "X\xB8\xBF FM         107,4"},                                 //48 - Хит FM
  {107800, "M\xB8\xBB\xB8\xE5""e\xB9""c\xBA""a\xC7 \xB3o\xBB\xBD""a   "}, //49 - Милицейская волна
};
const int listSize = sizeof(radioList) / sizeof(RadioItem);

int volume = 10;  // громкость
int index = 35;   // индекс радиостанции

AlarmItem *pCurrentAlarm = NULL;
AlarmItem alarmOn[4] =
{
  {
    .week = FLAG_WORK_WEEK,
    .hour = 7,
    .minute = 10,
    .second = 0
  },
  {
    .week = FLAG_SATURDAY | FLAG_SUNDAY,
    .hour = 9,
    .minute = 0,
    .second = 0
  },  
  {
    .week = 0,
    .hour = 0,
    .minute = 0,
    .second = 0
  },
  {
    .week = 0,
    .hour = 0,
    .minute = 0,
    .second = 0
  },
};

AlarmItem alarmOff[4] =
{
  {
    .week = FLAG_WORK_WEEK | FLAG_SATURDAY | FLAG_SUNDAY,
    .hour = 23,
    .minute = 0,
    .second = 0
  },
  {
    .week = FLAG_WORK_WEEK,
    .hour = 7,
    .minute = 20,
    .second = 0
  },
  {
    .week = FLAG_SATURDAY | FLAG_SUNDAY,
    .hour = 10,
    .minute = 0,
    .second = 0
  },
  {
    .week = 0,
    .hour = 0,
    .minute = 0,
    .second = 0
  },
};

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

// Melodies.h
const int playListSize = sizeof(playList) / sizeof(char*);
int currentPlay = 0;

int8_t corrSec = 0;
bool corrApplied = 0;

void setup()
{
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
  pinMode(buttonPin1, INPUT_PULLUP);
  pinMode(buttonPin2, INPUT_PULLUP);
  pinMode(buttonPin3, INPUT_PULLUP);
  pinMode(buttonPin4, INPUT_PULLUP);
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
  byte *p_item = (byte *)(radioList + index);
  long wave = (long)pgm_read_dword_near(p_item);
  MP1090S::SetStation(wave);
  MP1090S::SetVolume(volume);

  Serial.println(F("Initialize Date/Time"));
  rtc.begin();
  //rtc.adjust(DateTime(2000, 1, 1, 0, 0, 0));
  
  //saveAlarmData(EEPROM_ADDR_ALARM_ON1,  &alarmOn[0]);
  //saveAlarmData(EEPROM_ADDR_ALARM_ON2,  &alarmOn[1]);
  //saveAlarmData(EEPROM_ADDR_ALARM_ON3,  &alarmOn[2]);
  //saveAlarmData(EEPROM_ADDR_ALARM_ON4,  &alarmOn[3]);
  //saveAlarmData(EEPROM_ADDR_ALARM_OFF1, &alarmOff[0]);
  //saveAlarmData(EEPROM_ADDR_ALARM_OFF2, &alarmOff[1]);
  //saveAlarmData(EEPROM_ADDR_ALARM_OFF3, &alarmOff[2]);
  //saveAlarmData(EEPROM_ADDR_ALARM_OFF4, &alarmOff[3]);
  
  dumpInfo();
}

void dumpInfo()
{
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

void dumpInfoAlarm(AlarmItem *pAlarmData)
{
  char text[21];
  sprintf(text, "%02X, %02d:%02d:%02d", pAlarmData->week, pAlarmData->hour, pAlarmData->minute, pAlarmData->second);
  Serial.println(text);
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

  AlarmItem *pAlarmData = pCurrentAlarm;
  lcd.setCursor(6, 0);
  lcd.print(F("\xA0\xA9\xE0\xA5\xA7""bH\xA5K"));

  char text[20];
  sprintf(text, "%02d %02d", pAlarmData->hour, pAlarmData->minute);

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

bool checkAlarmTime(AlarmItem *pAlarmData, DateTime now, int dayOfWeek)
{
  if (pAlarmData->week & (1 << dayOfWeek))
  {
    if (now.hour() == pAlarmData->hour && now.minute() == pAlarmData->minute && now.second() == pAlarmData->second)
    {
      return true;
    }
  }
  return false;
}

bool checkAlarm()
{
  DateTime now = rtc.now();
  int dayOfWeek = now.dayOfWeek();
  dayOfWeek = (dayOfWeek == 0) ? 6 : dayOfWeek - 1;

  for (uint16_t i = 0; i < sizeof(alarmOn)/sizeof(alarmOn[0]); i++)
  {
    AlarmItem *pAlarmData = alarmOn + i;
    if (checkAlarmTime(pAlarmData, now, dayOfWeek))
    {
      pCurrentAlarm = pAlarmData;
      mode = MODE_ALARM;
      return true;
    }
  }
  for (uint16_t i = 0; i < sizeof(alarmOff)/sizeof(alarmOff[0]); i++)
  {
    AlarmItem *pAlarmData = alarmOff + i;
    if (checkAlarmTime(pAlarmData, now, dayOfWeek))
    {
      if (volume > 0)
      {
        volume = 0;
        showRadioVolume();
      }
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
