#include <OLED_I2C.h>

OLED  myOLED(SDA, SCL); // Remember to add the RESET pin if your display requires it...

/*

0  0  0  0  0  0  0  0
0  0  0  0  0  0  0  0
0  0  X  X  X  X  X  X
0  0  X  0  0  0  0  0
0  0  X  0  X  X  X  X
0  0  X  0  X  0  0  0
0  0  X  0  X  0  0  0
0  0  X  0  X  0  0  0

0  0  0  0  0  0  0  0
0  0  0  0  0  0  0  0
X  X  X  X  X  X  X  X
0  0  0  0  0  0  0  0
X  X  X  X  X  X  X  X
0  0  0  0  0  0  0  0
0  0  0  0  0  0  0  0
0  0  0  0  0  0  0  0

0  0  0  0  0  0  0  0
0  0  0  0  0  0  0  0
X  X  X  X  X  X  0  0
0  0  0  0  0  X  0  0
X  X  X  X  0  X  0  0
0  0  0  X  0  X  0  0
0  0  0  X  0  X  0  0
0  0  0  X  0  X  0  0

0  0  X  0  X  0  0  0
0  0  X  0  X  0  0  0
0  0  X  0  X  0  0  0
0  0  X  0  X  0  0  0
0  0  X  0  X  0  0  0
0  0  X  0  X  0  0  0
0  0  X  0  X  0  0  0
0  0  X  0  X  0  0  0

0  0  0  0  0  0  0  0
0  0  0  0  0  0  0  0
0  0  0  0  0  0  0  0
0  0  0  0  0  0  0  0
0  0  0  0  0  0  0  0
0  0  0  0  0  0  0  0
0  0  0  0  0  0  0  0
0  0  0  0  0  0  0  0

0  0  X  0  X  0  0  0
0  0  X  0  X  0  0  0
0  0  X  0  X  0  0  0
0  0  X  0  X  X  X  X
0  0  X  0  0  0  0  0
0  0  X  X  X  X  X  X
0  0  0  0  0  0  0  0
0  0  0  0  0  0  0  0

0  0  0  0  0  0  0  0
0  0  0  0  0  0  0  0
0  0  0  0  0  0  0  0
X  X  X  X  X  X  X  X
0  0  0  0  0  0  0  0
X  X  X  X  X  X  X  X
0  0  0  0  0  0  0  0
0  0  0  0  0  0  0  0

0  0  0  X  0  X  0  0
0  0  0  X  0  X  0  0
0  0  0  X  0  X  0  0
X  X  X  X  0  X  0  0
0  0  0  0  0  X  0  0
X  X  X  X  X  X  0  0
0  0  0  0  0  0  0  0
0  0  0  0  0  0  0  0

0  0  0  X  X  0  0  0
0  0  X  X  X  X  0  0
0  X  X  X  X  X  X  0
X  X  X  X  X  X  X  X
X  X  X  X  X  X  X  X
0  X  X  X  X  X  X  0
0  0  X  X  X  X  0  0
0  0  0  X  X  0  0  0

0  0  0  X  X  0  0  0
0  0  X  X  X  X  0  0
0  X  X  0  0  X  X  0
X  X  0  0  0  0  X  X
X  X  0  0  0  0  X  X
0  X  X  0  0  X  X  0
0  0  X  X  X  X  0  0
0  0  0  X  X  0  0  0
*/

const uint8_t borUpLt[8] PROGMEM={0x00, 0x00, 0xFC, 0x04, 0xF4, 0x14, 0x14, 0x14};  //╔
const uint8_t borRowU[8] PROGMEM={0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14};  //═
const uint8_t borUpRt[8] PROGMEM={0x14, 0x14, 0x14, 0xF4, 0x04, 0xFC, 0x00, 0x00};  //╗

const uint8_t borColL[8] PROGMEM={0x00, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0x00, 0x00};  //║
const uint8_t borEmpt[8] PROGMEM={0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};  //
const uint8_t borColR[8] PROGMEM={0x00, 0x00, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0x00};  //║

