#ifndef WEBRADIO_H_
#define WEBRADIO_H_

#include <Arduino.h>
#include <TFT_eSPI.h>

#include "FontsRus\CourierCyr6.h"
#include "FontsRus\CourierCyr7.h"
#include "FontsRus\CourierCyr8.h"
#include "FontsRus\CourierCyr9.h"
#include "FontsRus\CourierCyr10.h"
#include "FontsRus\CourierCyr12.h"
#include "FontsRus\CourierCyr14.h"
#include "FontsRus\CourierCyr16.h"
#include "FontsRus\CourierCyr18.h"

#include "FontsRus\FreeMono6.h"
#include "FontsRus\FreeMono7.h"
#include "FontsRus\FreeMono8.h"
#include "FontsRus\FreeMono9.h"
#include "FontsRus\FreeMono10.h"
#include "FontsRus\FreeMono12.h"
#include "FontsRus\FreeMono14.h"
#include "FontsRus\FreeMono16.h"
#include "FontsRus\FreeMono18.h"

#define RADIO_PAGE    0
#define TIME_PAGE     1
#define WEATHER_PAGE  2

extern int currentPage;
extern TFT_eSPI tft;

extern char *utf8rus(const char *source);

extern int stationY;
extern int station2Y;
extern int scrollX;
extern int scrollY;

extern void displayRadioPage();
extern void displayStation();
extern void setScroll(const char * ptext);
extern void loopRadioPage();

extern int timeX;
extern int timeY;
extern int calendarY;
extern int dowY;

extern void displayTimePage();
extern void loopTimePage();

extern void displayWeatherPage();
extern void loopWeatherPage();

#endif //WEBRADIO_H_
