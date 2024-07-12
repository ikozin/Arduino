#include <Arduino.h>
#include <Wire.h>

#if !defined(ESP32)
  #error Select ESP32 DEV Board
#endif

void setup() {
  Wire.begin();
  Serial.begin(57600);
  Serial.printf("\nI2C Scanner\n");
}

bool checkPort(int address) {
  Wire.beginTransmission(address);
  return Wire.endTransmission() == 0; 
}

void loop() {
  Serial.printf("\nScanning...\n");
  Serial.printf("    0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F\n");
  
  for (byte address = 0; address < 127; address++) {
    if ((address & 0x0F) == 0) Serial.printf("%02X ", address);

    if (address == 0) {
      Serial.printf("   ");
      continue;
    }

    if (checkPort(address)) {
      Serial.printf("%02X ", address);
    }
    else {
      Serial.printf("-- ");
    }
    if ((address & 0x0F) == 0x0F) Serial.printf("\n");
  }
  Serial.printf("\n");
  delay(5000);           // wait 5 seconds for next scan
}
