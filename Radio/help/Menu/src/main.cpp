/*
Advanced Memory Usage is available via "PlatformIO Home > Project Inspect"
RAM:   [=====     ]  47.1% (used 964 bytes from 2048 bytes)
Flash: [====      ]  40.7% (used 12498 bytes from 30720 bytes)

RAM:   [====      ]  37.9% (used 776 bytes from 2048 bytes)
Flash: [=====     ]  45.2% (used 13874 bytes from 30720 bytes)
*/

#include <Arduino.h>
#include <Wire.h>
#include <StringN.h>
#include <GyverMenu.h>
#include <LiquidCrystal_I2C.h>
#include <MCP23008.h>

#ifndef ARDUINO_AVR_PRO
#error Select board: Arduino Pro Mini 
#endif

const int lcdLines = 4;
const int lcdRows = 20;

LiquidCrystal_I2C lcd(0);

String64 text; 

const int pinControl = 3;
const int pinUp = 4;
const int pinDown = 5;
const int pinLeft = 6;
const int pinRight = 7;
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
GyverMenu menu(lcdRows, lcdLines);

byte _L1[8] = { B00000, B00000, B00000, B00000, B00000, B11111, B11111, B11111 };
byte _L2[8] = { B11111, B11111, B11111, B00000, B00000, B00000, B00000, B00000 };
byte _L3[8] = { B11111, B11111, B11111, B00000, B00000, B00000, B11111, B11111 };
byte _B1[8] = { B00111, B01111, B11111, B11111, B11111, B11111, B11111, B11111 };
byte _B2[8] = { B11100, B11110, B11111, B11111, B11111, B11111, B11111, B11111 };
byte _B3[8] = { B11111, B11111, B11111, B11111, B11111, B11111, B01111, B00111 };
byte _B4[8] = { B11111, B11111, B11111, B11111, B11111, B11111, B11110, B11100 };

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
const uint8_t dayInMonth[] = {
    31,
    28,
    31,
    30,
    31,
    30,
    31,
    31,
    30,
    31,
    30,
    31,
};

typedef struct _DEVICE_SETTING_ALARM_ {
    bool state;
    bool Monday;
    bool Tuesday;
    bool Wednesday;
    bool Thursday;
    bool Friday;
    bool Saturday;
    bool Sunday;
    uint8_t hour;
    uint8_t minute;
    uint8_t mode;
    uint8_t volume;
    uint8_t radio;
} DEVICE_SETTING_ALARM;
#define ALARM_SIZE  (6)
DEVICE_SETTING_ALARM    alarm[ALARM_SIZE] = {
    {
        .state = true,
        .Monday = true,
        .Tuesday = true,
        .Wednesday = true,
        .Thursday = true,
        .Friday = true,
        .Saturday = true,
        .Sunday = true,
        .hour = 23,
        .minute = 0,
        .mode = 0,
        .volume = 0,
        .radio = 0,
    },
    {
        .state = true,
        .Monday = true,
        .Tuesday = true,
        .Wednesday = true,
        .Thursday = true,
        .Friday = true,
        .Saturday = false,
        .Sunday = false,
        .hour = 8,
        .minute = 0,
        .mode = 1,
        .volume = 4,
        .radio = 30    
    },
    {
        .state = true,
        .Monday = false,
        .Tuesday = false,
        .Wednesday = false,
        .Thursday = false,
        .Friday = false,
        .Saturday = true,
        .Sunday = true,
        .hour = 10,
        .minute = 0,
        .mode = 1,
        .volume = 4,
        .radio = 30    
    }
};

DEVICE_SETTING_ALARM* alarm1 = &alarm[0];
DEVICE_SETTING_ALARM* alarm2 = &alarm[1];
DEVICE_SETTING_ALARM* alarm3 = &alarm[2];
DEVICE_SETTING_ALARM* alarm4 = &alarm[3];
DEVICE_SETTING_ALARM* alarm5 = &alarm[4];
DEVICE_SETTING_ALARM* alarm6 = &alarm[5];


uint16_t year = 2026;
uint8_t month = 1;
uint8_t day = 1;

uint8_t hour = 0;
uint8_t minute = 0;
uint8_t second = 0;


void actionExit() {
    Serial.println("actionExit");
}

void actionDateSave() {
    menu.back();
}

void actionTimeSave() {
    menu.back();
}

void actionAlarmSave() {
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

void setup() {
    Serial.begin(115200);

    pinMode(pinControl, INPUT_PULLUP);
    pinMode(pinUp, INPUT_PULLUP);
    pinMode(pinDown, INPUT_PULLUP);
    pinMode(pinLeft, INPUT_PULLUP);
    pinMode(pinRight, INPUT_PULLUP);

    Wire.begin();
    Wire.setClock(400000);  // По умолчанию 100000 = 981, при 400000 = 385 
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
            b.ValueInt<uint16_t>("\xA1""o\xE3", &year, 2020, 2090, 1, DEC, "");
            b.ValueInt<uint8_t>("Mec\xC7\xE5", &month, 1, 12, 1, DEC, "");
            b.ValueInt<uint8_t>("\xE0""e\xBD\xC4", &day, 1, 31, 1, DEC, "");
            b.Button(F("Coxpa\xBD\xB8\xBF\xC4"), actionDateSave);  // "Сохранить"
        });
        b.Page(GM_NEXT, F("Bpe\xBC\xC7"), [](gm::Builder& b) {     // Время
            b.ValueInt<uint8_t>("\xAB""ac", &hour, 1, 23, 1, DEC, "");
            b.ValueInt<uint8_t>("M\xB8\xBDy\xBF""a", &minute, 1, 59, 1, DEC, "");
            b.ValueInt<uint8_t>("Ce\xBAy\xBD\xE3""a", &second, 1, 59, 1, DEC, "");
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

    menu.refresh();
}

void loop() {
  if (digitalRead(pinControl) == LOW) {
      menu.set();
  }
  if (digitalRead(pinUp) == LOW) {
      menu.up();
  }
  if (digitalRead(pinDown) == LOW) {
      menu.down();
  }
  if (digitalRead(pinLeft) == LOW) {
      menu.left();
  }
  if (digitalRead(pinRight) == LOW) {
      menu.right();
  }
  delay(100);
}
