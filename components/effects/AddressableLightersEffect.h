#pragma once

#include "AddressableAbstractEffect.h"


namespace esphome {
namespace effects {

class AddressableLightersEffect : public AddressableAbstractEffect 
{
public:
    AddressableLightersEffect(const std::string &name) : AddressableAbstractEffect(name) {}

    void apply(light::AddressableLight &it, const Color &current_color) override 
    {
        const uint32_t now = millis();
        if (now - this->last_run_ < this->update_interval_) {
            return;
        }

        this->last_run_ = now;

        if (this->first_run_) {
            this->lightersPos_.resize(2);
            this->lightersPos_[0].resize(this->lighters_am_);
            this->lightersPos_[1].resize(this->lighters_am_);

            this->lightersSpeed_.resize(2);
            this->lightersSpeed_[0].resize(this->lighters_am_);
            this->lightersSpeed_[1].resize(this->lighters_am_);

            this->lightersColor_.resize(this->lighters_am_);

            for (uint8_t i = 0; i < this->lighters_am_; i++) {
                this->lightersPos_[0][i] = random(0, this->manager_->width() * 10);
                this->lightersPos_[1][i] = random(0, this->manager_->height() * 10);
                this->lightersSpeed_[0][i] = random(-10, 10);
                this->lightersSpeed_[1][i] = random(-10, 10);
                this->lightersColor_[i] = light::ESPHSVColor(random(0, 255), 255, 255);
            }
        }

        it.all() = Color::BLACK;
        if (++this->loopCounter_ > 20) {
            this->loopCounter_ = 0;
        }

        for (uint8_t i = 0; i < this->scale_; i++) {
            if (this->loopCounter_ == 0) {     // меняем скорость каждые 255 отрисовок
                this->lightersSpeed_[0][i] += random(-3, 4);
                this->lightersSpeed_[1][i] += random(-3, 4);
                this->lightersSpeed_[0][i] = constrain(this->lightersSpeed_[0][i], -20, 20);
                this->lightersSpeed_[1][i] = constrain(this->lightersSpeed_[1][i], -20, 20);
            }

            this->lightersPos_[0][i] += this->lightersSpeed_[0][i];
            this->lightersPos_[1][i] += this->lightersSpeed_[1][i];

            if (this->lightersPos_[0][i] < 0) {
                this->lightersPos_[0][i] = (this->manager_->width() - 1) * 10;
            }
            if (this->lightersPos_[0][i] >= this->manager_->width() * 10) {
                this->lightersPos_[0][i] = 0;
            }

            if (this->lightersPos_[1][i] < 0) {
                this->lightersPos_[1][i] = 0;
                this->lightersSpeed_[1][i] = -this->lightersSpeed_[1][i];
            }
            if (this->lightersPos_[1][i] >= (this->manager_->height() - 1) * 10) {
                this->lightersPos_[1][i] = (this->manager_->height() - 1) * 10;
                this->lightersSpeed_[1][i] = -this->lightersSpeed_[1][i];
            }
            myMatrix->drawPixelXY(this->lightersPos_[0][i] / 10, this->lightersPos_[1][i] / 10, this->lightersColor_[i]);
        }

        it.schedule_show();
    }

protected:
    std::vector<std::vector<int> > lightersPos_;
    std::vector<std::vector<int8_t> > lightersSpeed_;
    std::vector<light::ESPHSVColor> lightersColor_;

    uint8_t loopCounter_{0};

    uint8_t lighters_am_{100};
};

}  // namespace effects
}  // namespace esphome