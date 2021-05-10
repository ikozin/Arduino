#include "rda5807m.h"

void radioSetRadio(uint8_t index) {
  byte *pData = (byte *)(radioList + index);
  uint16_t band = pgm_read_word(pData);
#if defined(DEBUG_CONSOLE)  
  char c;
  Serial.print(band);
  Serial.print(':');
  pData += sizeof(uint16_t);
  while ((c = (char)pgm_read_byte(pData++)) != 0) {
    Serial.print(c);
  }
  Serial.println();
#endif
  radioSetChannel(band);
}

void radioInit() {
  Wire.begin();
  
  rda_reg2_t reg2 = { .value = 0 };
  reg2.DMUTE = 1;
  reg2.DHIZ = 1;
  reg2.ENABLE = 1;
  reg2.BASS = 1;
  setRegister(RDA5807M_REG2, reg2.value);
  
  rda_reg5_t reg5 = { .value = 0 };
  reg5.LNA_PORT_SEL = 2;
  reg5.SEEKTH = 8;
  setRegister(RDA5807M_REG5, reg5.value);
  delay(1000);
}

void radioSetChannel(uint16_t value) {
  rda_reg3_t reg = { .value = 0 };
  reg.CHAN = value - RADIO_BAND_MIN;
  reg.TUNE = 1;
  reg.BAND = RADIO_BAND_WIDTH; //00 - 87..108МГц, 01 - 76..91МГц, 10 - 76..108МГц, 11 - 65..76МГц или 50..65МГц (определяется битом 65M_50M MODE регистра 07h)
  setRegister(RDA5807M_REG3, reg.value);
  waitTune();
  delay(200);
}

uint16_t radioGetChannel() {
  rda_reg3_t reg = { .value = getRegister(RDA5807M_REG3) };
  return reg.CHAN + RADIO_BAND_MIN;
}

void radioSetVolume(uint8_t value) {
#if defined(DEBUG_CONSOLE)  
  Serial.print(F("Volume = "));
  Serial.println(value);
#endif
  rda_reg5_t reg = { .value = getRegister(RDA5807M_REG5) };
  reg.VOLUME = value;
  setRegister(RDA5807M_REG5, reg.value);
  delay(100);
}

uint8_t radioGetVolume() {
  rda_reg5_t reg = { .value = getRegister(RDA5807M_REG5) };
  return reg.VOLUME;
}

void radioSetMute(bool value) {
  rda_reg2_t reg = { .value = getRegister(RDA5807M_REG2) };
  reg.DMUTE = !value;
  setRegister(RDA5807M_REG2, reg.value);
}

bool radioGetMute() {
  rda_reg2_t reg = { .value = getRegister(RDA5807M_REG2) };
  return reg.DMUTE == 0;
}

void radioSetHardMute(bool value) {
  rda_reg2_t reg = { .value = getRegister(RDA5807M_REG2) };
  reg.DHIZ = !value;
  setRegister(RDA5807M_REG2, reg.value);
}

bool radioGetHardMute() {
  rda_reg2_t reg = { .value = getRegister(RDA5807M_REG2) };
  return reg.DHIZ == 0;
}

uint8_t radioGetRssi() {
  rda_regb_t reg;
  reg.value = getRegister(RDA5807M_REGB);
  return reg.RSSI;  
}

void waitTune() {
  rda_rega_t reg;
  do {
    reg.value = getRegister(RDA5807M_REGA);
  } while (reg.STC == 0);
}

uint16_t getRegister(uint8_t reg) {
  uint16_t result;
  Wire.beginTransmission(RDA5807M_RANDOM_ACCESS_ADDRESS);
  Wire.write(reg);
  Wire.endTransmission(false);
  Wire.requestFrom((uint16_t)RDA5807M_RANDOM_ACCESS_ADDRESS, (uint8_t)2, true);
  result = (uint16_t)Wire.read() << 8;
  result |= Wire.read();
  return result;
}

void setRegister(uint8_t reg, const uint16_t value) {
#if defined(DEBUG_CONSOLE)  
  char text[128];
  sprintf(text, "0x%02X = 0x%04X", reg, value);
  Serial.println(text);
#endif
  Wire.beginTransmission(RDA5807M_RANDOM_ACCESS_ADDRESS);
  Wire.write(reg);
  Wire.write(highByte(value));
  Wire.write(lowByte(value));
  Wire.endTransmission(true);
}
