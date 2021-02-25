#include <Arduino.h>
//#include <EEPROM.h>
#include <Wire.h>
#include "radio.h"
//#include <radio.h>
//#include <RDA5807M.h>         // https://github.com/mathertel/Radio
//#include <RotaryEncoder.h>    // https://github.com/mathertel/RotaryEncoder

/*
Скетч использует 2628 байт (8%) памяти устройства. Всего доступно 32256 байт.
Глобальные переменные используют 297 байт (14%) динамической памяти, оставляя 1751 байт для локальных переменных. Максимум: 2048 байт.

Скетч использует 4004 байт (12%) памяти устройства. Всего доступно 32256 байт.
Глобальные переменные используют 400 байт (19%) динамической памяти, оставляя 1648 байт для локальных переменных. Максимум: 2048 байт.

Скетч использует 4372 байт (13%) памяти устройства. Всего доступно 32256 байт.
Глобальные переменные используют 430 байт (20%) динамической памяти, оставляя 1618 байт для локальных переменных. Максимум: 2048 байт.

Скетч использует 4426 байт (13%) памяти устройства. Всего доступно 32256 байт.
Глобальные переменные используют 404 байт (19%) динамической памяти, оставляя 1644 байт для локальных переменных. Максимум: 2048 байт.

*/

//ARDUINO_AVR_MINI
//ARDUINO_AVR_NANO
//ARDUINO_AVR_UNO

#if !defined(ARDUINO_AVR_UNO)
  #error Select ARDUINO_AVR_UNO
#endif

uint8_t currentVolume = 2;    // 0..15
uint16_t currentBand = 1017;  // 101.7FM

typedef struct _radioItem {
  uint16_t band;
  char name[30];
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

const int listSize = sizeof(radioList) / sizeof(RadioItem_t);

uint8_t currentIndex = 35;

/*
RDA5807M radio;

RotaryEncoder encoderVolume(2, 3, RotaryEncoder::LatchMode::FOUR3);

int currentVolume = 2;
int currentBand = 10170;
int currentIndex = 0;   // индекс радиостанции
*/

void setup() {
  Serial.begin(9600);
  Wire.begin();
  
  radioInit();
  //radioSetBand(currentBand);
  selectStation(currentIndex);
  radioSetVolume(currentVolume);
    
/*
  pinMode(4, INPUT_PULLUP);

  radio.init();
  //radio.debugEnable();
  //setBand(currentBand);
  setRadio(currentIndex);
  setVolume(currentVolume);
  setMono(false);
  setMute(false);
*/
}

void loop() {
  uint8_t RSSI = radioGetRssi();
  Serial.print(F("RSSI = "));
  Serial.print(RSSI);
  Serial.println(F(" (0-min, 127-max)"));
  delay(500);
  
/*
  encoderVolume.tick();

  if (digitalRead(4) == LOW) {
    setMute(!radio.getMute());
    delay(1000);
  }
  
  int dir = (int)encoderVolume.getDirection();
  if (dir > 0) {
    if (currentIndex < listSize) {
      setRadio(++currentIndex);
    }
  }
  if (dir < 0) {
    if (currentIndex > 0) {
      setRadio(--currentIndex);
    }
  }
*/

/*
  if (dir > 0) {
    if (currentVolume < 15) {
      setVolume(++currentVolume);
    }
  }
  if (dir < 0) {
    if (currentVolume > 0) {
      setVolume(--currentVolume);
    }
  }
*/
}
/*
void setMute(bool value) {
  radio.setMute(value);
  Serial.print("Mute: ");
  Serial.println(value);  
}

void setMono(bool value) {
  radio.setMono(value);
  Serial.print("Mono: ");
  Serial.println(value);  
}

void setBand(int value) {
  radio.setBandFrequency(RADIO_BAND_FM, value);
  Serial.print("Band: ");
  Serial.println(value);  
}

void setVolume(int volume) {
  radio.setVolume(volume);
  Serial.print("Volume: ");
  Serial.println(volume);  
}

void setRadio(int value) {
  RadioItem_t row = radioList[value];
  radio.setBandFrequency(RADIO_BAND_FM, row.band);
  Serial.print("Band: ");
  Serial.print(row.band);
  Serial.print(" , Name: ");
  Serial.println(row.name);  
}
*/

void selectStation(uint8_t index) {
  char c;
  byte *p_item = (byte *)(radioList + index);
  uint16_t band = (uint16_t)pgm_read_dword_near(p_item);
  radioSetBand(band);

  p_item += sizeof(long);
  while ((c = (char)pgm_read_byte_near(p_item)) != '\0') {
    Serial.print(c);
    p_item++;
  }
  Serial.println();
}

void radioInit() {
  uint16_t reg02h = RDA5807M_FLG_ENABLE | RDA5807M_FLG_DHIZ | RDA5807M_FLG_DMUTE | RDA5807M_FLG_BASS;
  setRegister(RDA5807M_REG_CONFIG, reg02h);
}

void radioSetBand(uint16_t value) {
  uint16_t reg03h = (value - 870) << RDA5807M_CHAN_SHIFT;
  setRegister(RDA5807M_REG_TUNING, reg03h | RDA5807M_FLG_TUNE);  
}

void radioSetVolume(uint16_t value) {
  uint16_t reg05h = getRegister(RDA5807M_REG_VOLUME);
  reg05h &= ~RDA5807M_VOLUME_MASK;
  reg05h |= value << RDA5807M_VOLUME_SHIFT;
  setRegister(RDA5807M_REG_VOLUME, reg05h);
}

bool radioGetMute() {
  uint16_t reg02h = getRegister(RDA5807M_REG_CONFIG);
  return (reg02h & RDA5807M_FLG_DMUTE) == 0;
}

void radioSetMute(bool value) {
  uint16_t reg02h = getRegister(RDA5807M_REG_CONFIG);
  reg02h |= RDA5807M_FLG_DMUTE;
  if (value) reg02h &= ~RDA5807M_FLG_DMUTE;
  setRegister(RDA5807M_REG_CONFIG, reg02h);
}

uint8_t radioGetRssi() {
  uint16_t reg0Bh = getRegister(RDA5807M_REG_RSSI);
  uint8_t RSSI = (reg0Bh & RDA5807M_RSSI_MASK) >> RDA5807M_RSSI_SHIFT;
  return RSSI;  
}

uint16_t getRegister(uint8_t reg) {
  uint16_t result;
  Wire.beginTransmission(RDA5807M_RANDOM_ACCESS_ADDRESS);
  Wire.write(reg);
  Wire.endTransmission(false);
  Wire.requestFrom(0x11, 2, true);
  result = (uint16_t)Wire.read() << 8;
  result |= Wire.read();
  return result;
}
void setRegister(uint8_t reg, const uint16_t value) {
  Wire.beginTransmission(0x11);
  Wire.write(reg);
  Wire.write(highByte(value));
  Wire.write(lowByte(value));
  Wire.endTransmission(true);
}
