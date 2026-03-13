# Добавление в PlatformIO поддержки ATTinyCore (ATTiny85)

## Репозиторий на GitHub: https://github.com/SpenceKonde/ATTinyCore

## ***ВАЖНО: ATTiny85 должен содержать загрузчик ATTinyCore: ATtiny45/85 (Optiboot)***

Описание настроек PlatformIO для Arduino ISP
https://docs.platformio.org/en/latest/platforms/atmelavr.html#upload-using-programmer

добавляем в **platformio.ini** следующие настройки
```
upload_protocol = custom
upload_port = COM7
upload_speed = 19200
upload_flags =
    -C
    ; use "tool-avrdude-megaavr" for the atmelmegaavr platform
    ${platformio.packages_dir}/tool-avrdude/avrdude.conf
    -p
    $BOARD_MCU
    -P
    $UPLOAD_PORT
    -b
    $UPLOAD_SPEED
    -c
    stk500v1
upload_command = avrdude $UPLOAD_FLAGS -U flash:w:$SOURCE:i
```
Дополнительная информация:

https://community.platformio.org/t/burn-bootloader-to-attiny85-via-arduinoasisp/662/15
