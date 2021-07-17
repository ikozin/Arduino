#include <Wire.h>


void setup() {
  Wire.begin();
  Serial.begin(9600);
  Serial.println("\nI2C Scanner");
}

char text[80];
void loop() {
  Serial.println("\nScanning...");
  Serial.println("    0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F");
  
  for (byte address = 0; address < 127; address++) {
    if ((address & 0x0F) == 0) {
      sprintf(text, "%02X ", address);
      Serial.print(text);
    }

    if (address == 0) {
      Serial.print("   ");
      continue;
    }

    if (checkPort(address)) {
      sprintf(text, "%02X ", address);
      Serial.print(text);
    }
    else {
      Serial.print("-- ");
    }
    if ((address & 0x0F) == 0x0F) Serial.println();
  }
  Serial.println();
  delay(5000);           // wait 5 seconds for next scan
}

bool checkPort(int address) {
  Wire.beginTransmission(address);
  return Wire.endTransmission() == 0; 
}
