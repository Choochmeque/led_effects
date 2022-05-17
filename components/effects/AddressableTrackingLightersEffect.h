#pragma once

#include "AddressableAbstractEffect.h"


namespace esphome {
namespace effects {

class AddressableTrackingLightersEffect : public AddressableAbstractEffect 
{
public:
    AddressableTrackingLightersEffect(const std::string &name) : AddressableAbstractEffect(name) {}

    void start() override
    {
        this->lighters_pos_.resize(2);
        this->lighters_pos_[0].resize(this->amount_);
        this->lighters_pos_[1].resize(this->amount_);

        this->lighters_speed_.resize(2);
        this->lighters_speed_[0].resize(this->amount_);
        this->lighters_speed_[1].resize(this->amount_);

        this->lighters_color_.resize(this->amount_);

        for (uint8_t j = 0; j < this->amount_; j++) {
            int8_t sign = 0;
            this->lighters_pos_[0][j] = this->manager_->width() / 2 * 10;
            random(0, 2) ? sign = 1 : sign = -1;
            this->lighters_speed_[0][j] = random(4, 15) * sign;
            this->lighters_pos_[1][j] = this->manager_->height() / 2 * 10;
            random(0, 2) ? sign = 1 : sign = -1;
            this->lighters_speed_[1][j] = random(4, 15) * sign;
            this->lighters_color_[j] = light::ESPHSVColor((this->scale_ * (j + 1)) % 256, 255, 255);
        }
    }

    void apply(light::AddressableLight &it, const Color &current_color) override 
    {
        const uint32_t now = millis();
        if (now - this->last_run_ < this->update_interval_) {
            return;
        }

        this->last_run_ = now;

        if (this->tails_) {
            fader(it, this->tail_step_);
        } 
        else {
            clear(it);
        }

        for (uint8_t j = 0; j < this->amount_; j++) {
            for (uint8_t i = 0; i < 2; i++) {
                this->lighters_pos_[i][j] += this->lighters_speed_[i][j];
                if (this->lighters_pos_[i][j] < 0) {
                    this->lighters_pos_[i][j] = 0;
                    this->lighters_speed_[i][j] = -this->lighters_speed_[i][j];
                }
            }

            if (this->lighters_pos_[0][j] > (int16_t)((this->manager_->width() - 1) * 10)) {
                this->lighters_pos_[0][j] = (this->manager_->width() - 1) * 10;
                this->lighters_speed_[0][j] = -this->lighters_speed_[0][j];
            }
            if (this->lighters_pos_[1][j] > (int16_t)((this->manager_->height() - 1) * 10)) {
                this->lighters_pos_[1][j] = (this->manager_->height() - 1) * 10;
                this->lighters_speed_[1][j] = -this->lighters_speed_[1][j];
            }
            it[getPixelNumber(this->lighters_pos_[0][j] / 10, this->lighters_pos_[1][j] / 10)] = this->lighters_color_[j];
        }

        it.schedule_show();
    }

protected:
    uint8_t amount_{3};
    uint8_t tails_{true};
    uint8_t tail_step_{70};

    std::vector<std::vector<int16_t> > lighters_pos_;
    std::vector<std::vector<int8_t> > lighters_speed_;
    std::vector<light::ESPHSVColor> lighters_color_;
};

}  // namespace effects
}  // namespace esphome