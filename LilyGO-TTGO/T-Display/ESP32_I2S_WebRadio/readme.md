# TTGO T-Display ESP32_I2S_WebRadio

https://zen.yandex.ru/media/id/5d5ff446998ed600ad85b50c/internetradio-esp32-na-dekodere-i2s-pcm5102-5f80c3a6109c65627ebb6ca0

https://github.com/espressif/arduino-esp32

https://docs.espressif.com/projects/esp-idf/en/latest/esp32/

https://diytech.ru/projects/spravochnik-po-raspinovke-esp32-kakie-vyvody-gpio-sleduet-ispolzovat

## Необходимые библиотеки

#### ESP32FS (SPIFFS)
[ESP32FS](https://github.com/me-no-dev/arduino-esp32fs-plugin/releases)
Плагин для Arduino IDE, загружает файлы из директории Data в ESP32 flash memory.
Подробнее: https://habr.com/ru/post/483280/

#### Графика
Используется локальная копия библиотеки TFT_eSPI https://github.com/Bodmer/TFT_eSPI, для устанвки выполнить **deploy_TFT_eSPI.cmd** (находится уровнем выше)

#### Кнопки
Библиотека https://github.com/LennartHennigs/Button2

#### Аудио
Библиотека https://github.com/schreibfaul1/ESP32-audioI2S

#### Время
Установка времени осуществляется через функцию **configTime**, она использует API ESP32 для работы с SNTP: 
https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/system/system_time.html

#### Энкодеры
Библиотека https://github.com/madhephaestus/ESP32Encoder/ основана на API ESP32

### Список радиостанций

- ~~Пополняемы список - https://esp-radio.ru/stream_list/~~
- Слушать радио онлайн - https://top-radio.ru/


