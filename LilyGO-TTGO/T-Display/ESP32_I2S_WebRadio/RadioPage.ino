#include "WebRadio.h"

int stationY        = 20;
int station2Y       = 48;
int scrollX         = 0;
int scrollY         = 100;
int scrollWidth     = 0;
long lastTimeScroll = 0;
#define ScrollStep  4
#define ScrollDelay 40
char songText[128]  = { 0 };

void displayRadioPage() {
  displayStation();
  setScroll(rtrim(songText));
}

void displayStation() {
  if (currentPage != RADIO_PAGE) return;

  tft.setFreeFont(&CourierCyr14pt8b);
  tft.setTextSize(1);
  
  clearScroll();
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  
  const char* pname;
  pname = utf8rus(listStation[station].name);
  tft.drawString(pname, (TFT_HEIGHT - tft.textWidth(pname)) >> 2, stationY);
  
  pname = utf8rus(listStation[station].name2);
  tft.drawString(pname, (TFT_HEIGHT - tft.textWidth(pname)) >> 2, station2Y);

  tft.setTextColor(TFT_YELLOW, TFT_BLACK);
}

void clearScroll() {
  scrollWidth = 0;
  scrollX = TFT_HEIGHT;
  int height = tft.fontHeight() >> 2;
  if (currentPage == RADIO_PAGE) {
    tft.fillRect(0, scrollY - height, scrollX, scrollY + height, TFT_BLACK);
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
