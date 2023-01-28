#include <Arduino.h>
#include <MAX7219Segment.h>

#define DIN 11
#define CLK 13
#define CS  5

MAX7219Segment display = MAX7219Segment(DIN, CS, CLK);

void setup() {
  display.setBright(10); // 1 - 15
  display.setDigitLimit(8);
  display.clear();
  // display.printDigit(-123, 4);
  // display.printDot(2);
  // display.printDigit(-456);
  // display.printDot(6);
}

void loop() {
  display.printDot(0);
  display.printDot(1);
  display.printDot(2);
  display.printDot(3);
  display.printDot(4);
  display.printDot(5);
  display.printDot(6);
  display.printDot(7);
  display.printDot(8);
  display.printDigit(0, 0);
  display.printDigit(0, 1);
  display.printDigit(0, 2);
  display.printDigit(0, 3);
  display.printDigit(0, 4);
  display.printDigit(0, 5);
  display.printDigit(0, 6);
  display.printDigit(0, 7);
  display.printDigit(0, 8);



}