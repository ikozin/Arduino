#pragma once

#include "esphome/core/component.h"
#include "esphome/core/automation.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/i2c/i2c.h"

namespace esphome {
namespace radio {

class Radio : public Component, public i2c::I2CDevice {
    public:
        void set_volume(uint8_t volume);
        void volume_up();
        void volume_down();

        void set_mute(bool mute);
        void toggle_mute();

        void set_band(uint16_t band);
    protected:
        uint16_t    _band;
        uint8_t     _volume;
        bool        _mute;
    public:
        // ========== INTERNAL METHODS ==========
        // (In most use cases you won't need these)
        void setup() override;
        void dump_config() override;
        float get_setup_priority() const override;
        void loop() override;
};


template<typename... Ts> class SetVolumeAction : public Action<Ts...>, public Parented<Radio> {
 public:
  TEMPLATABLE_VALUE(uint8_t, volume)

  void play(Ts... x) override {
    auto volume = this->volume_.value(x...);
    this->parent_->set_volume(volume);
  }
};


template<typename... Ts> class VolumeUpAction : public Action<Ts...>, public Parented<Radio> {
    void play(Ts... x) override { this->parent_->volume_up(); }
};


template<typename... Ts> class VolumeDownAction : public Action<Ts...>, public Parented<Radio> {
    void play(Ts... x) override { this->parent_->volume_down(); }
};


template<typename... Ts> class SetMuteAction : public Action<Ts...>, public Parented<Radio> {
 public:
  TEMPLATABLE_VALUE(bool, mute)

  void play(Ts... x) override {
    auto mute = this->mute_.value(x...);
    this->parent_->set_mute(mute);
  }
};


template<typename... Ts> class ToggleMuteAction : public Action<Ts...>, public Parented<Radio> {
    void play(Ts... x) override { this->parent_->toggle_mute(); }
};


template<typename... Ts> class SetBandAction : public Action<Ts...>, public Parented<Radio> {
 public:
  TEMPLATABLE_VALUE(uint16_t, band)

  void play(Ts... x) override {
    auto band = this->band_.value(x...);
    this->parent_->set_band(band);
  }
};


}  // namespace radio
}  // namespace esphome