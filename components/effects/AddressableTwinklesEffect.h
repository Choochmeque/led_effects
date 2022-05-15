#pragma once

#include "AddressableAbstractEffect.h"


namespace esphome {
namespace effects {

class AddressableTwinklesEffect : public AddressableAbstractEffect 
{
public:
    AddressableTwinklesEffect(const std::string &name) : AddressableAbstractEffect(name) {}

    void start() override
    {
        this->hue_ = 0;
        this->ledsbuff_.resize(this->manager_->num_leds());
        for (uint32_t idx = 0; idx < this->manager_->num_leds(); idx++) {
            if (random8(this->scale_ % 11) == 0) {
                ledsbuff[idx].r = random8();
                ledsbuff[idx].g = random8(1, this->speed_ * 2 + 1);
                ledsbuff[idx].b = random8();
            } 
            else {
                ledsbuff[idx] = 0;
            }
        }
    }

    void apply(light::AddressableLight &it, const Color &current_color) override 
    {
        const uint32_t now = millis();
        if (now - this->last_run_ < this->update_interval_) {
            return;
        }

        this->last_run_ = now;

        for (uint16_t idx = 0; idx < this->manager_->num_leds(); idx++) {
            if (ledsbuff[idx].b == 0){
                if (random8(this->scale_ % 11) == 0 && this->hue_ > 0) {
                    ledsbuff[idx].r = random8();
                    ledsbuff[idx].g = random8(1, this->speed_ + 1);
                    ledsbuff[idx].b = ledsbuff[idx].g;
                    this->hue_--;
                }
            } 
            else if (ledsbuff[idx].g <= this->speed_) {
                if (ledsbuff[idx].b > 255 - ledsbuff[idx].g - this->mult_) {
                    ledsbuff[idx].b = 255;
                    ledsbuff[idx].g = ledsbuff[idx].g + this->speed_;
                } 
                else {
                    ledsbuff[idx].b = ledsbuff[idx].b + ledsbuff[idx].g + this->mult_;
                }
            } 
            else {
                if (ledsbuff[idx].b <= ledsbuff[idx].g - this->speed_ + this->mult_) {
                    ledsbuff[idx].b = 0;
                    this->hue_++;
                } 
                else {
                    ledsbuff[idx].b = ledsbuff[idx].b - ledsbuff[idx].g + this->speed_ - this->mult_;
                }
            }
            if (ledsbuff[idx].b == 0) {
                it[idx] = Color::BLACK;
            } 
            else {
                it[idx] = ColorFromPalette(*GetColorPalette(this->scale_),
                                            ledsbuff[idx].r,
                                            ledsbuff[idx].b);
            }
        }

        it.schedule_show();
    }

protected:
    uint8_t hue_{0};
    std::vector<Color> ledsbuff_;

    // settings
    uint8_t speed_{4};
    uint8_t mult_{6};
};

}  // namespace effects
}  // namespace esphome