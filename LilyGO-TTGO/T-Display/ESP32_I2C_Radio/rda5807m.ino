#include "rda5807m.h"

SemaphoreHandle_t _mutexRadio;

void radioInit() {
  Wire.begin();
  _mutexRadio = xSemaphoreCreateMutex();
  xSemaphoreTake(_mutexRadio, portMAX_DELAY);

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

  vTaskDelay(1000 / portTICK_RATE_MS);
  xSemaphoreGive(_mutexRadio);
}

void radioSetChannel(uint16_t value) {
  xSemaphoreTake(_mutexRadio, portMAX_DELAY);
  rda_reg3_t reg = { .value = 0 };
  reg.CHAN = value - RADIO_BAND_MIN;
  reg.TUNE = 1;
  reg.BAND = RADIO_BAND_WIDTH; //00 - 87..108МГц, 01 - 76..91МГц, 10 - 76..108МГц, 11 - 65..76МГц или 50..65МГц (определяется битом 65M_50M MODE регистра 07h)
  setRegister(RDA5807M_REG3, reg.value);
  waitTune();
  vTaskDelay(200 / portTICK_RATE_MS);
  xSemaphoreGive(_mutexRadio);
}

uint16_t radioGetChannel() {
  xSemaphoreTake(_mutexRadio, portMAX_DELAY);
  rda_reg3_t reg = { .value = getRegister(RDA5807M_REG3) };
  xSemaphoreGive(_mutexRadio);
  return reg.CHAN + RADIO_BAND_MIN;
}

void radioSetVolume(uint16_t value) {
  debug_printf("Volume = %d\r\n", value);

  xSemaphoreTake(_mutexRadio, portMAX_DELAY);
  rda_reg5_t reg = { .value = getRegister(RDA5807M_REG5) };
  reg.VOLUME = value;
  setRegister(RDA5807M_REG5, reg.value);
  vTaskDelay(100 / portTICK_RATE_MS);
  xSemaphoreGive(_mutexRadio);
}

uint8_t radioGetVolume() {
  xSemaphoreTake(_mutexRadio, portMAX_DELAY);
  rda_reg5_t reg = { .value = getRegister(RDA5807M_REG5) };
  xSemaphoreGive(_mutexRadio);
  return reg.VOLUME;
}

void radioSetMute(bool value) {
  xSemaphoreTake(_mutexRadio, portMAX_DELAY);
  rda_reg2_t reg = { .value = getRegister(RDA5807M_REG2) };
  reg.DMUTE = !value;
  setRegister(RDA5807M_REG2, reg.value);
  xSemaphoreGive(_mutexRadio);
}

bool radioGetMute() {
  xSemaphoreTake(_mutexRadio, portMAX_DELAY);
  rda_reg2_t reg = { .value = getRegister(RDA5807M_REG2) };
  xSemaphoreGive(_mutexRadio);
  return reg.DMUTE == 0;
}

void radioSetHardMute(bool value) {
  xSemaphoreTake(_mutexRadio, portMAX_DELAY);
  rda_reg2_t reg = { .value = getRegister(RDA5807M_REG2) };
  reg.DHIZ = !value;
  setRegister(RDA5807M_REG2, reg.value);
  xSemaphoreGive(_mutexRadio);
}

bool radioGetHardMute() {
  xSemaphoreTake(_mutexRadio, portMAX_DELAY);
  rda_reg2_t reg = { .value = getRegister(RDA5807M_REG2) };
  xSemaphoreGive(_mutexRadio);
  return reg.DHIZ == 0;
}

uint8_t radioGetRssi() {
  xSemaphoreTake(_mutexRadio, portMAX_DELAY);
  rda_regb_t reg = { .value = getRegister(RDA5807M_REGB) };
  xSemaphoreGive(_mutexRadio);
  return reg.RSSI;  
}

void waitTune() {
  rda_rega_t reg;
  do {
    reg.value = getRegister(RDA5807M_REGA);
    if (reg.STC == 0) vTaskDelay(1);
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
  debug_printf("0x%02X = 0x%04X\r\n", reg, value);

  Wire.beginTransmission(RDA5807M_RANDOM_ACCESS_ADDRESS);
  Wire.write(reg);
  Wire.write(highByte(value));
  Wire.write(lowByte(value));
  Wire.endTransmission(true);
}
