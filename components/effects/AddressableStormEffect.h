#pragma once

#include "AddressableAbstractEffect.h"


namespace esphome {
namespace effects {

class AddressableStormEffect : public AddressableAbstractEffect 
{
public:
    AddressableStormEffect(const std::string &name) : AddressableAbstractEffect(name) {}

    void apply(light::AddressableLight &it, const Color &current_color) override 
    {
        const uint32_t now = millis();
        if (now - this->last_run_ < this->update_interval_) {
            return;
        }

        this->last_run_ = now;

        if (this->is_colored_) {
            this->saturation_ = this->scale_ * 2.55;
        } 
        else {
            this->tail_step_ = 255 - this->scale_ * 2.55;
        }

        for (int8_t x = 0; x < this->manager_->width() - 1; x++) {
            if (!random8(this->snow_density_) &&
                    isEqualColors(it[getPixelNumber(wrapX(x), this->manager_->height() - 1)].get(), Color::BLACK) &&
                    isEqualColors(it[getPixelNumber(wrapX(x + 1), this->manager_->height() - 1)].get(), Color::BLACK) &&
                    isEqualColors(it[getPixelNumber(wrapX(x - 1), this->manager_->height() - 1)].get(), Color::BLACK)) {
                it[getPixelNumber(x, this->manager_->height() - 1)] = light::ESPHSVColor(random8(), this->saturation_, random8(64, 255));
            }
        }

        for (int8_t y = 0; y < this->manager_->height() - 1; y++) {
            for (int8_t x = 0; x < this->manager_->width(); x++) {
                it[getPixelNumber(wrapX(x + 1), y)] = it[getPixelNumber(x, y + 1)].get();
            }
        }

        for (int8_t x = 0; x < this->manager_->width(); x++) {
            fadePixelXY(it, x, this->manager_->height() - 1, this->tail_step_);
        }

        it.schedule_show();
    }

protected:
    bool is_colored_{false};
    uint8_t snow_density_{32};

    uint8_t saturation_{0};
    uint8_t tail_step_{127};
};

}  // namespace effects
}  // namespace esphome