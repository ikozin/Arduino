#include <Arduino.h>
#include <Wire.h>

#include "rda5807m.h"

// PUBLIC

Rda5807M::Rda5807M() {
  _mutex = xSemaphoreCreateMutex();
}

void Rda5807M::Init() {
  xSemaphoreTake(_mutex, portMAX_DELAY);

  Wire.begin();

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

  xSemaphoreGive(_mutex);
}

void Rda5807M::SetChannel(uint16_t value) {
  xSemaphoreTake(_mutex, portMAX_DELAY);

  rda_reg3_t reg3 = { .value = 0 };
  reg3.SPACE = 0;
  reg3.BAND = RADIO_BAND_WIDTH; //00 - 87..108МГц, 01 - 76..91МГц, 10 - 76..108МГц, 11 - 65..76МГц или 50..65МГц (определяется битом 65M_50M MODE регистра 07h)
  reg3.TUNE = 1;
  reg3.CHAN = value - RADIO_BAND_MIN;
  setRegister(RDA5807M_REG3, reg3.value);
  vTaskDelay(200 / portTICK_RATE_MS);
  waitTune();

  xSemaphoreGive(_mutex);
}

void Rda5807M::SetVolume(uint16_t value) {
  xSemaphoreTake(_mutex, portMAX_DELAY);

  rda_reg5_t reg5 = { .value = getRegister(RDA5807M_REG5) };
  reg5.VOLUME = value;
  setRegister(RDA5807M_REG5, reg5.value);
  vTaskDelay(100 / portTICK_RATE_MS);

  xSemaphoreGive(_mutex);
 
}

void Rda5807M::SetMute(bool value) {
  xSemaphoreTake(_mutex, portMAX_DELAY);

  rda_reg2_t reg2 = { .value = getRegister(RDA5807M_REG2) };
  reg2.DMUTE = !value;
  setRegister(RDA5807M_REG2, reg2.value);

  xSemaphoreGive(_mutex);
}

void Rda5807M::SetHardMute(bool value) {
  xSemaphoreTake(_mutex, portMAX_DELAY);

  rda_reg2_t reg2 = { .value = getRegister(RDA5807M_REG2) };
  reg2.DHIZ = !value;
  setRegister(RDA5807M_REG2, reg2.value);

  xSemaphoreGive(_mutex);
}

void Rda5807M::Seek(uint16_t seekth, uint16_t softblend, bool seekUp) {
  xSemaphoreTake(_mutex, portMAX_DELAY);

  rda_reg5_t reg5 = { .value = getRegister(RDA5807M_REG5) };
  rda_reg7_t reg7 = { .value = getRegister(RDA5807M_REG7) };
  if (reg5.SEEKTH != seekth) {
    reg5.SEEKTH = seekth;
    setRegister(RDA5807M_REG5, reg5.value);
  }
  if (reg7.TH_SOFRBLEND != softblend) {
    reg7.TH_SOFRBLEND = softblend;
    setRegister(RDA5807M_REG7, reg7.value);
  }
 
  rda_reg2_t reg2 = { .value = getRegister(RDA5807M_REG2) };
  reg2.SKMODE = 1;
  reg2.SEEK = 1;
  reg2.SEEKUP = seekUp ? 1: 0;
  setRegister(RDA5807M_REG2, reg2.value);
  vTaskDelay(300 / portTICK_RATE_MS);
  waitTune();

  xSemaphoreGive(_mutex);
}


uint16_t Rda5807M::GetChannel() {
  xSemaphoreTake(_mutex, portMAX_DELAY);
  rda_reg3_t reg3 = { .value = getRegister(RDA5807M_REG3) };

  xSemaphoreGive(_mutex);
  return reg3.CHAN + RADIO_BAND_MIN;
}

uint8_t Rda5807M::GetVolume() {
  xSemaphoreTake(_mutex, portMAX_DELAY);

  rda_reg5_t reg5 = { .value = getRegister(RDA5807M_REG5) };

  xSemaphoreGive(_mutex);
  return reg5.VOLUME;
}

bool Rda5807M::GetMute() {
  xSemaphoreTake(_mutex, portMAX_DELAY);

  rda_reg2_t reg2 = { .value = getRegister(RDA5807M_REG2) };

  xSemaphoreGive(_mutex);
  return reg2.DMUTE == 0;
}

bool Rda5807M::GetHardMute() {
  xSemaphoreTake(_mutex, portMAX_DELAY);
  
  rda_reg2_t reg2 = { .value = getRegister(RDA5807M_REG2) };
  
  xSemaphoreGive(_mutex);
  return reg2.DHIZ == 0;
}

uint8_t Rda5807M::GetRssi() {
  xSemaphoreTake(_mutex, portMAX_DELAY);

  rda_regb_t regb = { .value = getRegister(RDA5807M_REGB) };

  xSemaphoreGive(_mutex);
  return regb.RSSI;  
}

uint16_t Rda5807M::GetSeekTh() {
  xSemaphoreTake(_mutex, portMAX_DELAY);

  rda_reg5_t reg5 = { .value = getRegister(RDA5807M_REG5) };

  xSemaphoreGive(_mutex);
  return reg5.SEEKTH;  
}

uint16_t Rda5807M::GetSoftBlend() {
  xSemaphoreTake(_mutex, portMAX_DELAY);

  rda_reg7_t reg7 = { .value = getRegister(RDA5807M_REG7) };

  xSemaphoreGive(_mutex);
  return reg7.TH_SOFRBLEND;  
}

// PRIVATE

void Rda5807M::waitTune() {
  rda_rega_t rega;
  do {
    rega.value = getRegister(RDA5807M_REGA);
    if (rega.STC == 0) vTaskDelay(WaitTime / portTICK_RATE_MS);
  } while (rega.STC == 0);
}

uint16_t Rda5807M::getRegister(uint8_t reg) {
  uint16_t result;
  Wire.beginTransmission(RDA5807M_RANDOM_ACCESS_ADDRESS);
  Wire.write(reg);
  Wire.endTransmission(false);
  Wire.requestFrom((uint16_t)RDA5807M_RANDOM_ACCESS_ADDRESS, (uint8_t)2, true);
  result = (uint16_t)Wire.read() << 8;
  result |= Wire.read();
  return result;
}

void Rda5807M::setRegister(uint8_t reg, const uint16_t value) {
  Wire.beginTransmission(RDA5807M_RANDOM_ACCESS_ADDRESS);
  Wire.write(reg);
  Wire.write(highByte(value));
  Wire.write(lowByte(value));
  Wire.endTransmission(true);
}
