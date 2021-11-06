#include "GameBoard.h"
#include "TestBoard.h"

boolean TestBoard::init() {
  return true;
}

boolean TestBoard::loop() {
  return true;
}

void TestBoard::clickButtonA() {
  Serial.println("A");
}

void TestBoard::clickButtonB() {
  Serial.println("B");
}

void TestBoard::clickButtonC() {
  Serial.println("Center");
}

void TestBoard::clickButtonU() {
  Serial.println("Up");
}

void TestBoard::clickButtonD() {
  Serial.println("Down");
}

void TestBoard::clickButtonL() {
  Serial.println("Left");
}
void TestBoard::clickButtonR() {
  Serial.println("Right");
}
