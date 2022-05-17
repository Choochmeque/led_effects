#pragma once

#include "AddressableAbstractEffect.h"


namespace esphome {
namespace effects {

class AddressableMetaBallsEffect : public AddressableAbstractEffect 
{
public:
    AddressableMetaBallsEffect(const std::string &name) : AddressableAbstractEffect(name) {}

    void apply(light::AddressableLight &it, const Color &current_color) override 
    {
        const uint32_t now = millis();
        if (now - this->last_run_ < this->update_interval_) {
            return;
        }

        this->last_run_ = now;

        float speed = this->update_interval_ / 127.0;

        // get some 2 random moving points
        uint8_t x2 = inoise8(millis() * speed, 25355, 685 ) / this->manager_->width();
        uint8_t y2 = inoise8(millis() * speed, 355, 11685 ) / this->manager_->height();

        uint8_t x3 = inoise8(millis() * speed, 55355, 6685 ) / this->manager_->width();
        uint8_t y3 = inoise8(millis() * speed, 25355, 22685 ) / this->manager_->height();

        // and one Lissajou function
        uint8_t x1 = beatsin8(23 * speed, 0, 15);
        uint8_t y1 = beatsin8(28 * speed, 0, 15);

        for (uint8_t y = 0; y < this->manager_->height(); y++) {
            for (uint8_t x = 0; x < this->manager_->width(); x++) {

                // calculate distances of the 3 points from actual pixel
                // and add them together with weightening
                uint8_t  dx =  abs(x - x1);
                uint8_t  dy =  abs(y - y1);
                uint8_t dist = 2 * sqrt((dx * dx) + (dy * dy));

                dx =  abs(x - x2);
                dy =  abs(y - y2);
                dist += sqrt((dx * dx) + (dy * dy));

                dx =  abs(x - x3);
                dy =  abs(y - y3);
                dist += sqrt((dx * dx) + (dy * dy));

                // inverse result
                //byte color = modes[currentMode].Speed * 10 / dist;
                uint8_t color = 1000 / dist;

                // map color between thresholds
                if (color > 0 && color < 60) {
                    if (this->scale_ == 100) {
                        it[getPixelNumber(x, y)] = light::ESPHSVColor(color * 9, 255, 255);
                    }
                    else {
                        it[getPixelNumber(x, y)] = ColorFromPalette(*GetColorPalette(this->scale_), color * 9);
                    }
                } 
                else {
                    if (settings.scale == 100) {
                        it[getPixelNumber(x, y)] = light::ESPHSVColor(0, 255, 255);
                    } 
                    else {
                        it[getPixelNumber(x, y)] = ColorFromPalette(*GetColorPalette(this->scale_), 0);
                    }
                }
                // show the 3 points, too
                it[getPixelNumber(x1, y1)] = light::ESPHSVColor(255, 255, 255);
                it[getPixelNumber(x2, y2)] = light::ESPHSVColor(255, 255, 255);
                it[getPixelNumber(x3, y3)] = light::ESPHSVColor(255, 255, 255);
            }
        }

        it.schedule_show();
    }
};

}  // namespace effects
}  // namespace esphome