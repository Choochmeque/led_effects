#pragma once

#include "AddressableAbstractEffect.h"


namespace esphome {
namespace effects {

class AddressablePulseCirclesEffect : public AddressableAbstractEffect 
{
public:
    AddressablePulseCirclesEffect(const std::string &name) : AddressableAbstractEffect(name) {}

    void start() override
    {
        this->pulse_center_x_ = random8(this->manager_->width() - 5) + 3;
        this->pulse_center_y_ = random8(this->manager_->height() - 5) + 3;
    }

    void apply(light::AddressableLight &it, const Color &current_color) override 
    {
        const uint32_t now = millis();
        if (now - this->last_run_ < this->update_interval_) {
            return;
        }

        this->last_run_ = now;

        // Dim all
        it.all().fade_to_black(248);

        uint8_t _sat;
        if (this->step_ <= this->current_radius_) {
            for (uint8_t i = 0; i < this->step_; i++ ) {
                uint8_t _dark = qmul8(2, cos8 (128 / (this->step_ + 1) * (i + 1)));
                light::ESPHSVColor _pulse_color;
                switch (this->mode_) {
                case 1: // random circles
                    _pulse_color = light::ESPHSVColor(this->hue_, 255, _dark);
                    break;
                case 2: // changing colored circles
                    this->delta_hue2_ = this->scale_;
                    _pulse_color = light::ESPHSVColor(this->hue2_, 255, _dark);
                    break;
                case 3:  // manual colored circles
                    this->delta_hue_ = this->scale_ * 2.55;
                    _pulse_color = light::ESPHSVColor(this->delta_hue_, 255, _dark);
                    break;
                case 4: // rainbow colored circles
                    this->delta_hue_ += this->scale_;
                    _pulse_color = light::ESPHSVColor(this->delta_hue_, 255, _dark);
                    break;
                case 5: // manual rainbow colored circles
                    _sat =  qsub8(255, cos8 (128 / (this->step_ + 1) * (i + 1))) ;
                    this->delta_hue_ += this->scale_;
                    _pulse_color = light::ESPHSVColor(this->delta_hue_, _sat, _dark);
                    break;
                case 6: // manual colored bubbles
                    _sat =  qsub8(255, cos8 (128 / (this->step_ + 1) * (i + 1))) ;
                    this->delta_hue_ = this->scale_ * 2.55;
                    _pulse_color = light::ESPHSVColor(this->delta_hue_, _sat, _dark);
                    break;
                case 7: // changing colored bubbles
                    _sat =  qsub8(255, cos8 (128 / (this->step_ + 1) * (i + 1))) ;
                    this->delta_hue2_ = this->scale_;
                    _pulse_color = light::ESPHSVColor(this->hue2_, _sat, _dark);
                    break;
                case 8: // random bubbles
                    _sat =  qsub8(255, cos8 (128 / (this->step_ + 1) * (i + 1))) ;
                    this->delta_hue_ = this->hue_;
                    _pulse_color = light::ESPHSVColor(this->delta_hue_, _sat, _dark);
                    break;
                }
                _drawCircle(it, this->pulse_center_x_, this->pulse_center_y_, i, _pulse_color);
            }
        } 
        else {
            this->pulse_center_x_ = random8(this->manager_->width() - 5) + 3;
            this->pulse_center_y_ = random8(this->manager_->height() - 5) + 3;
            this->hue2_ += this->delta_hue2_;
            this->hue_ = random8(0, 255);
            this->current_radius_ = random8(3, 9);
            this->step_ = 0;
        }
        this->step_++;

        it.schedule_show();
    }

    void _drawCircle(light::AddressableLight &it, uint8_t x0, uint8_t y0, uint8_t radius, const light::ESPHSVColor& color) {
        uint8_t a = radius, b = 0;
        int radiusError = 1 - a;

        if (radius == 0) {
            it[getPixelNumber(x0, y0)] = color;
            return;
        }

        while (a >= b)  {
            it[getPixelNumber(a + x0, b + y0)] = color;
            it[getPixelNumber(b + x0, a + y0)] = color;
            it[getPixelNumber(-a + x0, b + y0)] = color;
            it[getPixelNumber(-b + x0, a + y0)] = color;
            it[getPixelNumber(-a + x0, -b + y0)] = color;
            it[getPixelNumber(-b + x0, -a + y0)] = color;
            it[getPixelNumber(a + x0, -b + y0)] = color;
            it[getPixelNumber(b + x0, -a + y0)] = color;
            b++;
            if (radiusError < 0) {
                radiusError += 2 * b + 1;
            } 
            else {
                a--;
                radiusError += 2 * (b - a + 1);
            }
        }
    }

protected:
    uint8_t pulse_center_x_{0};
    uint8_t pulse_center_y_{0};

    uint8_t mode_{1}; // TODO:
    uint8_t current_radius_{4};

    uint8_t step_{0};
    uint8_t delta_hue_{0};
    uint8_t delta_hue2_{0};
    uint8_t hue_{0};
    uint8_t hue2_{0};

    const uint8_t limit_steps_{6};
    const float fade_rate_{0.8f};
};

}  // namespace effects
}  // namespace esphome