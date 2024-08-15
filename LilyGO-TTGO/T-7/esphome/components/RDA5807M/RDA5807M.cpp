#include "RDA5807M.h"
#include "esphome/core/hal.h"
#include "esphome/core/log.h"

namespace esphome {
namespace rda5807m {

static const char *const TAG = "rda5807m.device";

void RDA5807M::volume_up() {
    ESP_LOGD(TAG, "volume_up");
}

void RDA5807M::volume_down() {
    ESP_LOGD(TAG, "volume_down");
}

void RDA5807M::set_volume(uint8_t volume) {
    ESP_LOGD(TAG, "set_volume: %d", volume);
}

void RDA5807M::toggle_mute() {
    ESP_LOGD(TAG, "toggle_mute");
}

void RDA5807M::set_band(uint16_t band) {
    ESP_LOGD(TAG, "set_band: %d", band);
}


void RDA5807M::setup() {
    ESP_LOGCONFIG(TAG, "Setting up RDA5807M...");
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