#include <Arduino.h>
#include <Wire.h>


#if !defined(ESP32)
  #error Select ESP32 DEV Board
#endif

#define TEA5767_ADR 0x60 // I2C address of TEA5767
#define QUARTZ 32768
#define FILTER 225000

#define REG_1 0x00
#define REG_1_MUTE  0x80
#define REG_1_SM    0x40
#define REG_1_PLL   0x3F

#define REG_2 0x01
#define REG_2_PLL   0xFF

#define REG_3 0x02
#define REG_3_MS   0x08
#define REG_3_SSL  0x60
#define REG_3_SUD  0x80

#define REG_4 0x03
#define REG_4_SMUTE 0x08
#define REG_4_XTAL  0x10
#define REG_4_BL    0x20
#define REG_4_STBY  0x40

#define REG_5 0x04
#define REG_5_PLLREF  0x80
#define REG_5_DTC     0x40

#define FIX_STATION 10170

uint8_t registers[5]; ///< registers for controlling the radio chip.

void setup() {
  // open the Serial port
  Serial.begin(115200);
  Serial.println("Radio...");
  delay(200);

  init();

  setFrequency(FIX_STATION);
  //radio.setMono(false);
}

void loop() {
/*
  char s[12];
  radio.formatFrequency(s, sizeof(s));
  Serial.print("Station:"); 
  Serial.println(s);
  
  Serial.print("Radio:"); 
  radio.debugRadioInfo();
  
  Serial.print("Audio:"); 
  radio.debugAudioInfo();
*/
  delay(3000);
} // loop

void init() {
  registers[0] = 0x00;
  registers[1] = 0x00;
  registers[2] = 0xB0;
  registers[3] = REG_4_XTAL | REG_4_SMUTE;
  registers[4] = 0;
  Wire.begin();

  //_freqLow = 8700;
  //_freqHigh = 10800;
  //_freqSteps = 10;
  registers[3] &= ~REG_4_BL;
} 

void setFrequency(uint16_t newF) {
  uint16_t frequencyB = 4 * (newF * 10000L + FILTER) / QUARTZ;
  Serial.println(frequencyB);

  registers[0] = frequencyB >> 8;
  registers[1] = frequencyB & 0XFF;
  saveRegisters();
  delay(100);
}

void saveRegisters()
{
  Wire.beginTransmission(TEA5767_ADR);
  for (uint8_t n = 0; n < sizeof(registers); n++) {
    Wire.write(registers[n]);
  }

  byte ack = Wire.endTransmission();
  if (ack != 0) { //We have a problem!
    Serial.print("Write Fail:"); //No ACK!
    Serial.println(ack, DEC); //I2C error: 0 = success, 1 = data too long, 2 = rx NACK on address, 3 = rx NACK on data, 4 = other error
  }
}
