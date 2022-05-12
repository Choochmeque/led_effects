#pragma once

#include "AddressableAbstractEffect.h"


namespace esphome {
namespace effects {

class AddressableRainEffect : public AddressableAbstractEffect 
{
public:
    AddressableRainEffect(const std::string &name) : AddressableAbstractEffect(name) {}

    void apply(light::AddressableLight &it, const Color &current_color) override 
    {
        const uint32_t now = millis();
        if (now - this->last_run_ < this->update_interval_) {
            return;
        }

        this->last_run_ = now;

        for (uint8_t x = 0; x < this->manager_->width(); x++) {
            const int led_num = getPixelNumber(x, this->manager_->height() - 1);

            // заполняем случайно верхнюю строку
            const Color thisColor = it[led_num].get();
            if (isEqualColors(thisColor, Color::BLACK)) {
                if (random(0, 50) == 0) {
                    if (this->scale_ <= 1) {
                        it[led_num] = light::ESPHSVColor(random(0, 9) * 28, 255, 255);
                    } 
                    else if (this->scale_ == 100) {
                        it[led_num] = RgbToHsv(Color(0xE0FFFF - 0x101010 * random(0, 4)));
                    } 
                    else {
                        it[led_num] = light::ESPHSVColor(this->scale_ * 2.4 + random(0, 16), 255, 255);
                    }
                }
            } 
            else {
                // Shade pixel
                const Color color = it[led_num].get();
                ESP_LOGD("custom", "Colors1 : %d %d, %d %d, %d %d", color.r, color.red, color.g, color.green, color.b, color.blue);
                const Color c = color - light::ESPHSVColor(0, 0, random(96, 128)).to_rgb();
                ESP_LOGD("custom", "Colors2 : %d %d, %d %d, %d %d", c.r, c.red, c.g, c.green, c.b, c.blue);
                it[led_num] = RgbToHsv(c);
            }
        }
        // сдвигаем всё вниз
        for (uint8_t x = 0; x < this->manager_->width(); x++) {
            for (uint8_t y = 0; y < this->manager_->height() - 1; y++) {
                it[getPixelNumber(x, y)] = it[getPixelNumber(x, y + 1)].get();
            }
        }

        it.schedule_show();
    }
};

}  // namespace effects
}  // namespace esphome