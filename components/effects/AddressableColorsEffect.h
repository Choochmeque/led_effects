#pragma once

#include "AddressableAbstractEffect.h"


namespace esphome {
namespace effects {

class AddressableColorsEffect : public AddressableAbstractEffect 
{
public:
    AddressableColorsEffect(const std::string &name) : AddressableAbstractEffect(name) {}

    void apply(light::AddressableLight &it, const Color &current_color) override 
    {
        const uint32_t now = millis();
        if (now - this->last_run_ < this->update_interval_) {
            return;
        }

        this->last_run_ = now;

        this->hue_ += this->scale_;
        it.all() = light::ESPHSVColor(hue, 255, 255);

        it.schedule_show();
    }

protected:
    uint8_t hue_{0};
};

}  // namespace effects
}  // namespace esphome