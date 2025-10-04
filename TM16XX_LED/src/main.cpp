#include <Arduino.h>

#define TM16XX_DEBUG    1

#include <TM1638.h>
#include <TM1638Anode.h>
#include <TM16xxDisplay.h>
#include <TM16xxButtons.h>

// Module connection pins (Digital Pins)
#define DIO 32
#define CLK 27
#define STB 25

TM1638Anode module(DIO, CLK, STB, true, 7);
TM16xxButtons buttons(&module);
TM16xxDisplay display(&module, 8);

// This function will be called when a button was pressed 1 time (without a second press).
void fnClick(byte nButton) {
    Serial.print(F("Button "));
    Serial.print(nButton);
    Serial.println(F(" click."));
    display.println(F("sclk    "));
}

void setup() {
    Serial.begin(115200);
    Serial.print(F("TM1638: DIO="));
    Serial.print(DIO);
    Serial.print(F(", CLK="));
    Serial.print(CLK);
    Serial.print(F(", STB="));
    Serial.print(STB);
    Serial.println();
    
    module.clearDisplay();              // clear display
    module.setupDisplay(true, 7);       // set intensity 0-7, 7=highest
    delay(50);

    module.setNumDigits(8);
    module.setDisplayToString("HALO    ");
    delay(1000);
    module.setDisplayToString("YOUTUBE ");
    delay(1000);
    module.clearDisplay();

    // Attach the button callback functions that are defined below
    // buttons.attachRelease(fnRelease);
    buttons.attachClick(fnClick);
    // buttons.attachDoubleClick(fnDoubleclick);
    // buttons.attachLongPressStart(fnLongPressStart);
    // buttons.attachLongPressStop(fnLongPressStop);
    // buttons.attachDuringLongPress(fnLongPress);
    Serial.println(F("Start"));
    module.clearDisplay();              // clear display
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
            char text[17];
            //sprintf(text, "%lu", millis());
            ltoa(millis(), text, 10);   // DECIMAL = base 10
            module.setDisplayToString(text);
            ulTime=millis();
        }
    }
}
