#include <Arduino.h>
#include <Device.h>
#include <DevicePackage.h>
#include <EncButton.h>

#include <K155.h>
#include <K555.h>
#include <K556.h>
#include <K565.h>
#include <K580.h>
#include <K1533.h>

#ifndef __AVR_ATmega2560__
#error Select board ATMEGA2560
#endif

GyverDisplay display;
EncButtonT<PIN_ENC_S1, PIN_ENC_S2, PIN_ENC_BTN> encoder;

//               DIP 14
//    PC0(37) [ 1]   [14]  VCC
//    PC1(36) [ 2]   [13] PA0(22)
//    PC2(35) [ 3]   [12] PA1(23)
//    PC3(34) [ 4]   [11] PA2(24)
//    PC4(33) [ 5]   [10] PA3(25)
//    PC5(32) [ 6]   [ 9] PA4(26)
//      GND   [ 7]   [ 8] PA5(27)
//
//
//
//               DIP 16
//    PC0(37) [ 1]   [16]  VCC
//    PC1(36) [ 2]   [15] PA0(22)
//    PC2(35) [ 3]   [14] PA1(23)
//    PC3(34) [ 4]   [13] PA2(24)
//    PC4(33) [ 5]   [12] PA3(25)
//    PC5(32) [ 6]   [11] PA4(26)
//    PC6(31) [ 7]   [10] PA5(27)
//      GND   [ 8]   [ 9] PA6(28)
//
//
//
//               DIP 20
//    PL0(49) [ 1]   [20]  VCC
//    PC0(37) [ 2]   [19] PL1(48)
//    PC1(36) [ 3]   [18] PA0(22)
//    PC2(35) [ 4]   [17] PA1(23)
//    PC3(34) [ 5]   [16] PA2(24)
//    PC4(33) [ 6]   [15] PA3(25)
//    PC5(32) [ 7]   [14] PA4(26)
//    PC6(31) [ 8]   [13] PA5(27)
//    PC7(30) [ 9]   [12] PA6(28)
//      GND   [10]   [11] PA7(29)
//
//
//
//    !!!!!!!!!!!!!!!!!!!!!!!!!!!
//    !! DIP 14(ИЕ2, ИЕ4, ИЕ5) !!
//    !!!!!!!!!!!!!!!!!!!!!!!!!!!
//
//    PC0(37) [ 1]   [14] PA0(22)
//    PC1(36) [ 2]   [13] 
//    PC2(35) [ 3]   [12] PA1(24)
//            [ 4]   [11] PA2(25)
//      VCC   [ 5]   [10]  GND 
//    PC4(34) [ 6]   [ 9] PA3(26)
//    PC5(33) [ 7]   [ 8] PA4(27)
//
//
//
//    !!!!!!!!!!!!!!!!!!!!!!!!!!!
//    !! DIP 16(ИД1, ИМ3, ТМ7) !!
//    !!!!!!!!!!!!!!!!!!!!!!!!!!!
//
//    PC0(37) [ 1]   [16] PA0(22)
//    PC1(36) [ 2]   [15] PA1(23)
//    PC2(35) [ 3]   [14] PA2(24)
//    PC3(34) [ 4]   [13] PA3(25)
//      VCC   [ 5]   [12]  GND 
//    PC4(33) [ 6]   [11] PA4(26)
//    PC5(32) [ 7]   [10] PA5(27)
//    PC6(31) [ 8]   [ 9] PA6(28)
//
//
//


// Не стандартная разводка питания: ИЕ5, ТМ5, ТМ7
DevicePackage* packList[] = {
    new K155_Pack(),
    new K555_Pack(),
    new K556_Pack(),
    new K565_Pack(),
    new K580_Pack(),
    new K1533_Pack(),
};

int size  = sizeof(packList)/sizeof(packList[0]);
int index = 0;

void encoderMenuAction();
void encoderPackageAction();

