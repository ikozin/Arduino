# Radio Project Skill

## Описание проекта
FM-радиоприёмник на базе **Arduino Pro Mini** с модулем **MP1090S** (FM receiver), Buzzer и сенсорными кнопками **TTP223**.

## Стек технологий
- **MCU:** Arduino Pro Mini (ATmega328, 16MHz, 5V)
- **Framework:** Arduino
- **IDE/Build:** PlatformIO
- **Коммуникация:** Serial (115200 baud)

## Модули и периферия
| Модуль | Пин Arduino | Назначение |
|-|-|-|
| MP1090S | A0 (~SEN), A1 (~RST) | FM-радио модуль |
| BUZZER | D2 | Звуковая индикация |
| TTP223 | D8–D12 | Сенсорные кнопки (5 шт.) |

## Структура проекта
Radio/
├── platformio.ini
├── src/main.cpp              # Основная логика (1108 строк)
├── include/
│   ├── Radio.h               # Константы пинов, режимов
│   ├── Storage.h             # EEPROM storage (шаблонный класс)
│   ├── Melodies.h            # Частоты нот + 25 RTTTL мелодий
│   ├── strings.h             # строки в кодировке для диспея HD44780 (автогенерация)
│   └── menu_strings.h        # Маппинг строк меню
├── lib/
│   ├── GyverMenu/            # Библиотека меню
│   ├── video/                # LiquidCrystal_I2C, MCP23008 для дисплея HD44780
│   └── radio/                # MP1090S драйвер
├── scripts/
│   └── pre_build.py          # Генерация strings.h
├── strings.ini               # Источники строк (UTF-8 → кодировка для дисплея HD44780)
├── skill.md                  # Описание проекта
└── readme.md                 # Распиновка

## Зависимости (PlatformIO)
- `gyverlibs/StringN`
- `gyverlibs/GyverIO`
- `adafruit/RTClib@^2.1.4`

## Правила разработки
1. Все строки хранятся в `include/strings.h` и `include/menu_strings.h`
2. Настройки сохраняются через `Storage.h`
3. Меню реализовано через сенсорные кнопки TTP223 (D8–D12)
4. Не удалять прескрипт `scripts/pre_build.py`
5. Код должен быть оптимизирован по памяти (ATmega328: 32KB Flash, 2KB SRAM)

## Важные замечания
- MP1090S управляется через аналоговые пины A0/A1
- Buzzer подключён к пину D2
- Сенсорные кнопки используют активный низкий уровень
