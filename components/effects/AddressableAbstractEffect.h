#pragma once

#include "esphome/core/component.h"
#include "esphome/components/light/esp_hsv_color.h"
#include "esphome/components/light/addressable_light_effect.h"

namespace esphome {
namespace effects {

class AddressableAbstractEffect : public light::AddressableLightEffect 
{
public:
    AddressableAbstractEffect(const std::string &name) : AddressableLightEffect(name) {}

    void set_update_interval(uint32_t update_interval) { this->update_interval_ = update_interval; }

    void set_scale(uint8_t scale) { this->scale_ = scale; }

protected:
    uint32_t last_run_{0};
    uint32_t update_interval_;
    uint8_t scale_;
};

}  // namespace effects
}  // namespace esphome