#pragma once

#include "AddressableAbstractEffect.h"


namespace esphome {
namespace effects {

class AddressableStarfallEffect : public AddressableAbstractEffect 
{
public:
    AddressableStarfallEffect(const std::string &name) : AddressableAbstractEffect(name) {}

    void apply(light::AddressableLight &it, const Color &current_color) override 
    {
        const uint32_t now = millis();
        if (now - this->last_run_ < this->update_interval_) {
            return;
        }

        this->last_run_ = now;

        for (uint8_t i = this->manager_->height() / 2; i < this->manager_->height(); i++) {
            if (isEqualColors(it[getPixelNumber(0, i)].get(), Color::BLACK)
                    && (random(0, this->scale_) == 0)
                    && isEqualColors(it[getPixelNumber(0, i + 1)].get(), Color::BLACK)
                    && isEqualColors(it[getPixelNumber(0, i - 1)].get(), Color::BLACK)) {
                const uint8_t hue = random(0, 200);
                it[getPixelNumber(0, i)] = light::ESPHSVColor(hue, this->saturation_, 255);
            }
        }

        for (uint8_t i = 0; i < this->manager_->width() / 2; i++) {
            if (isEqualColors(it[getPixelNumber(i, this->manager_->height() - 1)].get(), Color::BLACK)
                    && (random(0, this->scale_) == 0)
                    && isEqualColors(it[getPixelNumber(i + 1, this->manager_->height() - 1)].get(), Color::BLACK)
                    && isEqualColors(it[getPixelNumber(i - 1, this->manager_->height() - 1)].get(), Color::BLACK)) {
                const uint8_t hue = random(0, 200);
                it[getPixelNumber(i, this->manager_->height() - 1)] = light::ESPHSVColor(hue, this->saturation_, 255);
            }
        }

        // сдвигаем по диагонали
        for (uint8_t y = 0; y < this->manager_->height() - 1; y++) {
            for (uint8_t x = this->manager_->width() - 1; x > 0; x--) {
                it[getPixelNumber(x, y)] = it[getPixelNumber(x - 1, y + 1)].get();
            }
        }

        // уменьшаем яркость левой и верхней линии, формируем "хвосты"
        for (uint8_t i = this->manager_->height() / 2; i < this->manager_->height(); i++) {
            fadePixelXY(it, 0, i, this->tail_step_);
        }
        for (uint8_t i = 0; i < this->manager_->width() / 2; i++) {
            fadePixelXY(it, i, this->manager_->height() - 1, this->tail_step_);
        }

        it.schedule_show();
    }

    void set_saturation(uint8_t saturation) { this->saturation_ = saturation; }

    void set_tail_step(uint8_t tail_step) { this->tail_step_ = tail_step; }

protected:
    uint8_t saturation_{150};
    uint8_t tail_step_{100};
};

}  // namespace effects
}  // namespace esphome