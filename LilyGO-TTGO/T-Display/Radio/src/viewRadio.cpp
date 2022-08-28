#include "viewRadio.h"

ViewRadio::ViewRadio(const char* name, TFT_eSPI* tft, View** currentView, ControllerRadio* radio) : View(name, tft, currentView) {
    _radio = radio;
}

void ViewRadio::displayVolume() {
  const char* text;
  uint16_t volume = _radio->getVolume();
  if (volume < 1)       return;
  else if (volume < 3)  text = "▁";
  else if (volume < 5)  text = "▂";
  else if (volume < 7)  text = "▃";
  else if (volume < 9)  text = "▄";
  else if (volume < 11) text = "▅";
  else if (volume < 13) text = "▆";
  else if (volume < 15) text = "▇";
  else                  text = "█";
  _tft->setTextDatum(MC_DATUM);
  _tft->drawString(text, 149, 21);
}

void ViewRadio::displayMute() {
  const char* text;
  if (_radio->getMute()) text = "";
  else        text = "";
  _tft->setTextDatum(MC_DATUM);
  _tft->drawString(text, 185, 24);
}

void ViewRadio::displayLevel() {
  const char* text;
  uint8_t rssi = _radio->GetRssi();
  if (rssi < 20)      text = "";
  else if (rssi < 30) text = "";
  else if (rssi < 50) text = "";
  else if (rssi < 60) text = "";
  else                text = "";
  _tft->setTextDatum(MC_DATUM);
  _tft->drawString(text, 221, 24);
}

void ViewRadio::displayFreq() {
  String freq;
  freq.reserve(16);
  uint16_t index = _radio->getRadioIndex();
  ControllerRadioStorage::RadioItem_t rec = _radio->getStorage()->getRadioList()[index];
  uint16_t band = rec.band;
  freq.concat((uint16_t)(band / 10));
  freq.concat('.');
  freq.concat((uint16_t)(band % 10));
  _tft->setTextDatum(MC_DATUM);
  _tft->drawString(freq, 63, 26);
}

void ViewRadio::OnHandle() {
  // Serial.printf("%s\r\n", _name);
  _tft->fillScreen(TFT_SKYBLUE);
  _tft->setTextColor(TFT_MAGENTA);

  _tft->loadFont(FONT_SEGOE_32);
  // debug_printf("▁ %d\r\n", tft.textWidth("▁"));
  // debug_printf("▂ %d\r\n", tft.textWidth("▂"));
  // debug_printf("▃ %d\r\n", tft.textWidth("▃"));
  // debug_printf("▄ %d\r\n", tft.textWidth("▄"));
  // debug_printf("▅ %d\r\n", tft.textWidth("▅"));
  // debug_printf("▆ %d\r\n", tft.textWidth("▆"));
  // debug_printf("▇ %d\r\n", tft.textWidth("▇"));
  // debug_printf("█ %d\r\n", tft.textWidth("█"));
  // debug_printf(" %d\r\n", tft.textWidth(""));
  // debug_printf(" %d\r\n", tft.textWidth(""));
  // debug_printf(" %d\r\n", tft.textWidth(""));
  // debug_printf(" %d\r\n", tft.textWidth(""));
  // debug_printf(" %d\r\n", tft.textWidth(""));
  // debug_printf(" %d\r\n", tft.textWidth(""));
  // debug_printf(" %d\r\n", tft.textWidth(""));
  // debug_printf("Height = %d\r\n", tft.fontHeight());
  displayVolume();
  displayMute();
  displayLevel();
  _tft->unloadFont();
  
  _tft->loadFont(FONT_CALIBRI_56);
  displayFreq();
  _tft->unloadFont();

  _tft->loadFont(FONT_CALIBRI_32);

  uint16_t index = _radio->getRadioIndex();
  ControllerRadioStorage::RadioItem_t rec = _radio->getStorage()->getRadioList()[index];
  String text = rec.name;
  if (_tft->textWidth(text) >=  239) {
    _tft->setTextDatum(TL_DATUM);
    _tft->drawString(text, 0, 70);
  }
  else {
    _tft->setTextDatum(TC_DATUM);
    _tft->drawString(text, 119, 70);
  }
  _tft->unloadFont();
}
