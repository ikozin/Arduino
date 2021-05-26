#include "rda5807m.h"

SemaphoreHandle_t _mutexRadio;

void radioInit() {
  debug_printf("radioInit\r\n");
  Wire.begin();
  _mutexRadio = xSemaphoreCreateMutex();
  xSemaphoreTake(_mutexRadio, portMAX_DELAY);

  rda_reg2_t reg2 = { .value = 0 };
  reg2.ENABLE = 1;
  reg2.NEW_METHOD = 1;
  reg2.BASS = 1;
  reg2.MONO = 1;
  reg2.DMUTE = 1;
  reg2.DHIZ = 1;
  setRegister(RDA5807M_REG2, reg2.value);

  rda_reg4_t reg4 = { .value = 0 };
  reg4.DE = 1;
  setRegister(RDA5807M_REG4, reg4.value);

  rda_reg5_t reg5 = { .value = 0 };
  reg5.LNA_PORT_SEL = 2;
  reg5.SEEKTH = 8;
  setRegister(RDA5807M_REG5, reg5.value);

  rda_reg7_t reg7 = { .value = 0 };
  reg7.SOFTBLEND_EN = 1;
  reg7.TH_SOFRBLEND = 4;
  setRegister(RDA5807M_REG7, reg7.value);

  vTaskDelay(1000 / portTICK_RATE_MS);
  xSemaphoreGive(_mutexRadio);
}

void radioSetChannel(uint16_t value) {
  debug_printf("radioSetChannel\r\n");
  xSemaphoreTake(_mutexRadio, portMAX_DELAY);
  rda_reg3_t reg3 = { .value = 0 };
  reg3.SPACE = 0;
  reg3.BAND = RADIO_BAND_WIDTH; //00 - 87..108МГц, 01 - 76..91МГц, 10 - 76..108МГц, 11 - 65..76МГц или 50..65МГц (определяется битом 65M_50M MODE регистра 07h)
  reg3.TUNE = 1;
  reg3.CHAN = value - RADIO_BAND_MIN;
  setRegister(RDA5807M_REG3, reg3.value);
  vTaskDelay(200 / portTICK_RATE_MS);
  waitTune();
  xSemaphoreGive(_mutexRadio);
}

uint16_t radioGetChannel() {
  debug_printf("radioGetChannel\r\n");
  xSemaphoreTake(_mutexRadio, portMAX_DELAY);
  rda_reg3_t reg3 = { .value = getRegister(RDA5807M_REG3) };
  xSemaphoreGive(_mutexRadio);
  return reg3.CHAN + RADIO_BAND_MIN;
}

void radioSetVolume(uint16_t value) {
  debug_printf("radioSetVolume\r\nVolume = %d\r\n", value);
  xSemaphoreTake(_mutexRadio, portMAX_DELAY);
  rda_reg5_t reg5 = { .value = getRegister(RDA5807M_REG5) };
  reg5.VOLUME = value;
  setRegister(RDA5807M_REG5, reg5.value);
  vTaskDelay(100 / portTICK_RATE_MS);
  xSemaphoreGive(_mutexRadio);
}

uint8_t radioGetVolume() {
  debug_printf("radioGetVolume\r\n");
  xSemaphoreTake(_mutexRadio, portMAX_DELAY);
  rda_reg5_t reg5 = { .value = getRegister(RDA5807M_REG5) };
  xSemaphoreGive(_mutexRadio);
  return reg5.VOLUME;
}

void radioSetMute(bool value) {
  debug_printf("radioSetMute\r\n");
  xSemaphoreTake(_mutexRadio, portMAX_DELAY);
  rda_reg2_t reg2 = { .value = getRegister(RDA5807M_REG2) };
  reg2.DMUTE = !value;
  setRegister(RDA5807M_REG2, reg2.value);
  xSemaphoreGive(_mutexRadio);
}

bool radioGetMute() {
  debug_printf("radioGetMute\r\n");
  xSemaphoreTake(_mutexRadio, portMAX_DELAY);
  rda_reg2_t reg2 = { .value = getRegister(RDA5807M_REG2) };
  xSemaphoreGive(_mutexRadio);
  return reg2.DMUTE == 0;
}

void radioSetHardMute(bool value) {
  debug_printf("radioSetHardMute\r\n");
  xSemaphoreTake(_mutexRadio, portMAX_DELAY);
  rda_reg2_t reg2 = { .value = getRegister(RDA5807M_REG2) };
  reg2.DHIZ = !value;
  setRegister(RDA5807M_REG2, reg2.value);
  xSemaphoreGive(_mutexRadio);
}

bool radioGetHardMute() {
  debug_printf("radioGetHardMute\r\n");
  xSemaphoreTake(_mutexRadio, portMAX_DELAY);
  rda_reg2_t reg2 = { .value = getRegister(RDA5807M_REG2) };
  xSemaphoreGive(_mutexRadio);
  return reg2.DHIZ == 0;
}

uint8_t radioGetRssi() {
  debug_printf("radioGetRssi\r\n");
  xSemaphoreTake(_mutexRadio, portMAX_DELAY);
  rda_regb_t regb = { .value = getRegister(RDA5807M_REGB) };
  xSemaphoreGive(_mutexRadio);
  return regb.RSSI;  
}

void radioSeek(bool seekUp) {
  debug_printf("radioSeek\r\n");
  xSemaphoreTake(_mutexRadio, portMAX_DELAY);
  rda_reg2_t reg2 = { .value = getRegister(RDA5807M_REG2) };
  reg2.SKMODE = 1;
  reg2.SEEK = 1;
  reg2.SEEKUP = seekUp ? 1: 0;
  setRegister(RDA5807M_REG2, reg2.value);
  vTaskDelay(300 / portTICK_RATE_MS);
  waitTune();
  xSemaphoreGive(_mutexRadio);
}

void waitTune() {
  rda_rega_t rega;
  do {
    rega.value = getRegister(RDA5807M_REGA);
    if (rega.STC == 0) vTaskDelay(5 / portTICK_RATE_MS);
  } while (rega.STC == 0);
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
  debug_printf("0x%02X = 0x%04X\r\n", reg, value);

  Wire.beginTransmission(RDA5807M_RANDOM_ACCESS_ADDRESS);
  Wire.write(reg);
  Wire.write(highByte(value));
  Wire.write(lowByte(value));
  Wire.endTransmission(true);
}
