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
        for (byte j = 0; j < HEIGHT; j++) {
            const light::ESPHSVColor thisColor = light::ESPHSVColor((byte)(this->hue_ + j * 18), 255, 255);
            for (byte i = 0; i < WIDTH; i++) {
                it[getPixelNumber(i, j)] = thisColor;
            }
        }

        it.schedule_show();
    }

protected:
    uint8_t hue_{0};
};

}  // namespace effects
}  // namespace esphome