const uint8_t borDnLt[8] PROGMEM={0x00, 0x00, 0x3F, 0x20, 0x2F, 0x28, 0x28, 0x28};  //╚
const uint8_t borRowD[8] PROGMEM={0x28, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28};  //═
const uint8_t borDnRt[8] PROGMEM={0x28, 0x28, 0x28, 0x2F, 0x20, 0x2F, 0x00, 0x00};  //╝

//const uint8_t i1[8] PROGMEM={0x00, 0x18, 0x18, 0xFF, 0xFF, 0x18, 0x18, 0x00};
//const uint8_t i2[8] PROGMEM={0x18, 0x18, 0x18, 0x3E, 0x3E, 0x18, 0x18, 0x18};
const uint8_t i1[8] PROGMEM={0x18, 0x3C, 0x7E, 0xFF, 0xFF, 0x7E, 0x3C, 0x18};
const uint8_t i2[8] PROGMEM={0x18, 0x3C, 0x66, 0xC3, 0xC3, 0x66, 0x3C, 0x18};

uint8_t* screen[8][16] =
{
  { borUpLt, borRowU, borRowU, borRowU, borRowU, borRowU, borRowU, borRowU, borRowU, borRowU, borRowU, borRowU, borRowU, borRowU, borRowU, borUpRt }, //╔══════════════╗
  { borColL, borEmpt, borEmpt, borEmpt, borEmpt, borEmpt, borEmpt, borEmpt, borEmpt, borEmpt, borEmpt, borEmpt, borEmpt, borEmpt, borEmpt, borColR }, //║                       ║
  { borColL, borEmpt, borEmpt, borEmpt, borEmpt, borEmpt, borEmpt, borEmpt, borEmpt, borEmpt, borEmpt, borEmpt, borEmpt, borEmpt, borEmpt, borColR }, //║                       ║
  { borColL, borEmpt, borEmpt, borEmpt, borEmpt, borEmpt, borEmpt, borEmpt, borEmpt, borEmpt, borEmpt, borEmpt, borEmpt, borEmpt, borEmpt, borColR }, //║                       ║
  { borColL, borEmpt, borEmpt, borEmpt, borEmpt, borEmpt, borEmpt, borEmpt, borEmpt, borEmpt, borEmpt, borEmpt, borEmpt, borEmpt, borEmpt, borColR }, //║                       ║
  { borColL, borEmpt, borEmpt, borEmpt, borEmpt, borEmpt, borEmpt, borEmpt, borEmpt, borEmpt, borEmpt, borEmpt, borEmpt, borEmpt, borEmpt, borColR }, //║                       ║
  { borColL, borEmpt, borEmpt, borEmpt, borEmpt, borEmpt, borEmpt, borEmpt, borEmpt, borEmpt, borEmpt, borEmpt, borEmpt, borEmpt, borEmpt, borColR }, //║                       ║
  { borDnLt, borRowD, borRowD, borRowD, borRowD, borRowD, borRowD, borRowD, borRowD, borRowD, borRowD, borRowD, borRowD, borRowD, borRowD, borDnRt }, //╚══════════════╝
};


void setup()
{
  if(!myOLED.begin(SSD1306_128X64))
    while(1);   // In case the library failed to allocate enough RAM for the display buffer...
  myOLED.clrScr();
}


void loop()
{
  screen[2][2] = i1;
  screen[5][2] = i2;
  for (int y = 0; y < 8; y++)
    for (int x = 0; x < 16; x++)
      myOLED.drawBitmap(x << 3, y << 3, screen[y][x], 8, 8);
  myOLED.update();
  delay(100);

  screen[2][2] = i2;
  screen[5][2] = i1;
  for (int y = 0; y < 8; y++)
    for (int x = 0; x < 16; x++)
      myOLED.drawBitmap(x << 3, y << 3, screen[y][x], 8, 8);
  myOLED.update();
  delay(100);
/*  
  delay(2000);
  for (int i=0; i<2; i++)
  {
    myOLED.invert(true);
    delay(500);
    myOLED.invert(false);
    delay(500);
  }
  delay(2000);
*/
}
