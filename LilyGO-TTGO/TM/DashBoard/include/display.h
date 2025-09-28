#pragma once

#include <Arduino.h>
#include <LovyanGFX.hpp>  // Подключение Библиотеки Lovyan GFX

#define TFT_MISO -1  // Must be defined even though it is not used
#define TFT_MOSI 23  // Connected to display SDA line
#define TFT_SCLK 18

#define TFT_CS   05
#define TFT_DC   16
#define TFT_RST  17

#define TFT_WIDTH  240
#define TFT_HEIGHT 320

// https://github.com/lovyan03/LovyanGFX
// https://lovyangfx.readthedocs.io/en/latest/
// https://adior.ru/index.php/robototekhnika/439-st7789

class LGFX : public lgfx::LGFX_Device {
    private:
        lgfx::Panel_ST7789  _panel_instance;        // Предлагается выбрать контроллер дисплея
        lgfx::Bus_SPI       _bus_instance;          // Выбрать тип шины
        // lgfx::Light_PWM     _light_instance;
        // lgfx::Touch_XPT2046 _touch_instance;

    public:
        LGFX(void) {
            {
                auto cfg = _bus_instance.config();  // Получите структуру для настроек шины.
                cfg.spi_host    = SPI2_HOST;        // Выберите SPI для использования (VSPI_HOST or HSPI_HOST)
                cfg.spi_mode    = 0;                // SPI Установить режим связи (0 ~ 3)
                cfg.freq_write  = 20000000;         // Тактовая частота SPI во время передачи (максимум 80 МГц, 80 МГц округляется до целого числа)
                cfg.freq_read   = 16000000;         // Частота SPI при приеме
                cfg.spi_3wire   = false;            // Установите значение true, если прием осуществляется на контакт MOSI.
                cfg.use_lock    = true;             // Установите true, чтобы использовать блокировку транзакции
                cfg.dma_channel = SPI_DMA_CH_AUTO;  // Использовать настройку канала DMA (1 или 2, 0=отключить) (0=не использовать DMA)
                cfg.pin_sclk    = TFT_SCLK;         // Установить номер вывода SPI SCLK SCK
                cfg.pin_mosi    = TFT_MOSI;         // Установите номер контакта SPI MOSI SDI
                cfg.pin_miso    = TFT_MISO;         // Установить номер контакта SPI MISO (-1 = отключить) SDO
                cfg.pin_dc      = TFT_DC;           // Установить номер контакта SPI D/C (-1 = отключить) RS
                // При использовании той же шины SPI, что и SD-карта, обязательно установите MISO, не пропуская его.
                _bus_instance.config(cfg);   // Применяет заданное значение к шине.
                _panel_instance.setBus(&_bus_instance);// Установите шину на панели.
            }
            {
                auto cfg = _panel_instance.config();// Получает структуру для настроек панели отображения.
                cfg.pin_cs           = TFT_CS;      // CS  номер контакта, к которому подключен (-1 = отключить)
                cfg.pin_rst          = TFT_RST;     // RST номер контакта, к которому подключен (-1 = отключить)
                cfg.pin_busy         = -1;          // BUSY номер контакта, к которому подключен (-1 = отключить)
                cfg.memory_width     = TFT_WIDTH;   // Максимальная ширина, поддерживаемая микросхемой драйвера
                cfg.memory_height    = TFT_HEIGHT;  // Максимальная высота, поддерживаемая микросхемой драйвера
                cfg.panel_width      = TFT_WIDTH;   // фактическая отображаемая ширина
                cfg.panel_height     = TFT_HEIGHT;  // реальная видимая высота
                cfg.offset_x         = 0;           // Величина смещения панели в направлении X
                cfg.offset_y         = 0;           // Величина смещения панели в направлении Y
                cfg.offset_rotation  = 0;           // Смещение значения направления вращения 0~7 (4~7 перевернуто)
                cfg.dummy_read_pixel = 16;          // Количество битов для фиктивного чтения перед считыванием пикселей
                cfg.dummy_read_bits  = 1;           // Количество битов для фиктивного чтения перед чтением данных вне пикселей
                cfg.readable         = false;       // Установите значение true, если данные можно прочитать
                cfg.invert           = false;       // Установите значение true, если яркость панели инвертирована.
                cfg.rgb_order        = false;       // установите значение true, если красная и синяя панели поменялись местами.
                cfg.dlen_16bit       = false;       // Панель для отправки в единицах 16-битной длины данных Установите значение true
                cfg.bus_shared       = false;       // Совместное использование шины с SD-картой Установите значение true
                _panel_instance.config(cfg);

            }
            setPanel(&_panel_instance);
        }
};
