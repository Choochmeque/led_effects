#pragma once

#include "AddressableAbstractEffect.h"


namespace esphome {
namespace effects {

class AddressableSinusoidEffect : public AddressableAbstractEffect 
{
public:
    AddressableSinusoidEffect(const std::string &name) : AddressableAbstractEffect(name) {}

    void apply(light::AddressableLight &it, const Color &current_color) override 
    {
        const uint32_t now = millis();
        if (now - this->last_run_ < this->update_interval_) {
            return;
        }

        this->last_run_ = now;

        // TODO: initialize once?
        const uint8_t semiHeightMajor = this->manager_->height() / 2 + (this->manager_->height() % 2);
        const uint8_t semiWidthMajor =  this->manager_->width() / 2  + (this->manager_->width() % 2) ;
        const float e_s3_speed = 0.004 * this->update_interval_ + 0.015; // speed of the movement along the Lissajous curves
        const float e_s3_size = 3 * (float)this->scale_ / 100.0 + 2;    // amplitude of the curves

        const float time_shift = float(millis() % (uint32_t)(30000 * (1.0 / ((float)this->update_interval_ / 255))));

        for (uint8_t y = 0; y < this->manager_->height(); y++) {
            for (uint8_t x = 0; x < this->manager_->width(); x++) {
                Color color;

                float cx = y + float(e_s3_size * (sinf (float(e_s3_speed * 0.003 * time_shift)))) - semiHeightMajor;  // the 8 centers the middle on a 16x16
                float cy = x + float(e_s3_size * (cosf (float(e_s3_speed * 0.0022 * time_shift)))) - semiWidthMajor;
                float v = 127 * (1 + sinf ( sqrtf ( ((cx * cx) + (cy * cy)) ) ));
                color.red = v;

                cx = x + float(e_s3_size * (sinf (e_s3_speed * float(0.0021 * time_shift)))) - semiWidthMajor;
                cy = y + float(e_s3_size * (cosf (e_s3_speed * float(0.002 * time_shift)))) - semiHeightMajor;
                v = 127 * (1 + sinf ( sqrtf ( ((cx * cx) + (cy * cy)) ) ));
                color.blue = v;

                cx = x + float(e_s3_size * (sinf (e_s3_speed * float(0.0041 * time_shift)))) - semiWidthMajor;
                cy = y + float(e_s3_size * (cosf (e_s3_speed * float(0.0052 * time_shift)))) - semiHeightMajor;
                v = 127 * (1 + sinf ( sqrtf ( ((cx * cx) + (cy * cy)) ) ));
                color.green = v;
                
                it[getPixelNumber(x, y)] = color;
            }
        }

        it.schedule_show();
    }
};

}  // namespace effects
}  // namespace esphome