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
  { 1018, "Наше Радио" },
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
Rda5807M radio; 

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

  radio.Init();
  radio.SetChannel(1018);
  radio.SetVolume(2);
  radio.SetMute(false);

}


void loop() {
  delay(1000);
}
