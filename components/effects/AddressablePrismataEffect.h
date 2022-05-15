#pragma once

#include "AddressableAbstractEffect.h"


namespace esphome {
namespace effects {

class AddressablePrismataEffect : public AddressableAbstractEffect 
{
public:
    AddressablePrismataEffect(const std::string &name) : AddressableAbstractEffect(name) {}

    void apply(light::AddressableLight &it, const Color &current_color) override 
    {
        const uint32_t now = millis();
        if (now - this->last_run_ < this->update_interval_) {
            return;
        }

        this->last_run_ = now;

        EVERY_N_MILLIS(33) {
            this->hue_++;
        }

        this->applyBlur2d(it, 20);
        this->dimAll(it, 255 - this->scale_ % 11);

        for (int x = 0; x < this->manager_->width(); x++) {
            uint8_t beat = (GET_MILLIS() * (accum88(x + 1)) * 28 * this->update_interval_) >> 17;
            uint8_t y = scale8(sin8(beat), this->manager_->height() - 1);
            it[getPixelNumber(x, y)] = ColorFromPalette(*GetColorPalette(this->scale_), x * 7 + this->hue_);
        }

        it.schedule_show();
    }

protected:
    uint8_t hue_{0};
};

}  // namespace effects
}  // namespace esphome