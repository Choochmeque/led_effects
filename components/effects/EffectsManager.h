#pragma once

#ifdef USE_ARDUINO

#include "esphome/core/component.h"

namespace esphome {
namespace effects {

class EffectsManager : public esphome::Component 
{
public:
    EffectsManager() {}
    ~EffectsManager() {}

    void set_width(uint8_t width) { this->width_ = width; }
    void set_height(uint8_t height) { this->height_ = height; }

    uint8_t width() const { return this->width_; }
    uint8_t height() const { return this->height_; }

    uint32_t num_leds() const { return this->width_ * this->height_; }

protected:
    uint8_t width_;
    uint8_t height_;
};

}  // namespace effects
}  // namespace esphome

#endif  // USE_ARDUINO
