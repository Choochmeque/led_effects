#pragma once

#include "AddressableAbstractEffect.h"


namespace esphome {
namespace effects {

class AddressableMatrixEffect : public AddressableAbstractEffect 
{
public:
    AddressableMatrixEffect(const std::string &name) : AddressableAbstractEffect(name) {}

    void apply(light::AddressableLight &it, const Color &current_color) override 
    {
        const uint32_t now = millis();
        if (now - this->last_run_ < this->update_interval_) {
            return;
        }

        this->last_run_ = now;

        for (uint8_t x = 0; x < WIDTH; x++) {
            const int led_num = getPixelNumber(x, HEIGHT - 1);
            
            // заполняем случайно верхнюю строку
            const Color thisColor = it[led_num].get();
            if (isEqualColors(thisColor, Color::BLACK))
                it[led_num] = (random(0, 25) == 0) ? RgbToHsv(0, 255, 0) : light::ESPHSVColor(0, 0, 0);
            else if (compareColors(thisColor, Color(0x002000)) < 0)
                it[led_num] = Color::BLACK;
            else
                it[led_num] = thisColor - Color(0x002000);
        }  

        // сдвигаем всё вниз
        for (uint8_t x = 0; x < WIDTH; x++) {
            for (uint8_t y = 0; y < HEIGHT - 1; y++) {
                it[getPixelNumber(x, y)] = it[getPixelNumber(x, y + 1)].get();
            }
        }
        it.schedule_show();
    }
};

}  // namespace effects
}  // namespace esphome