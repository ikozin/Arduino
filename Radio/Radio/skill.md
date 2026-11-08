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
     ├── platformio.ini # Конфиг PlatformIO
     ├── src/
     │      └── main.cpp # Основной файл
     ├── include/
     │          ├── Radio.h # Заголовки радиомодуля
     │          ├── Storage.h # Хранение настроек
     │          ├── Melodies.h # Мелодии/звуки
     │          ├── strings.h # Строковые ресурсы
     │          └── menu_strings.h # Строки меню
     ├── lib/ # Пользовательские библиотеки
     ├── include/ # Инклуд-пути
     └── scripts/
                └── pre_build.py # Прескрипт сборки

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
