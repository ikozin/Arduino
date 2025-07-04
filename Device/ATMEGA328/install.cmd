@ECHO OFF
IF EXIST "%HOMEDRIVE%\.platformio\platforms\atmelavr\boards" XCOPY "ATmega328P_BB_8Mhz.json" "%HOMEDRIVE%\.platformio\platforms\atmelavr\boards\" /Y
IF EXIST "%HOMEPATH%\.platformio\platforms\atmelavr\boards" XCOPY "ATmega328P_BB_8Mhz.json" "%HOMEPATH%\.platformio\platforms\atmelavr\boards\" /Y
PAUSE
