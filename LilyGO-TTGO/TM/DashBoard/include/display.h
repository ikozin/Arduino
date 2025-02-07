#pragma once

#include <Arduino.h>
#include <LovyanGFX.hpp>  // Подключение Библиотеки Lovyan GFX

#define TFT_MISO 19  // Must be defined even though it is not used
#define TFT_MOSI 23  // Connected to display SDA line
#define TFT_SCLK 18

#define TFT_CS   05
#define TFT_DC   16
#define TFT_RST  17

#define TOUCH_CS -1

#define TFT_WIDTH  240
#define TFT_HEIGHT 320

// https://github.com/lovyan03/LovyanGFX
// https://lovyangfx.readthedocs.io/en/latest/
// https://adior.ru/index.php/robototekhnika/439-st7789

class LGFX : public lgfx::LGFX_Device {
    private:
        lgfx::Panel_ST7789  _panel_instance;        // Предлагается выбрать контроллер дисплея
        lgfx::Bus_SPI       _bus_instance;          // Выбрать тип шины
    public:
        LGFX(void) {
            {
                auto cfg = _bus_instance.config();

                cfg.spi_host = SPI2_HOST;               // Выбор номера шины SPI в микроконтроллере
                cfg.freq_write = 80000000;              // Частота передачи данных
                cfg.freq_read = 60000000;
                cfg.dma_channel = SPI_DMA_CH_AUTO;      // Канал DirectMemoryAccess
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
                cfg.panel_width      =   TFT_WIDTH;
                cfg.panel_height     =   TFT_HEIGHT;
                cfg.invert           =  false;          // Инвертирование цвета (необходимо при неправильном отображении цвета)
                _panel_instance.config(cfg);
            }
            setPanel(&_panel_instance);
        }
};
