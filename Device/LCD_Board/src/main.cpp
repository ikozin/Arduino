#include <Arduino.h>
#include <TFT_eSPI.h>
#include <SD.h>

#ifndef ESP32
    #error ESP32
#endif


#if !defined(DRIVER_TEXT) && defined(ILI9486_DRIVER)
    #define DRIVER_TEXT "ILI9486_DRIVER"
#endif
#if !defined(DRIVER_TEXT) && defined(ILI9488_DRIVER)
    #define DRIVER_TEXT "ILI9488_DRIVER"
#endif
#if !defined(DRIVER_TEXT) && defined(ST7789_DRIVER)
    #define DRIVER_TEXT "ST7789_DRIVER"
#endif
#if !defined(DRIVER_TEXT)
    #define DRIVER_TEXT "UNKNOWN_DRIVER"
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
║ 3V3 ║ GND ║  5  ║     ║     ║ 23  ║ 18  ║     ║     ║ 18  ║     ║ 23  ║ 19  ║     ║
╚═════╩═════╩═════╩═════╩═════╩═════╩═════╩═════╩═════╩═════╩═════╩═════╩═════╩═════╝
╔═════╦═════╦═════╦═════╦═════╦═════╦═════╦═════╦═════╦═════╦═════╦═════╦═════╦═════╗
║     ║     ║     ║ 26  ║ 25  ║     ║     ║27/3V║     ║     ║ 32  ║     ║     ║     ║
╚═════╩═════╩═════╩═════╩═════╩═════╩═════╩═════╩═════╩═════╩═════╩═════╩═════╩═════╝



#define TFT_MISO    19
#define TFT_MOSI    23
#define TFT_SCLK    18
#define TFT_CS      5

#define TFT_DC      25
#define TFT_RST     26

*/
char text[128];

TFT_eSPI tft = TFT_eSPI();       // Invoke custom library
uint32_t backColors[] = { TFT_BLACK, TFT_WHITE, TFT_RED, TFT_GREEN, TFT_BLUE, TFT_MAGENTA, TFT_YELLOW, TFT_CYAN};

void touch_calibrate() {
    uint16_t calData[5];
    tft.fillScreen(TFT_BLACK);
    tft.setCursor(20, 0);
    tft.setTextFont(2);
    tft.setTextSize(1);
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.println("Touch corners as indicated");
    tft.calibrateTouch(calData, TFT_MAGENTA, TFT_BLACK, 15);
    tft.setTextFont(1);
    tft.setTextColor(TFT_GREEN, TFT_BLACK);
    tft.println("Calibration complete!");
    tft.setTouch(calData);
    for (int i = 0; i < sizeof(calData)/sizeof(calData[0]); i++) {
        sprintf(text, "%04X ", calData[i]);
        Serial.print(text);
    }
    Serial.println();
    delay(2000);
}

void setup() {
    Serial.begin(115200);
    Serial.println("setup");

    Serial.println("init video");
    tft.init();
    tft.setRotation(1);
    tft.fillScreen(random(0xFFFF));
    Serial.println(DRIVER_TEXT);
    tft.println(DRIVER_TEXT);

    touch_calibrate();

    Serial.println("init sd");
    tft.println("init sd");
    if (SD.begin()) {
        uint8_t cardType = SD.cardType();
        if (cardType != CARD_NONE) {
            Serial.print("SD Card Type: ");
            tft.print("SD Card Type: ");
            switch (cardType) {
                case CARD_MMC:
                    Serial.println("MMC");
                    tft.println("MMC");
                    break;
                case CARD_SD:
                    Serial.println("SDSC");
                    tft.println("SDSC");
                    break;
                case CARD_SDHC:
                    Serial.println("SDHC");
                    tft.println("SDHC");
                    break;
                default:
                    Serial.println("UNKNOWN");
                    tft.println("UNKNOWN");
                    break;
            }
            uint64_t cardSize = SD.cardSize() / (1024 * 1024);
            Serial.printf("SD Card Size: %lluMB\n", cardSize);
            tft.printf("SD Card Size: %lluMB\n", cardSize);
        } else {
            Serial.println("No SD card attached");
            tft.println("No SD card attached");
            return;
        }
    }
    else {
        Serial.println("Card Mount Failed");
        tft.println("Card Mount Failed");
        return;
    }
    delay(5000);
    tft.fillScreen(TFT_BLACK);
}

void listDir(fs::FS &fs, const char * dirname, uint8_t levels) {
    Serial.printf("Listing directory: %s\n", dirname);
    tft.printf("Listing directory: %s\n", dirname);

    File root = fs.open(dirname);
    if (!root) {
        Serial.println("Failed to open directory");
        tft.println("Failed to open directory");
        return;
    }
    if (!root.isDirectory()) {
        Serial.println("Not a directory");
        tft.println("Not a directory");
        return;
    }

    File file = root.openNextFile();
    while (file) {
        if (file.isDirectory()) {
            Serial.print("  DIR : ");
            tft.print("  DIR : ");
            Serial.println(file.name());
            tft.println(file.name());
            if (levels) {
                listDir(fs, file.name(), levels -1);
            }
        } else {
            Serial.print("  FILE: ");
            tft.print("  FILE: ");
            Serial.print(file.name());
            tft.print(file.name());
            Serial.print("  SIZE: ");
            tft.print("  SIZE: ");
            Serial.println(file.size());
            tft.println(file.size());
        }
        file = root.openNextFile();
    }
}

void loop() {
    // tft.setCursor(0, 0, 1);
    // for (int i = 0; i < (sizeof(backColors)/sizeof(backColors[0])); i++) {
    //     tft.fillScreen(backColors[i]);
    //     Serial.printf("BackColor: %d\n", backColors[i]);
    //     delay(1000);
    // }
    // tft.fillScreen(TFT_BLACK);
    // listDir(SD, "/", 0);

    uint16_t t_x = 0, t_y = 0; // To store the touch coordinates
    // Pressed will be set true is there is a valid touch on the screen
    bool pressed = tft.getTouch(&t_x, &t_y);
    if (pressed) {
        tft.fillCircle(t_x, t_y, random(64), random(0xFFFF));
        delay(100);
    }
}