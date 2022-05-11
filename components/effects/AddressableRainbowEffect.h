#pragma once

#include "AddressableAbstractEffect.h"


namespace esphome {
namespace effects {

class AddressableRainbowEffect : public AddressableAbstractEffect 
{
public:
    AddressableRainbowEffect(const std::string &name) : AddressableAbstractEffect(name) {}

    void apply(light::AddressableLight &it, const Color &current_color) override 
    {
        const uint32_t now = millis();
        if (now - this->last_run_ < this->update_interval_) {
            return;
        }

        this->last_run_ = now;

        this->hue_ += 2;
        const auto jj = this->vertical_ ? this->manager_->height() : this->manager_->width();
        const auto ii = this->vertical_ ? this->manager_->width() : this->manager_->height();
        for (uint8_t j = 0; j < jj; j++) {
            const light::ESPHSVColor thisColor = light::ESPHSVColor((byte)(this->hue_ + j * this->scale_), 255, 255);
            for (uint8_t i = 0; i < ii; i++) {
                const auto pixel = this->vertical_ ? getPixelNumber(i, j) : getPixelNumber(j, i);
                it[pixel] = thisColor;
            }
        }

        it.schedule_show();
    }

    void set_vertical(bool vertical) { this->vertical_ = vertical; }

protected:
    uint8_t hue_{0};
    bool vertical_{true};
};

}  // namespace effects
}  // namespace esphome