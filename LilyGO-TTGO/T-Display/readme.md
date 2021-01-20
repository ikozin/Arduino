# TTGO T-Display

Git: https://github.com/Xinyuan-LilyGO/TTGO-T-Display


https://github.com/espressif/arduino-esp32
https://docs.espressif.com/projects/esp-idf/en/latest/esp32/
https://www.sites.google.com/site/jmaathuis/arduino/lilygo-ttgo-t-display-esp32

## Настройка Arduino IDE
Настройка менеджера плат в Arduino IDE
https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
![setting](./setting.png "Настройки")
## Необходимые библиотеки
Библиотеки Arduino IDE: **"%USERPROFILE%\Documents\Arduino\libraries\"**
### [Button2](https://github.com/LennartHennigs/Button2)
![button2](./button2.png "Button2")
### [TFT_eSPI](https://github.com/ikozin/Arduino/tree/master/LilyGO-TTGO/T-Display/TFT_eSPI/)
Оригинал библиотеки https://github.com/Bodmer/TFT_eSPI, подготовленная для T-Display https://github.com/Xinyuan-LilyGO/TTGO-T-Display/tree/master/TFT_eSPI/. Копия [TFT_eSPI](https://github.com/ikozin/Arduino/tree/master/LilyGO-TTGO/T-Display/TFT_eSPI/) (на 19 января 2021) 
## Выбор платы в Arduino IDE
![menu](./menu.png "menu")
## Скетч
Перед компиляцией необходимо установить локальную библиотеку **TFT_eSPI**,
для этого необходимо выполнить скрипт **deploy_TFT_eSPI.cmd**
После компиляции её нужно удалить выполнив скрипт **remove_TFT_eSPI.cmd**.
Скетч: [TTGO-T-Display.ino](https://github.com/ikozin/Arduino/tree/master/LilyGO-TTGO/T-Display/TTGO-T-Display/)

## CP2104 USB to UART Bridge Controller
Website: https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers

Скачать: [CP210x Universal Windows Driver](https://www.silabs.com/documents/public/software/CP210x_Universal_Windows_Driver.zip)