void displayMenu(GyverDisplay& display, int index) {
    gio::low(PIN_LED_GREEN);
    gio::low(PIN_LED_RED);
    int line = 0;
    if (size > 7) {
        line = (index - 3 >= 0) ? index - 3 : 0;
        line = (index >= size - 4) ? size - 8: line;
    }
    display.clear();
    display.setCursor(0, 0);
    for (int i = 0; i < 8;  i++) {
        if (line + i >= size) break;
        display.invertText(index == line + i);
        display.print(packList[line + i]->title());
        display.print("  (");
        display.print(packList[line + i]->count());
        display.print(" шт)");
        display.println();
    }
    display.invertText(false);
    display.update();
}

void encoderMenuAction() {
    int step;
    switch (encoder.action()) {
        case EB_HOLD:
            break;
        case EB_CLICK:
            encoder.attach(encoderPackageAction);
            packList[index]->display(display);
            break;
        case EB_TURN:
            step = (encoder.fast()) ? 7: 1;
            if (encoder.dir() > 0) {
                index += step;
                index = constrain(index, 0, size - 1);
            } else {
                index -= step;
                index = constrain(index, 0, size - 1);
            }
            displayMenu(display, index);
            break;
        default:
            break;
    }
}

void encoderPackageAction() {
    int step, result;
    switch (encoder.action()) {
        case EB_HOLD:
            encoder.attach(encoderMenuAction);
            displayMenu(display, index);
            break;
        case EB_CLICK:
            gio::low(PIN_LED_GREEN);
            gio::low(PIN_LED_RED);
            result = packList[index]->test(display);
            if (result == 0) {
                gio::high(PIN_LED_GREEN);
            } else {
                gio::high(PIN_LED_RED);
            }
            break;
        case EB_TURN:
            step = (encoder.fast()) ? 7: 1;
            if (encoder.dir() > 0) {
                packList[index]->next(step);
            } else {
                packList[index]->prev(step);
            }
            packList[index]->display(display);
            break;
        default:
            break;
    }
}

void setup() {
    //Serial.println("!!!");  //ЭТО БАГ Aduino Mega, ПРИ НАЛИЧИИ СТРОКИ "!!!" ВЫЗЫВАЕТ ОШИБКУ ЗАГРУЗКИ, НАПРИМЕР: char text[128] = "!!!";

    DDRA = B00000000;   // Set input mode
    DDRC = B00000000;   // Set input mode
    DDRL = B00000000;   // Set input mode

    PORTA = B11111111;  // Set pullup mode
    PORTC = B11111111;  // Set pullup mode
    PORTL = B11111111;  // Set pullup mode

    gio::mode(PIN_LED_GREEN, OUTPUT);
    gio::mode(PIN_LED_RED, OUTPUT);

    //encoder.init(INPUT_PULLUP, INPUT_PULLUP, LOW);
    encoder.attach(encoderMenuAction);

    // for (size_t p = 0; p < (sizeof(packList)/sizeof(packList[0])); p++) {
    //   for (size_t t = 0; t < packList[p]->count(); t++) {
    //   }
    // }

    // Initialize Serial
    Serial.begin(115200);
    while (!Serial);
    delay(2000); // Pause for 2 seconds
    
    display.init();
    display.clear();
    display.home();
    // display.flipV(true);
    // display.flipH(true);

    displayMenu(display, index);   
}

void testLed() {
    gio::high(PIN_LED_GREEN);
    gio::high(PIN_LED_RED);
    delay(250);

    gio::low(PIN_LED_GREEN);
    gio::low(PIN_LED_RED);
    delay(250);

    gio::high(PIN_LED_GREEN);
    gio::low(PIN_LED_RED);
    delay(250);

    gio::low(PIN_LED_GREEN);
    gio::high(PIN_LED_RED);
    delay(250);

    gio::low(PIN_LED_GREEN);
    gio::low(PIN_LED_RED);
    delay(250);
}

void loop() {
    encoder.tick();
    // testLed();
}
