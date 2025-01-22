#include <Arduino.h>
#include <TFT_eSPI.h>

#ifndef ESP32
    #error ESP32
#endif

/*

Параметры
╔════════════════╦════════════╗
║ Протокол       ║ SPI        ║
╠════════════════╬════════════╣
║ Питание        ║ +3V3       ║
╚════════════════╩════════════╝

Описание контактов
╔═════╦══════════════════════════════════════════════════════════════════════════════════════════════════╗
║ VDD ║ 3V3 power input (with R0)                                                                        ║
╠═════╬══════════════════════════════════════════════════════════════════════════════════════════════════╣
║ GND ║ Ground                                                                                           ║
╠═════╬══════════════════════════════════════════════════════════════════════════════════════════════════╣
║ CS  ║ LCD chip select signal, low level enable                                                         ║
╠═════╬══════════════════════════════════════════════════════════════════════════════════════════════════╣
║ RST ║ LCD chip reset signal, low level reset                                                           ║
╠═════╬══════════════════════════════════════════════════════════════════════════════════════════════════╣
║ D/C ║ LCD register/data selection signal, high level: register, low level: data                        ║
╠═════╬══════════════════════════════════════════════════════════════════════════════════════════════════╣
║ SDI ║ SPI (MOSI) bus write data signal                                                                 ║
╠═════╬══════════════════════════════════════════════════════════════════════════════════════════════════╣
║ SCK ║ SPI (SCK) bus clock signal                                                                       ║
╠═════╬══════════════════════════════════════════════════════════════════════════════════════════════════╣
║ BL  ║ Backlight control, high level lighting, if not controlled, connect 3v3 always bright             ║
╠═════╬══════════════════════════════════════════════════════════════════════════════════════════════════╣
║ SDO ║ SPI (MISO) bus data read signal, if you do not need to the read function, you can not connect it ║
╠═════╬══════════════════════════════════════════════════════════════════════════════════════════════════╣
║ TCK ║ Touch SPI bus clock signal                                                                       ║
╠═════╬══════════════════════════════════════════════════════════════════════════════════════════════════╣
║ TCS ║ Touch screen chip select signal, low level enable                                                ║
╠═════╬══════════════════════════════════════════════════════════════════════════════════════════════════╣
║ TDI ║ Touch SPI bus input                                                                              ║
╠═════╬══════════════════════════════════════════════════════════════════════════════════════════════════╣
║ TDO ║ Touch SPI bus output                                                                             ║
╠═════╬══════════════════════════════════════════════════════════════════════════════════════════════════╣
║ PEN ║ Touch screen interrupt signal, low level when touch is detected                                  ║
╚═════╩══════════════════════════════════════════════════════════════════════════════════════════════════╝


Распиновка
╔═════╦═════╦═════╦═════╦═════╦═════╦═════╦═════╦═════╦═════╦═════╦═════╦═════╦═════╗
║ VDD ║ GND ║ CS  ║ RST ║ D/C ║ SDI ║ SCK ║ BL  ║ SDO ║ TCK ║ TCS ║ TDI ║ TDO ║ PEN ║
╠═════╬═════╬═════╬═════╬═════╬═════╬═════╬═════╬═════╬═════╬═════╬═════╬═════╬═════╣
║ 3V3 ║ GND ║  5  ║ 26  ║ 25  ║ 23  ║ 18  ║ 27  ║     ║ 18  ║ 32  ║ 23  ║ 19  ║     ║
╚═════╩═════╩═════╩═════╩═════╩═════╩═════╩═════╩═════╩═════╩═════╩═════╩═════╩═════╝



#define TFT_MISO    19
#define TFT_MOSI    23
#define TFT_SCLK    18
#define TFT_CS      5

#define TFT_DC      25
#define TFT_RST     26
#define TFT_BL      27

*/

TFT_eSPI tft = TFT_eSPI();       // Invoke custom library
char text[128];

void touch_calibrate() {
    uint16_t calData[5];

    // data not valid so recalibrate
    tft.fillScreen(TFT_BLACK);
    tft.setCursor(20, 0);
    tft.setTextFont(2);
    tft.setTextSize(1);
    tft.setTextColor(TFT_WHITE, TFT_BLACK);

    tft.println("Touch corners as indicated");

    tft.setTextFont(1);
    tft.println();

    tft.calibrateTouch(calData, TFT_MAGENTA, TFT_BLACK, 15);

    tft.setTextColor(TFT_GREEN, TFT_BLACK);
    tft.println("Calibration complete!");

    // calibration data valid
    tft.setTouch(calData);
    for (int i = 0; i < sizeof(calData)/sizeof(calData[0]); i++) {
        sprintf(text, "%04X ", calData[i]);
        Serial.print(text);
    }
    Serial.println();
}

void setup() {
    Serial.begin(115200);
    Serial.println("setup");

    pinMode(TFT_BL, OUTPUT);
    digitalWrite(TFT_BL, HIGH);
    tft.init();
    tft.setRotation(0);
    tft.fillScreen(random(0xFFFF));

    touch_calibrate();

    tft.fillScreen(random(0xFFFF));
    tft.setCursor(0, 0, 2);
    tft.setTextColor(TFT_WHITE,TFT_BLACK);  tft.setTextSize(1);
    tft.println("Hello World!");

    tft.setTextColor(TFT_YELLOW); tft.setTextFont(7);
    tft.println(1234.56);

    tft.setTextColor(TFT_RED,TFT_BLACK);    tft.setTextFont(4);
    tft.println((long)3735928559, HEX); // Should print DEADBEEF

    tft.setTextColor(TFT_GREEN,TFT_BLACK);
    tft.setTextFont(4);
    tft.println("Groop");
    tft.println("I implore thee,");

    tft.setTextFont(2);
    tft.println(F("my foonting turlingdromes.")); // Can store strings in FLASH to save RAM
    tft.println("And hooptiously drangle me");
    tft.println("with crinkly bindlewurdles,");
    tft.println("Or I will rend thee in the gobberwarts with my blurglecruncheon, see if I don't!");

    float fnumber = 123.45;
    tft.setTextColor(TFT_BLUE);    tft.setTextFont(4);
    tft.print("Float = "); tft.println(fnumber);           // Print floating point number
    tft.print("Binary = "); tft.println((int)fnumber, BIN); // Print as integer value in binary
    tft.print("Hexadecimal = "); tft.println((int)fnumber, HEX); // Print as integer number in Hexadecimal
}

void loop() {
    uint16_t t_x = 0, t_y = 0; // To store the touch coordinates
    // Pressed will be set true is there is a valid touch on the screen
    bool pressed = tft.getTouch(&t_x, &t_y);
    if (pressed) {
        tft.fillCircle(t_x, t_y, random(64), random(0xFFFF));
        delay(100);
    }

}