#pragma once

#include "AddressableAbstractEffect.h"


namespace esphome {
namespace effects {

class AddressableSnowEffect : public AddressableAbstractEffect 
{
public:
    AddressableSnowEffect(const std::string &name) : AddressableAbstractEffect(name) {}

    void apply(light::AddressableLight &it, const Color &current_color) override 
    {
        const uint32_t now = millis();
        if (now - this->last_run_ < this->update_interval_) {
            return;
        }

        this->last_run_ = now;

        // сдвигаем всё вниз
        for (byte x = 0; x < this->manager_->width(); x++) {
            for (byte y = 0; y < this->manager_->height() - 1; y++) {
                it[getPixelNumber(x, y)] = it[getPixelNumber(x, y + 1)].get();
            }
        }
        
        for (byte x = 0; x < this->manager_->width(); x++) {
            // заполняем случайно верхнюю строку
            // а также не даём двум блокам по вертикали вместе быть
            if (isEqualColors(it[getPixelNumber(x, this->manager_->height() - 2)].get(), Color::BLACK) && (random(0, this->scale_) == 0)) {
                const Color c = Color(224, 255, 255) - Color(0x101010 * random(0, 4));
                it[getPixelNumber(x, this->manager_->height() - 1)] = RgbToHsv(c.red, c.green, c.blue);
            }
            else {
                it[getPixelNumber(x, this->manager_->height() - 1)] = Color::BLACK;
            }
        }

        it.schedule_show();
    }
};

}  // namespace effects
}  // namespace esphome