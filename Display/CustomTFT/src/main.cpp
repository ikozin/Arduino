#include <Arduino.h>
#include <FS.h>
#include <SPIFFS.h>

// https://learn.adafruit.com/adafruit-gfx-graphics-library?view=all
// https://learn.adafruit.com/adafruit-gfx-graphics-library/using-fonts?view=all

#define TFT_MISO 19  // Must be defined even though it is not used
#define TFT_MOSI 23  // Connected to display SDA line
#define TFT_SCLK 18

#define TFT_CS   05
#define TFT_DC   16
#define TFT_RST  17

#define TOUCH_CS -1

#define TFT_WIDTH  240
#define TFT_HEIGHT 320

#include <LovyanGFX.hpp>  // Подключение Библиотеки Lovyan GFX
#include <SPI.h>          // Подключение Библиотеки SPI
#include "image320x240x16.h"
#include <lgfx\Fonts\GFXFF\FreeMonoBoldOblique24pt7b.h>
#include <lgfx\Fonts\Custom\Orbitron_Light_32.h>

class LGFX : public lgfx::LGFX_Device
{
  lgfx::Panel_ST7789      _panel_instance;    // Предлагается выбрать контроллер дисплея
  lgfx::Bus_SPI        _bus_instance;         // Выбрать тип шины

public:

  LGFX(void)
  {
    {
      auto cfg = _bus_instance.config();

      cfg.spi_host = SPI2_HOST;              // Выбор номера шины SPI в микроконтроллере
      cfg.freq_write = 80000000;             // Частота передачи данных
      cfg.freq_read = 60000000;
      cfg.dma_channel = SPI_DMA_CH_AUTO;     // Канал DirectMemoryAccess
      cfg.pin_sclk = TFT_SCLK;
      cfg.pin_mosi = TFT_MOSI;
      cfg.pin_dc   = TFT_DC;
      _bus_instance.config(cfg);
      _panel_instance.setBus(&_bus_instance);
    }
    {
      auto cfg = _panel_instance.config();
      cfg.pin_cs           =   TFT_CS;
      cfg.pin_rst          =   TFT_RST;
      cfg.panel_width      =   240;
      cfg.panel_height     =   320;
      cfg.invert           =  false;        // Инвертирование цвета (необходимо при неправильном отображении цвета)
      _panel_instance.config(cfg);
    }
    setPanel(&_panel_instance);
  }
};

LGFX lcd;
static LGFX_Sprite sprite;


void setup() {
    lcd.init();
    lcd.setColorDepth(16);
    lcd.setRotation(1);

    sprite.setBuffer(const_cast<std::uint8_t*>(image320x240x16), 320, 240, 16);
    sprite.pushSprite(&lcd, 0, 0);
    delay(1000);
    lcd.clear(TFT_BLACK);
}

uint16_t color = 0;
void loop() {
    lcd.setTextColor(TFT_WHITE);
    lcd.setTextDatum(MC_DATUM);
    lcd.drawString("12:33", lcd.width() >> 1, lcd.height() >> 1, &fonts::FreeMonoBold24pt7b);
    // lcd.setFont(&fonts::Orbitron_Light_32);
    // lcd.setCursor(lcd.width() >> 1, lcd.height() >> 1);
    // lcd.print("12:34");
    // color += 0x020408;
    delay(1000);
}
