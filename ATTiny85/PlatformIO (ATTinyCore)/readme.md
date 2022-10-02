# ���������� � PlatformIO ��������� ATTinyCore (ATTiny85)

## ����������� �� GitHub: https://github.com/SpenceKonde/ATTinyCore

## ***�����: ATTiny85 ������ ��������� ��������� ATTinyCore: ATtiny45/85 (Optiboot)***

�������� �������� PlatformIO ��� Arduino ISP
https://docs.platformio.org/en/latest/platforms/atmelavr.html#upload-using-programmer

��������� � **platformio.ini** ��������� ���������
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
�������������� ����������:

https://community.platformio.org/t/burn-bootloader-to-attiny85-via-arduinoasisp/662/15
