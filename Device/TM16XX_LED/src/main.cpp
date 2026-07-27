#include <Arduino.h>

#include <TM16xxDisplay.h>
#include <TM16xxButtons.h>
/*
      D4  A  F D3 D2  B                        
╔══════╧══╧══╧══╧══╧══╧══════╗
║ ┌───┐  ┌───┐  ┌───┐  ┌───┐ ║
║ │   │  │   │  │   │  │   │ ║
║ ├───┤  ├───┤  ├───┤  ├───┤ ║
║ │   │  │   │  │   │  │   │ ║
║ └───┘▪ └───┘▪ └───┘▪ └───┘▪║
╚══════╤══╤══╤══╤══╤══╤══════╝
       E  D DP  C  G D1

 G   F  A/C  A   B
╔╧═══╧═══╧═══╧═══╧╗
║      ┌───┐      ║
║      │   │      ║
║      ├───┤      ║
║      │   │      ║
║      └───┘▪     ║
╚╤═══╤═══╤═══╤═══╤╝
 E   D  A/C  C  DP
*/
#define TM16XX_DEBUG    1
char text[64];

//#define DEF_TM1637
#define DEF_TM1638

#ifdef ARDUINO_TTGO_T7_V13_Mini32
#define DIO 32
#define CLK 27
#define STB 25
#endif

#ifdef __AVR_ATmega328P__
#define DIO 10
#define CLK 9
#define STB 8
#endif

#ifdef DEF_TM1637
#include <TM1637.h>
TM1637 module(DIO, CLK, 4, true, 7);
TM16xxButtons buttons(&module);
TM16xxDisplay display(&module, 8);
#define DEF_NAME    "TM1637"
#endif

#ifdef DEF_TM1638
#include <TM1638.h>
#include <TM1638Anode.h>
TM1638Anode module(DIO, CLK, STB, true, 7);
TM16xxButtons buttons(&module);
TM16xxDisplay display(&module, 8);
#define DEF_NAME    "TM1638"
#endif


// This function will be called when a button was pressed 1 time (without a second press).
void fnClick(byte nButton) {
    Serial.print(F("Button "));
    Serial.print(nButton);
    Serial.println(F(" click."));
}

void setup() {
    
    Serial.begin(115200);
    Serial.println(F("Start"));
    Serial.println(DEF_NAME);
    module.setupDisplay(true, 7);       // set intensity 0-7, 7=highest
    module.clearDisplay();              // clear display
    delay(50);

    buttons.attachClick(fnClick);
    // buttons.attachDoubleClick(fnDoubleclick);
    // buttons.attachLongPressStart(fnLongPressStart);
    // buttons.attachLongPressStop(fnLongPressStop);
    // buttons.attachDuringLongPress(fnLongPress);
}

void loop() {
    static unsigned long ulTime = millis();
    uint32_t dwButtons = buttons.tick();

    if(dwButtons) {
        display.setDisplayToHexNumber(dwButtons, 0, false);
    }
    else {
        // For best doubleclick detection, the loop() needs to be as fast as possible. 
        // So instead of calling delay(100), we check if 100ms has passed.
        if(millis()-ulTime>100) {
            sprintf(text, "%lu", millis());
            module.setDisplayToString(text);
            ulTime=millis();
        }
    }
}
