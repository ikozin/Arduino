#include <Arduino.h>

/*

DS9092L


Параметры
╔════════════════╦═════════╗
║ Протокол       ║ 1-Wire  ║
╠════════════════╬═════════╣
║ Питание        ║ 3V3, 5V ║
╚════════════════╩═════════╝

Распиновка
╔══════╦═══════╦═══════╦══════╗
║ DATA ║ LED-  ║ LED+  ║ GND  ║
╠══════╬═══════╬═══════╬══════╣
║GPIO* ║  GND  ║GPIO** ║ GND  ║
╚══════╩═══════╩═══════╩══════╝
* необходимо подтяжка к питанию 2.2 кОм
** необходим токоограничивающий резистор (maximum 20 mA DC at 2.7V typically)

https://mysku.club/blog/aliexpress/42027.html
https://habr.com/ru/articles/808553/
https://github.com/orgua/OneWireHub/blob/main/docs/source/device_support.md
https://wreckage.ru/protocol-ibutton-work-with-1-wire-in-arduino/
https://www.radiokot.ru/articles/13/
https://soltau.ru/index.php/arduino/item/394-kak-sdelat-kopiyu
https://usamodelkina.ru/14759-kak-sdelat-svoimi-rukami-kopirovalschik-kontaktnyh-i-beskontaktnyh-kljuchej-domofona.html

01:06:DA:0B:A0:00:00:0E:CRC: 0E
01:41:26:51:06:00:00:9D:CRC: 9D
01:93:CB:50:06:00:00:8E:CRC: 8E
01:BC:20:51:06:00:00:39:CRC: 39
01:D5:D6:06:06:00:00:08:CRC: 08

*/

#include <OneWire.h>

#define IBUTTON_PIN 32

OneWire ibutton (IBUTTON_PIN);
byte addr[8];
char text[128];

void setup() {
    Serial.begin(115200);
    Serial.println("Start");
    pinMode(IBUTTON_PIN, INPUT);
}

void loop() {
    delay(1000);
    if (ibutton.search(addr)) {

        for (byte x = 0; x < 8; x++) {
            sprintf(text, "%02X", addr[x]);
            Serial.print(text);
            Serial.print(":");
        }

        // Проверка контрольной суммы
        byte crc = ibutton.crc8(addr, 7);
        Serial.print("CRC: ");
        sprintf(text, "%02X", crc);
        Serial.print(text);
        Serial.println();

        ibutton.reset_search();
    }
}
