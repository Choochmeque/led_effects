#pragma once

#include "AddressableAbstractEffect.h"


namespace esphome {
namespace effects {

class AddressableLightBallsEffect : public AddressableAbstractEffect 
{
public:
    AddressableLightBallsEffect(const std::string &name) : AddressableAbstractEffect(name) {}

    void apply(light::AddressableLight &it, const Color &current_color) override 
    {
        const uint32_t now = millis();
        if (now - this->last_run_ < this->update_interval_) {
            return;
        }

        this->last_run_ = now;

        this->paint_width_ = this->manager_->width() - this->thickness_ * 2;
        this->paint_height_ = this->manager_->height() - this->thickness_ * 2;

        // Apply some blurring to whatever's already on the matrix
        // Note that we never actually clear the matrix, we just constantly
        // blur it repeatedly. Since the blurring is 'lossy', there's
        // an automatic trend toward black -- by design.
        const uint8_t blurAmount = dim8_raw(beatsin8(3, 64, 100));
        applyBlur2d(it, blurAmount);

        // Use two out-of-sync sine waves
        const uint16_t i = beatsin16( 79, 0, 255); //91
        const uint16_t j = beatsin16( 67, 0, 255); //109
        const uint16_t k = beatsin16( 53, 0, 255); //73
        const uint16_t m = beatsin16( 97, 0, 255); //123

        // The color of each point shifts over time, each at a different speed.
        const uint32_t ms = millis() / (this->scale_ / 4 + 1);
        it[getPixelNumber(highByte(i * this->paint_width_) + this->thickness_,
                            highByte(j * this->paint_height_) + this->thickness_)] = light::ESPHSVColor(ms / 29, 200, 255);
        it[getPixelNumber(highByte(j * this->paint_width_) + this->thickness_,
                            highByte(k * this->paint_height_) + this->thickness_)] = light::ESPHSVColor(ms / 41, 200, 255);
        it[getPixelNumber(highByte(k * this->paint_width_) + this->thickness_,
                            highByte(m * this->paint_height_) + this->thickness_)] = light::ESPHSVColor(ms / 37, 200, 255);
        it[getPixelNumber(highByte(m * this->paint_width_) + this->thickness_,
                            highByte(i * this->paint_height_) + this->thickness_)] = light::ESPHSVColor(ms / 53, 200, 255);

        it.schedule_show();
    }

protected:
    uint8_t thickness_{1};

    uint8_t paint_width_{0};
    uint8_t paint_height_{0};
};

}  // namespace effects
}  // namespace esphome