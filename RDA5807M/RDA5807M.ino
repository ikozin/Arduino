#include <Arduino.h>
#include <Wire.h>
#include <RotaryEncoder.h>    // https://github.com/mathertel/RotaryEncoder
#include "radio.h"

#define DEBUG

//ARDUINO_AVR_MINI
//ARDUINO_AVR_NANO
//ARDUINO_AVR_UNO

#if !defined(ARDUINO_AVR_UNO)
  #error Select ARDUINO_AVR_UNO
#endif

RotaryEncoder encoderVolume(2, 3, RotaryEncoder::LatchMode::FOUR3);

uint8_t currentVolume = 2;    // 0..15
uint8_t currentIndex = 35;

typedef struct _radioItem {
  uint16_t band;
  char name[62];
} RadioItem_t;

const RadioItem_t radioList[] PROGMEM = {
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
  { 1021, "Радио Монте-Карлo" },
  { 1025, "Comedy FM" },
  { 1030, "Радио Шансон" },
  { 1034, "Радио Маяк" },
  { 1037, "Радио Максимум" },
  { 1042, "Радио Энергия FM" },
  { 1047, "Радио 7 На Семи Хoлмах" },
  { 1050, "Радио Книга" },
  { 1053, "Capital FM" },
  { 1057, "Русское Радио" },
  { 1062, "Радио Европа Плюс" },
  { 1066, "Love радио" },
  { 1070, "звук IZ.RU" },
  { 1074, "Радио Хит FM" },
  { 1078, "Радио Новая Милицейская Волна" },
};

const int listSize = sizeof(radioList) / sizeof(RadioItem_t);

void (*currentHandle)(int);

void setup() {
  Serial.begin(9600);
  Wire.begin();
  Serial.println();
  Serial.println();
  
  radioInit();
  radioSetRadio(currentIndex);
  radioSetVolume(currentVolume);
  
  pinMode(4, INPUT_PULLUP);
  currentHandle = handleChannel;
}

void loop() {
  encoderVolume.tick();
  if (digitalRead(4) == LOW) {
      if (currentHandle == handleChannel) {
          Serial.println(F("Volume Control"));
          currentHandle = handleVolume;
      }
      else {
          Serial.println(F("Channel Control"));
          currentHandle = handleChannel;
      }
  }
  int dir = (int)encoderVolume.getDirection();
  currentHandle(dir);
}

void handleChannel(int dir) {
  if (dir > 0) {
    if (currentIndex < listSize - 1) {
      radioSetRadio(++currentIndex);
    }
  }
  if (dir < 0) {
    if (currentIndex > 0) {
      radioSetRadio(--currentIndex);
    }
  }
}

void handleVolume(int dir) {
  if (dir > 0) {
    if (currentVolume < 15) {
      radioSetVolume(++currentVolume);
    }
  }
  if (dir < 0) {
    if (currentVolume > 0) {
      radioSetVolume(--currentVolume);
    }
  }
}

void radioSetRadio(uint8_t index) {
  char c;
  byte *pData = (byte *)(radioList + index);
  uint16_t band = pgm_read_word(pData);
  Serial.print(band);
  Serial.print(':');
  pData += sizeof(uint16_t);
  while ((c = (char)pgm_read_byte(pData++)) != 0) {
    Serial.print(c);
  }
  Serial.println();
  radioSetChannel(band);
}

void radioInit() {
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
#ifdef DEBUG
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
  Wire.requestFrom(RDA5807M_RANDOM_ACCESS_ADDRESS, 2, true);
  result = (uint16_t)Wire.read() << 8;
  result |= Wire.read();
  return result;
}

void setRegister(uint8_t reg, const uint16_t value) {
#ifdef DEBUG
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
