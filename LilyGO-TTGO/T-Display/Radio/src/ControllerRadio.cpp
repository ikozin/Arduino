#include "controllerRadio.h"
#include "main.h"

// RadioItem_t radioList[RADIO_MAX] = {
//   {  875, "БИЗНЕС-FM" },
//   {  879, "Like FM" },
//   {  883, "Радио Ретро FM" },
//   {  887, "Юмор FM" },
//   {  891, "Радио Джаз" },
//   {  895, "Радио Мегаполис FM" },
//   {  899, "Страна FM" },
//   {  903, "Авто Радио" },
//   {  908, "Relax-FM" },
//   {  912, "Радио Эхо Москвы" },
//   {  916, "Радио Культура" },
//   {  920, "Москва ФМ" },
//   {  924, "Радио Дача" },
//   {  928, "Радио Карнавал" },
//   {  932, "STUDIO 21" },
//   {  936, "Коммерсант ФМ" },
//   {  940, "Восток FM" },
//   {  944, "Весна FM" },
//   {  948, "Говорит Москва" },
//   {  952, "Рок ФМ" },
//   {  956, "Радио Звезда-FM" },
//   {  960, "Дорожное радио" },
//   {  964, "Такси FM" },
//   {  968, "Детское радио" },
//   {  972, "Радио Комсомольская правда" },
//   {  976, "Вести ФМ" },
//   {  980, "Радио Шоколад" },
//   {  984, "Новое Радио" },
//   {  988, "Радио Романтика" },
//   {  992, "Радио Орфей" },
//   {  996, "Радио Русский Хит" },
//   { 1001, "Радио Серебряный Дождь" },
//   { 1005, "Жара FM" },
//   { 1009, "Радио Вера" },
//   { 1012, "Радио DFM" },
//   { 1017, "Наше Радио" },
//   { 1021, "Радио Монте-Карло" },
//   { 1025, "Comedy FM" },
//   { 1030, "Радио Шансон" },
//   { 1034, "Радио Маяк" },
//   { 1037, "Радио Максимум" },
//   { 1042, "Радио Энергия FM" },
//   { 1047, "Радио 7 На Семи Холмах" },
//   { 1050, "Радио Книга" },
//   { 1053, "Capital FM" },
//   { 1057, "Русское Радио" },
//   { 1062, "Радио Европа Плюс" },
//   { 1066, "Love радио" },
//   { 1070, "звук IZ.RU" },
//   { 1074, "Радио Хит FM" },
//   { 1078, "Радио Новая Милицейская Волна" },
// };

ControllerRadio::ControllerRadio(const char* name, Preferences* prefs, ControllerRadioStorage* storage) : Controller(name) {
    _prefs = prefs;
    _storage = storage;
    _currentVolume = 0;
    _currentIndex  = 0;
    _isMute = false;
}

void ControllerRadio::OnHandle() {
    _radio.Init();    
    setRadioIndex(_prefs->getInt("station", 35));
    setVolume(_prefs->getInt("volume", 2));
    setMute(_prefs->getBool("mute", false));
    vTaskDelete(_task);
}

void ControllerRadio::toggleMute() {
  setMute(!_isMute);
}

void ControllerRadio::changeChannel(int direction) {
  if (direction > 0) {
    if (_currentIndex < _storage->getCount() - 1) {
      setRadioIndex(_currentIndex + 1);
    }
  }
  if (direction < 0) {
    if (_currentIndex > 0) {
      setRadioIndex(_currentIndex - 1);
    }
  }
}

void ControllerRadio::changeVolume(int direction) {
  if (direction > 0) {
    if (_currentVolume < VOLUME_MAX) {
      setVolume(_currentVolume + 1);
    }
  }
  if (direction < 0) {
    if (_currentVolume > 0) {
      setVolume(_currentVolume - 1);
    }
  }
}


void ControllerRadio::setMute(bool mute) {
  _isMute = mute;
  _radio.SetMute(_isMute);
  _prefs->putBool("mute", _isMute);  
  xSemaphoreGive(_updateEvent);
}

void ControllerRadio::setRadioIndex(uint16_t index) {
  if (index >= _storage->getCount()) index = 0;
  if (_currentIndex == index) return;
  _currentIndex = index;
  ControllerRadioStorage::RadioItem_t rec = _storage->getRadioList()[_currentIndex];
  uint16_t band = rec.band;
  _radio.SetChannel(band);
  _prefs->putInt("station", _currentIndex);  
  xSemaphoreGive(_updateEvent);
}

void ControllerRadio::setVolume(uint16_t value) {
  if (value > VOLUME_MAX) value = VOLUME_MAX;
  if (_currentVolume == value) return; 
  _currentVolume = value;
  _radio.SetVolume(_currentVolume);
  _prefs->putInt("volume", _currentVolume);
  xSemaphoreGive(_updateEvent);
}
