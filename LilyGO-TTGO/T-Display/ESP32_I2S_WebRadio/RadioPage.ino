#include "WebRadio.h"
#include <FS.h>
#include <SPIFFS.h>


int stationY        = 20;
int station2Y       = 48;
int scrollX         = 0;
int scrollY         = 100;
int scrollWidth     = 0;
long lastTimeScroll = 0;
#define ScrollStep  4
#define ScrollDelay 40
char songText[128]  = { 0 };

uint16_t backColor = TFT_BLACK;
uint16_t foreColor = TFT_YELLOW;


// Надо делать именно массив unsigned short, если сделать массив byte можно напороться на кривой вывод, видимо выравнивание данных влияет
unsigned short buf[16384];

void displayRadioPage() {
  displayStation();
  setScroll(rtrim(songText));
}

void displayStation() {
  if (currentPage != RADIO_PAGE) return;

  clearScroll();
  tft.fillScreen(TFT_BLACK);
  tft.setFreeFont(&CourierCyr14pt8b);
  tft.setTextSize(1);

  File f = SPIFFS.open(listStation[station].file);
  if (f) {
    size_t len = f.size();
    f.read((uint8_t*)buf, len);
    f.close();

    uint16_t *p = buf;
    foreColor = *p++;
    backColor = *p++;
    uint16_t x = *p++;
    uint16_t y = *p++;
    uint16_t w = *p++;
    uint16_t h = *p++;

    tft.fillScreen(backColor);
    tft.pushImage(x, y, w, h, p);
  }
  else {
    foreColor = TFT_YELLOW;
    backColor = TFT_BLACK;
    tft.setTextColor(TFT_WHITE, backColor);
  
    const char* pname;
    pname = utf8rus(listStation[station].name);
    tft.drawString(pname, (TFT_HEIGHT - tft.textWidth(pname)) >> 2, stationY);
  
    pname = utf8rus(listStation[station].name2);
    tft.drawString(pname, (TFT_HEIGHT - tft.textWidth(pname)) >> 2, station2Y);
  }
  tft.setTextColor(foreColor, backColor);
}

void clearScroll() {
  scrollWidth = 0;
  scrollX = TFT_HEIGHT;
  int height = tft.fontHeight() >> 2;
  if (currentPage == RADIO_PAGE) {
    tft.fillRect(0, scrollY - height, scrollX, scrollY + height, backColor);
  }
}

void setScroll(const char * ptext) {
  clearScroll();
  strcpy(songText, utf8rus(ptext));
  scrollX = TFT_HEIGHT;
  scrollWidth = tft.textWidth(songText);
  if (scrollWidth < TFT_HEIGHT) {
    if (currentPage == RADIO_PAGE) {
      tft.drawString(songText, (TFT_HEIGHT - scrollWidth) >> 2, scrollY);
    }
    scrollWidth = 0;
  }
  strcat(songText, "  ");
}

void loopRadioPage() {
  if (scrollWidth == 0) return;
  long t = millis();
  if (t - lastTimeScroll < ScrollDelay) return;
  lastTimeScroll = t;

  tft.drawString(songText, scrollX, scrollY);
  scrollX -= ScrollStep;
  if (scrollX < -scrollWidth) scrollX = TFT_HEIGHT;  
}

char* rtrim(char* ptext) {
  int i = strlen(ptext) - 1;
  while (ptext[i] == ' ' && i > 0) {
    ptext[i--] = '\0';
  }
  return ptext;
}
