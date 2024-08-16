#include "RDA5807M.h"
#include "esphome/core/hal.h"
#include "esphome/core/log.h"

namespace esphome {
namespace rda5807m {

static const char *const TAG = "rda5807m";

void RDA5807M::Init() {
    _mutex = xSemaphoreCreateMutex();

    xSemaphoreTake(_mutex, portMAX_DELAY);

    rda_reg2_t reg2 = { .value = 0 };
    reg2.ENABLE = 1;
    reg2.NEW_METHOD = 1;
    reg2.BASS = 1;
    reg2.MONO = 1;
    reg2.DMUTE = 1;
    reg2.DHIZ = 1;
    setRegister(RDA5807M_REG2, reg2.value);

    rda_reg4_t reg4 = { .value = 0 };
    reg4.DE = 1;
    setRegister(RDA5807M_REG4, reg4.value);

    rda_reg5_t reg5 = { .value = 0 };
    reg5.LNA_PORT_SEL = 2;
    reg5.SEEKTH = 8;
    setRegister(RDA5807M_REG5, reg5.value);

    rda_reg7_t reg7 = { .value = 0 };
    reg7.SOFTBLEND_EN = 1;
    reg7.TH_SOFRBLEND = 4;
    setRegister(RDA5807M_REG7, reg7.value);

    vTaskDelay(1000 / portTICK_RATE_MS);

    xSemaphoreGive(_mutex);
}

void RDA5807M::SetChannel(uint16_t value) {
    xSemaphoreTake(_mutex, portMAX_DELAY);

    rda_reg3_t reg3 = { .value = 0 };
    reg3.SPACE = 0;
    reg3.BAND = RADIO_BAND_WIDTH; //00 - 87..108МГц, 01 - 76..91МГц, 10 - 76..108МГц, 11 - 65..76МГц или 50..65МГц (определяется битом 65M_50M MODE регистра 07h)
    reg3.TUNE = 1;
    reg3.CHAN = value - RADIO_BAND_MIN;
    setRegister(RDA5807M_REG3, reg3.value);
    vTaskDelay(200 / portTICK_RATE_MS);
    waitTune();

    xSemaphoreGive(_mutex);
}

void RDA5807M::SetVolume(uint16_t value) {
    xSemaphoreTake(_mutex, portMAX_DELAY);

    rda_reg5_t reg5 = { .value = getRegister(RDA5807M_REG5) };
    reg5.VOLUME = value;
    setRegister(RDA5807M_REG5, reg5.value);
    vTaskDelay(100 / portTICK_RATE_MS);

    xSemaphoreGive(_mutex);
}

void RDA5807M::SetMute(bool value) {
    xSemaphoreTake(_mutex, portMAX_DELAY);

    rda_reg2_t reg2 = { .value = getRegister(RDA5807M_REG2) };
    reg2.DMUTE = !value;
    setRegister(RDA5807M_REG2, reg2.value);

    xSemaphoreGive(_mutex);
}

void RDA5807M::SetHardMute(bool value) {
    xSemaphoreTake(_mutex, portMAX_DELAY);

    rda_reg2_t reg2 = { .value = getRegister(RDA5807M_REG2) };
    reg2.DHIZ = !value;
    setRegister(RDA5807M_REG2, reg2.value);

    xSemaphoreGive(_mutex);
}

void RDA5807M::Seek(uint16_t seekth, uint16_t softblend, bool seekUp) {
    xSemaphoreTake(_mutex, portMAX_DELAY);

    rda_reg5_t reg5 = { .value = getRegister(RDA5807M_REG5) };
    rda_reg7_t reg7 = { .value = getRegister(RDA5807M_REG7) };
    if (reg5.SEEKTH != seekth) {
        reg5.SEEKTH = seekth;
        setRegister(RDA5807M_REG5, reg5.value);
    }
    if (reg7.TH_SOFRBLEND != softblend) {
        reg7.TH_SOFRBLEND = softblend;
        setRegister(RDA5807M_REG7, reg7.value);
    }
 
    rda_reg2_t reg2 = { .value = getRegister(RDA5807M_REG2) };
    reg2.SKMODE = 1;
    reg2.SEEK = 1;
    reg2.SEEKUP = seekUp ? 1: 0;
    setRegister(RDA5807M_REG2, reg2.value);
    vTaskDelay(300 / portTICK_RATE_MS);
    waitTune();

    xSemaphoreGive(_mutex);
}


uint16_t RDA5807M::GetChannel() {
    xSemaphoreTake(_mutex, portMAX_DELAY);
    rda_reg3_t reg3 = { .value = getRegister(RDA5807M_REG3) };

    xSemaphoreGive(_mutex);
    return reg3.CHAN + RADIO_BAND_MIN;
}

uint8_t RDA5807M::GetVolume() {
    xSemaphoreTake(_mutex, portMAX_DELAY);

    rda_reg5_t reg5 = { .value = getRegister(RDA5807M_REG5) };

    xSemaphoreGive(_mutex);
    return reg5.VOLUME;
}

bool RDA5807M::GetMute() {
    xSemaphoreTake(_mutex, portMAX_DELAY);

    rda_reg2_t reg2 = { .value = getRegister(RDA5807M_REG2) };

    xSemaphoreGive(_mutex);
    return reg2.DMUTE == 0;
}

bool RDA5807M::GetHardMute() {
    xSemaphoreTake(_mutex, portMAX_DELAY);

    rda_reg2_t reg2 = { .value = getRegister(RDA5807M_REG2) };

    xSemaphoreGive(_mutex);
    return reg2.DHIZ == 0;
}

uint8_t RDA5807M::GetRssi() {
    xSemaphoreTake(_mutex, portMAX_DELAY);

    rda_regb_t regb = { .value = getRegister(RDA5807M_REGB) };

    xSemaphoreGive(_mutex);
    return regb.RSSI;  
}

uint16_t RDA5807M::GetSeekTh() {
    xSemaphoreTake(_mutex, portMAX_DELAY);

    rda_reg5_t reg5 = { .value = getRegister(RDA5807M_REG5) };

    xSemaphoreGive(_mutex);
    return reg5.SEEKTH;  
}

uint16_t RDA5807M::GetSoftBlend() {
    xSemaphoreTake(_mutex, portMAX_DELAY);

    rda_reg7_t reg7 = { .value = getRegister(RDA5807M_REG7) };

    xSemaphoreGive(_mutex);
    return reg7.TH_SOFRBLEND;  
}

// PRIVATE

void RDA5807M::waitTune() {
    rda_rega_t rega;
    do {
        rega.value = getRegister(RDA5807M_REGA);
        if (rega.STC == 0) vTaskDelay(WaitTime / portTICK_RATE_MS);
    } while (rega.STC == 0);
}

uint16_t RDA5807M::getRegister(uint8_t reg) {
    uint16_t result;
    // Wire.beginTransmission(RDA5807M_RANDOM_ACCESS_ADDRESS);
    // Wire.write(reg);
    // Wire.endTransmission(false);
    // Wire.requestFrom((uint16_t)RDA5807M_RANDOM_ACCESS_ADDRESS, (uint8_t)2, true);
    // result = (uint16_t)Wire.read() << 8;
    // result |= Wire.read();

    I2CDevice::read_bytes_16(reg, &result, 1);
    return result;
}

void RDA5807M::setRegister(uint8_t reg, const uint16_t value) {
    // Wire.beginTransmission(RDA5807M_RANDOM_ACCESS_ADDRESS);
    // Wire.write(reg);
    // Wire.write(highByte(value));
    // Wire.write(lowByte(value));
    // Wire.endTransmission(true);
    I2CDevice::write_bytes_16(reg, &value, 1);
}
//-------------------------------------------------------------
void RDA5807M::volume_up() {
    ESP_LOGD(TAG, "volume_up");
    if (_volume == 0) return;
    _volume--;
    SetVolume(_volume);
}

void RDA5807M::volume_down() {
    ESP_LOGD(TAG, "volume_down");
    if (_volume >= 16) return;
    _volume++;
    SetVolume(_volume);
}

void RDA5807M::set_volume(uint8_t volume) {
    ESP_LOGD(TAG, "set_volume: %d", volume);
    if (volume > 16) volume = 16;
    _volume = volume;
    SetVolume(_volume);
}

void RDA5807M::toggle_mute() {
    ESP_LOGD(TAG, "toggle_mute");
    _mute = !_mute;
    SetHardMute(_mute);
}

void RDA5807M::set_band(uint16_t band) {
    ESP_LOGD(TAG, "set_band: %d", band);
    _band = band;
    SetChannel(_band);
}


void RDA5807M::setup() {
    ESP_LOGCONFIG(TAG, "Setting up RDA5807M...");

    _band = 1018;
    _volume = 2;
    _mute = true;
    Init();
    SetHardMute(_mute);
    SetChannel(_band);
    SetVolume(_volume);
}

void RDA5807M::dump_config() {
    ESP_LOGCONFIG(TAG, "RDA5807M:");
    LOG_I2C_DEVICE(this);
    if (this->is_failed()) {
        ESP_LOGE(TAG, "Communication with RDA5807M failed!");
    }
    // LOG_UPDATE_INTERVAL(this);
}


float RDA5807M::get_setup_priority() const { return setup_priority::DATA; }

// void RDA5807MComponent::update() {

// }

void RDA5807M::loop() {
}

}  // namespace rda5807m
}  // namespace esphome