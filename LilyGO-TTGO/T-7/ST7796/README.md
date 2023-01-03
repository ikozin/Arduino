#Arduino_GFX

```src/main.c

#include <Arduino_GFX_Library.h>

#define	TFT_SCK		18
#define	TFT_MOSI	23
#define	TFT_MISO	19
#define	TFT_CS		5

#define	TFT_DC		27
#define	TFT_RST		33
#define	TFT_BL		22

Arduino_ESP32SPI *bus = new Arduino_ESP32SPI(TFT_DC, TFT_CS, TFT_SCK, TFT_MOSI, TFT_MISO, VSPI);
Arduino_GFX *gfx = new Arduino_ST7796(bus, TFT_RST, 0 /* rotation */, false /* IPS */);

```

#TFT_eSPI

```User_Setup.c
#define USER_SETUP_INFO "User_Setup"

#define ST7796_DRIVER

#define TFT_WIDTH  320
#define TFT_HEIGHT 480

#define	TFT_SCK		18
#define	TFT_MOSI	23
#define	TFT_MISO	19
#define	TFT_CS		5

#define	TFT_DC		27
#define	TFT_RST		33
//#define	TFT_BL		22

#define	TOUCH_CS    22

#define LOAD_GLCD   // Font 1. Original Adafruit 8 pixel font needs ~1820 bytes in FLASH
#define LOAD_FONT2  // Font 2. Small 16 pixel high font, needs ~3534 bytes in FLASH, 96 characters
#define LOAD_FONT4  // Font 4. Medium 26 pixel high font, needs ~5848 bytes in FLASH, 96 characters
#define LOAD_FONT6  // Font 6. Large 48 pixel font, needs ~2666 bytes in FLASH, only characters 1234567890:-.apm
#define LOAD_FONT7  // Font 7. 7 segment 48 pixel font, needs ~2438 bytes in FLASH, only characters 1234567890:-.
#define LOAD_FONT8  // Font 8. Large 75 pixel font needs ~3256 bytes in FLASH, only characters 1234567890:-.
//#define LOAD_FONT8N // Font 8. Alternative to Font 8 above, slightly narrower, so 3 digits fit a 160 pixel TFT
#define LOAD_GFXFF  // FreeFonts. Include access to the 48 Adafruit_GFX free fonts FF1 to FF48 and custom fonts

// Comment out the #define below to stop the SPIFFS filing system and smooth font code being loaded
// this will save ~20kbytes of FLASH
#define SMOOTH_FONT

#define SPI_FREQUENCY  80000000

#define SPI_TOUCH_FREQUENCY  2500000

```
