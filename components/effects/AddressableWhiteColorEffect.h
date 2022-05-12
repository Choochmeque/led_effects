#pragma once

#include "AddressableAbstractEffect.h"


namespace esphome {
namespace effects {

class AddressableWhiteColorEffect : public AddressableAbstractEffect 
{
public:
    AddressableWhiteColorEffect(const std::string &name) : AddressableAbstractEffect(name) {}

    void apply(light::AddressableLight &it, const Color &current_color) override 
    {
        const uint32_t now = millis();
        if (now - this->last_run_ < this->update_interval_) {
            return;
        }

        this->last_run_ = now;

        const uint8_t centerY = max((float)round(this->manager_->width() / 2.0f) - 1.0f, 0.0f);
        const uint8_t bottomOffset = (uint8_t)(!(this->manager_->height() & 1) && (this->manager_->height() > 1));
        
        for (int16_t y = centerY; y >= 0; y--) {
            light::ESPHSVColor color = light::ESPHSVColor(
                        45,
                        map(this->update_interval_, 0, 255, 0, 170),
                        y == centerY
                        ? 255
                        : (this->scale_ / 100.0f) > ((centerY + 1.0f) - (y + 1.0f)) / (centerY + 1.0f) ? 255 : 0);

            for (uint8_t x = 0; x < this->manager_->width(); x++) {
                it[getPixelNumber(x, y)] = color;
                it[getPixelNumber(x, max((uint8_t)(this->manager_->height() - 1) - (y + 1) + bottomOffset, 0))] = color;
            }
        }

        it.schedule_show();
    }
};

}  // namespace effects
}  // namespace esphome