#pragma once

#include "AddressableAbstractEffect.h"


namespace esphome {
namespace effects {

enum RainbowType
{
    Horizontal = 0,
    Vertical,
    Diagonal,
    Twirl
};

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

        if (this->first_run_) {
            this->first_run_ = false;

            maxDimension = max(this->manager_->width(), this->manager_->height());
            ratio = static_cast<float>(this->manager_->width()) / this->manager_->height();
        }

        if (this->rainbow_type_ == Horizontal) {
            this->hue_ += 2;
            for (uint8_t x = 0; x < this->manager_->width(); x++) {
                const light::ESPHSVColor thisColor = light::ESPHSVColor((byte)(this->hue_ + x * this->scale_), 255, 255);
                for (uint8_t y = 0; y < this->manager_->height(); y++) {
                    it[getPixelNumber(x, y)] = thisColor;
                }
            }
        }
        else if (this->rainbow_type_ == Vertical) {
            this->hue_ += 2;
            for (uint8_t y = 0; y < this->manager_->height(); y++) {
                const light::ESPHSVColor thisColor = light::ESPHSVColor((byte)(this->hue_ + y * this->scale_), 255, 255);
                for (uint8_t x = 0; x < this->manager_->width(); x++) {
                    it[getPixelNumber(x, y)] = thisColor;
                }
            }
        }
        else if (this->rainbow_type_ == Diagonal) {
            this->hue_ += 2;
            for (uint8_t x = 0; x < this->manager_->width(); x++) {
                const light::ESPHSVColor thisColor = light::ESPHSVColor((this->hue_ + x * this->scale_), 255, 255);
                for (uint8_t y = 0; y < this->manager_->height(); y++) {
                    it[getPixelNumber((x + y) % this->manager_->width(), y)] = thisColor;
                }
            }
        }
        else if (this->rainbow_type_ == Twirl) {
            this->hue_ += hueStep;
            float factor = (twirlFactor / 100.0f) * (this->scale_ / 100.0f);
            for (uint8_t x = 0; x < this->manager_->width(); x++) {
                for (uint8_t y = 0; y < this->manager_->height(); y++) {
                    light::ESPHSVColor thisColor = light::ESPHSVColor(static_cast<uint8_t>(hue + (ratio * x + y * factor) * (255.0f / maxDimension)), 255, 255);
                    it[getPixelNumber(x, y)] = thisColor;
                }
            }
        }

        it.schedule_show();
    }

    void set_rainbow_type(RainbowType rainbow_type) { this->rainbow_type_ = rainbow_type; }

protected:
    bool first_run_{true};
    uint8_t hue_{0};
    RainbowType rainbow_type_{Horizontal};

    uint8_t hue{0};
    uint8_t hueStep{8};
    uint16_t twirlFactor{300};

    uint8_t maxDimension{0};
    float ratio{0.0f};
};

}  // namespace effects
}  // namespace esphome