#pragma once

#include "AddressableAbstractEffect.h"


namespace esphome {
namespace effects {

class AddressableSinusoidEffect : public AddressableAbstractEffect 
{
public:
    AddressableSinusoidEffect(const std::string &name) : AddressableAbstractEffect(name) {}

    void start() override
    {
        this->semi_width_major_ =  this->manager_->width() / 2  + (this->manager_->width() % 2);
        this->semi_height_major_ = this->manager_->height() / 2 + (this->manager_->height() % 2);
        this->e_s3_speed_ = 0.004 * this->update_interval_ + 0.015; // speed of the movement along the Lissajous curves
        this->e_s3_size_ = 3 * (float)this->scale_ / 100.0 + 2;    // amplitude of the curves
    }

    void apply(light::AddressableLight &it, const Color &current_color) override 
    {
        const uint32_t now = millis();
        if (now - this->last_run_ < this->update_interval_) {
            return;
        }

        this->last_run_ = now;

        const float time_shift = float(millis() % (uint32_t)(30000 * (1.0 / ((float)this->update_interval_ / 255))));

        for (uint8_t y = 0; y < this->manager_->height(); y++) {
            for (uint8_t x = 0; x < this->manager_->width(); x++) {
                Color color;

                float cx = y + float(this->e_s3_size_ * (sinf (float(this->e_s3_speed_ * 0.003 * time_shift)))) - this->semi_height_major_;  // the 8 centers the middle on a 16x16
                float cy = x + float(this->e_s3_size_ * (cosf (float(this->e_s3_speed_ * 0.0022 * time_shift)))) - this->semi_width_major_;
                float v = 127 * (1 + sinf ( sqrtf ( ((cx * cx) + (cy * cy)) ) ));
                color.red = v;

                cx = x + float(this->e_s3_size_ * (sinf (this->e_s3_speed_ * float(0.0021 * time_shift)))) - this->semi_width_major_;
                cy = y + float(this->e_s3_size_ * (cosf (this->e_s3_speed_ * float(0.002 * time_shift)))) - this->semi_height_major_;
                v = 127 * (1 + sinf ( sqrtf ( ((cx * cx) + (cy * cy)) ) ));
                color.blue = v;

                cx = x + float(this->e_s3_size_ * (sinf (this->e_s3_speed_ * float(0.0041 * time_shift)))) - this->semi_width_major_;
                cy = y + float(this->e_s3_size_ * (cosf (this->e_s3_speed_ * float(0.0052 * time_shift)))) - this->semi_height_major_;
                v = 127 * (1 + sinf ( sqrtf ( ((cx * cx) + (cy * cy)) ) ));
                color.green = v;
                
                it[getPixelNumber(x, y)] = color;
            }
        }

        it.schedule_show();
    }

protected:
    uint8_t semi_width_major_{0};
    uint8_t semi_height_major_{0};
    float e_s3_speed_{0.0};
    float e_s3_size_{0.0};
};

}  // namespace effects
}  // namespace esphome