#pragma once

#include "AddressableAbstractEffect.h"


namespace esphome {
namespace effects {

class AddressableMovingCubeEffect : public AddressableAbstractEffect 
{
public:
    AddressableMovingCubeEffect(const std::string &name) : AddressableAbstractEffect(name) {}

    void apply(light::AddressableLight &it, const Color &current_color) override 
    {
        const uint32_t now = millis();
        if (now - this->last_run_ < this->update_interval_) {
            return;
        }

        this->last_run_ = now;

        if (this->first_run_) {
            this->first_run_ = false;
            
            coordB.resize(2);;
            vectorB.resize(2);

            for (uint8_t i = 0; i < 2; i++) {
                coordB[i] = this->manager_->width() / 2 * 10;
                vectorB[i] = random(8, 20);
            }

            ballColor = light::ESPHSVColor(random(0, 9) * 28, 255, 255);
        }

        ballSize = map(this->scale_ * 2.55, 0, 255, 2,
                    max(min(this->manager_->width(),
                            this->manager_->height()) / 3, 2));

        for (uint8_t i = 0; i < 2; i++) {
            coordB[i] += vectorB[i];
            if (coordB[i] < 0) {
                coordB[i] = 0;
                vectorB[i] = -vectorB[i];
                if (this->random_color_) {
                    ballColor = light::ESPHSVColor(random(0, 9) * 28, 255, 255);
                }
            }
        }

        if (coordB[0] > (int16_t)((this->manager_->width() - ballSize) * 10)) {
            coordB[0] = (this->manager_->width() - ballSize) * 10;
            vectorB[0] = -vectorB[0];
            if (this->random_color_) {
                ballColor = light::ESPHSVColor(random(0, 9) * 28, 255, 255);
            }
        }
        if (coordB[1] > (int16_t)((this->manager_->height() - ballSize) * 10)) {
            coordB[1] = (this->manager_->height() - ballSize) * 10;
            vectorB[1] = -vectorB[1];
            if (this->random_color_) {
                ballColor = light::ESPHSVColor(random(0, 9) * 28, 255, 255);
            }
        }

        it.all() = Color::BLACK;

        for (uint8_t i = 0; i < ballSize; i++) {
            for (uint8_t j = 0; j < ballSize; j++) {
                it[getPixelNumber(coordB[0] / 10 + i, coordB[1] / 10 + j)] = ballColor;
            }
        }

        it.schedule_show();
    }

    void set_random_color(bool random_color) { this->random_color_ = random_color; }

protected:
    bool first_run_{true};
    bool random_color_{true};

    std::vector<int16_t> coordB;
    std::vector<int8_t> vectorB;

    light::ESPHSVColor ballColor;
    int8_t ballSize{0};
};

}  // namespace effects
}  // namespace esphome