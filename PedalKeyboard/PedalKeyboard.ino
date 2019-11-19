/*

https://compacttool.ru/viewtovar.php?id=683

На плате Pro Micro нет светодиода подключенного к 13 пину
             ---------------------
      TX 0  | TX0             RAW | (7-12V)
      RX 1  | RX1             GND |
            | GND             RST |    RST
            | GND             VCC |
     SDA 2  | 2                A3 | 21 A3
 PWM SCL 3  | 3                A2 | 20 A2
      A6 4  | 4                A1 | 19 A1
 PWM     5  | 5                A0 | 18 A0
 PWM  A7 6  | 6   ---    ---   15 | 15 SCLK
         7  | 7  |RX-|  |TX-|  14 | 14 MISO
      A8 8  | 8  |LED|  |LED|  16 | 16 MOSI
 PWM  A9 9  | 9   ---    ---   10 | 10 A10  PWM
             ---------------------

Помигать можно так
const int LED_RX = 17;
const int LED_TX = 24;

void setup()
{
  Serial.begin(9600);
  pinMode(LED_RX, OUTPUT);
}
void loop()
{
  Serial.println ("Hello World!");
  digitalWrite(LED_RX, LOW);
  delay(1000);
  digitalWrite(LED_RX, HIGH);
  delay(1000);
}

*/

#include <Keyboard.h>

void setup()
{
  // initialize control over the keyboard:
  Keyboard.begin();
}

void loop()
{
  delay(5000);
  //Keyboard.print("Hello World!");

  // CTRL-ALT-DEL:
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press(KEY_LEFT_ALT);
  Keyboard.press(KEY_DELETE);
  delay(100);
  Keyboard.releaseAll();
  // Enter
  delay(1000);
  Keyboard.write(KEY_RETURN);
  while (1) {}
}
