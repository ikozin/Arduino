#include <Arduino.h>
#include <Wire.h>
#include <WiFi.h>
#include <Preferences.h>
#include <FS.h>
#include <SPIFFS.h>

#include "rda5807m.h"

#if !defined(ESP32)
  #error Select ESP32 DEV Board
#endif

#define DEBUG_CONSOLE

#if defined(DEBUG_CONSOLE)
#define debug_printf(...)   Serial.printf(__VA_ARGS__)
#else
#define debug_printf(...)
#define listDir(...)
#endif

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

uint16_t radioGetSeekTh() {
  debug_printf("radioGetSeekTh\r\n");
  xSemaphoreTake(_mutexRadio, portMAX_DELAY);
  rda_reg5_t reg5 = { .value = getRegister(RDA5807M_REG5) };
  xSemaphoreGive(_mutexRadio);
  return reg5.SEEKTH;  
}

uint16_t radioGetSoftBlend() {
  debug_printf("radioGetSoftBlend\r\n");
  xSemaphoreTake(_mutexRadio, portMAX_DELAY);
  rda_reg7_t reg7 = { .value = getRegister(RDA5807M_REG7) };
  xSemaphoreGive(_mutexRadio);
  return reg7.TH_SOFRBLEND;  
}

void radioSeek(uint16_t seekth, uint16_t softblend, bool seekUp) {
  debug_printf("radioSeek\r\n");
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

#define VOLUME_MAX      15
uint16_t currentVolume = 0;    // 0..15
uint16_t currentIndex  = 0;
bool    isMute = false;

typedef struct _radioItem {
  uint16_t band;
  char name[78];
} RadioItem_t;

#define RADIO_MAX   64

RadioItem_t radioList[RADIO_MAX] = {
  {  875, "БИЗНЕС-FM" },
  {  879, "Like FM" },
  {  883, "Радио Ретро FM" },
  {  887, "Юмор FM" },
  {  891, "Радио Джаз" },
  {  895, "Радио Мегаполис FM" },
  {  899, "Страна FM" },
  {  903, "Авто Радио" },
  {  908, "Relax-FM" },
  {  912, "Радио Эхо Москвы" },
  {  916, "Радио Культура" },
  {  920, "Москва ФМ" },
  {  924, "Радио Дача" },
  {  928, "Радио Карнавал" },
  {  932, "STUDIO 21" },
  {  936, "Коммерсант ФМ" },
  {  940, "Восток FM" },
  {  944, "Весна FM" },
  {  948, "Говорит Москва" },
  {  952, "Рок ФМ" },
  {  956, "Радио Звезда-FM" },
  {  960, "Дорожное радио" },
  {  964, "Такси FM" },
  {  968, "Детское радио" },
  {  972, "Радио Комсомольская правда" },
  {  976, "Вести ФМ" },
  {  980, "Радио Шоколад" },
  {  984, "Новое Радио" },
  {  988, "Радио Романтика" },
  {  992, "Радио Орфей" },
  {  996, "Радио Русский Хит" },
  { 1001, "Радио Серебряный Дождь" },
  { 1005, "Жара FM" },
  { 1009, "Радио Вера" },
  { 1012, "Радио DFM" },
  { 1017, "Наше Радио" },
  { 1021, "Радио Монте-Карло" },
  { 1025, "Comedy FM" },
  { 1030, "Радио Шансон" },
  { 1034, "Радио Маяк" },
  { 1037, "Радио Максимум" },
  { 1042, "Радио Энергия FM" },
  { 1047, "Радио 7 На Семи Холмах" },
  { 1050, "Радио Книга" },
  { 1053, "Capital FM" },
  { 1057, "Русское Радио" },
  { 1062, "Радио Европа Плюс" },
  { 1066, "Love радио" },
  { 1070, "звук IZ.RU" },
  { 1074, "Радио Хит FM" },
  { 1078, "Радио Новая Милицейская Волна" },
};

uint16_t listSize = 51;
void setRegister(uint8_t reg, const uint16_t value) {
  debug_printf("0x%02X = 0x%04X\r\n", reg, value);

  Wire.beginTransmission(RDA5807M_RANDOM_ACCESS_ADDRESS);
  Wire.write(reg);
  Wire.write(highByte(value));
  Wire.write(lowByte(value));
  Wire.endTransmission(true);
}

void setup() {
#if defined(DEBUG_CONSOLE)
  Serial.begin(115200);
  debug_printf("\r\n");
  debug_printf("\r\n");
  debug_printf("Model: %s, Rev: %d, Core: %d\r\n", ESP.getChipModel(), ESP.getChipRevision(), ESP.getChipCores());
  debug_printf("SDK: %s\r\n", ESP.getSdkVersion());
  debug_printf("Flash: %d\r\n", ESP.getFlashChipSize());
  //debug_printf("NVS Free Entries: %d\r\n", prefs.freeEntries());
  //debug_printf("Current Core = %d\r\n", xPortGetCoreID());
#endif

  radioInit();
  handleSetRadio(35);
  handleSetVolume(10);
  handleMute(false);

}

void handleMute(bool mute) {
  if (mute == isMute) return;
  isMute = mute;
  radioSetMute(isMute);
  //prefs.putBool("mute", isMute);  
  //xSemaphoreGive(displayRadioEvent);
}

void handleSetRadio(uint16_t index) {
  if (index >= listSize) index = 0;
  if (currentIndex == index) return;
  currentIndex = index;
  RadioItem_t rec = radioList[currentIndex];
  uint16_t band = rec.band;
  debug_printf("%d:%s\r\n", band, rec.name);
  radioSetChannel(band);
  //prefs.putInt("station", currentIndex);  
  //xSemaphoreGive(displayRadioEvent);
}

void handleSetVolume(uint16_t value) {
  if (value > VOLUME_MAX) value = VOLUME_MAX;
  if (currentVolume == value) return; 
  currentVolume = value;
  radioSetVolume(currentVolume);
  //prefs.putInt("volume", currentVolume);
  //xSemaphoreGive(displayRadioEvent);
}

void loop() {
  delay(1000);
}
