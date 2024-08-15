#pragma once

#include "esphome/core/component.h"
#include "esphome/core/automation.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/i2c/i2c.h"


namespace esphome {
namespace rda5807m {

class RDA5807M : public Component, public i2c::I2CDevice {
    public:
        void volume_up();
        void volume_down();
        void set_volume(uint8_t volume);
        void toggle_mute();
        void set_band(uint16_t band);

    public:
        // ========== INTERNAL METHODS ==========
        // (In most use cases you won't need these)
        void setup() override;
        void dump_config() override;
        float get_setup_priority() const override;
        void loop() override;
};

template<typename... Ts> class VolumeUpAction : public Action<Ts...>, public Parented<RDA5807M> {
    void play(Ts... x) override { this->parent_->volume_up(); }
};

template<typename... Ts> class VolumeDownAction : public Action<Ts...>, public Parented<RDA5807M> {
    void play(Ts... x) override { this->parent_->volume_down(); }
};

template<typename... Ts> class SetVolumeAction : public Action<Ts...>, public Parented<RDA5807M> {
 public:
  TEMPLATABLE_VALUE(uint8_t, volume)

  void play(Ts... x) override {
    auto volume = this->volume_.value(x...);
    this->parent_->set_volume(volume);
  }
};

template<typename... Ts> class ToggleMuteAction : public Action<Ts...>, public Parented<RDA5807M> {
    void play(Ts... x) override { this->parent_->toggle_mute(); }
};

template<typename... Ts> class SetBandAction : public Action<Ts...>, public Parented<RDA5807M> {
 public:
  TEMPLATABLE_VALUE(uint16_t, volume)

  void play(Ts... x) override {
    auto band = this->volume_.value(x...);
    this->parent_->set_band(band);
  }
};



}  // namespace rda5807m
}  // namespace esphome