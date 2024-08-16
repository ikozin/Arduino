#include "esphome/core/hal.h"
#include "esphome/core/log.h"
#include "radio.h"


// https://esphome.io/components/sensor/custom#logging-in-custom-components

namespace esphome {
namespace radio {

static const char *const TAG = "radio";

void Radio::set_volume(uint8_t volume) {
    ESP_LOGD(TAG, "set_volume: %d", volume);
}

void Radio::volume_up() {
    ESP_LOGD(TAG, "volume_up");
}

void Radio::volume_down() {
    ESP_LOGD(TAG, "volume_down");
}

void Radio::set_mute(bool mute) {
    ESP_LOGD(TAG, "set_mute: %d", mute);
}

void Radio::toggle_mute() {
    ESP_LOGD(TAG, "toggle_mute");
}

void Radio::set_band(uint16_t band) {
    ESP_LOGD(TAG, "set_band: %d", band);
}

void Radio::setup() {
    ESP_LOGCONFIG(TAG, "Setting up RDA5807M...");
}

void Radio::dump_config() {
    ESP_LOGCONFIG(TAG, "Radio:");
    LOG_I2C_DEVICE(this);
    if (this->is_failed()) {
        ESP_LOGE(TAG, "Communication with Radio failed!");
    }
}

float Radio::get_setup_priority() const {
    // https://github.com/esphome/esphome/blob/dev/esphome/core/component.h
    return setup_priority::HARDWARE;
}

void Radio::loop() {
}

}  // namespace radio
}  // namespace esphome
