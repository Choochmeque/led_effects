#pragma once

#include "AddressableAbstractEffect.h"


namespace esphome {
namespace effects {

class AddressableBouncingBallsEffect : public AddressableAbstractEffect 
{
public:
    AddressableBouncingBallsEffect(const std::string &name) : AddressableAbstractEffect(name) {}

    void start() override
    {
        bballsMaxNUM = this->manager_->width() * 2;
        bballsVImpact0 = sqrt(2 * bballsGRAVITY * bballsH0);

        bballsCOLOR.resize(bballsMaxNUM);
        bballsX.resize(bballsMaxNUM);
        bballsShift.resize(bballsMaxNUM);

        bballsVImpact.resize(bballsMaxNUM);
        bballsPos.resize(bballsMaxNUM);
        bballsTLast.resize(bballsMaxNUM);
        bballsCOR.resize(bballsMaxNUM);

        bballsNUM = (this->scale_ - 1) / 99.0f * (bballsMaxNUM - 1) + 1;
        if (bballsNUM > bballsMaxNUM) {
            bballsNUM = bballsMaxNUM;
        }
        for (int i = 0 ; i < bballsNUM ; i++) {
            bballsCOLOR[i] = random(0, 255);
            bballsX[i] = random(0, this->manager_->width());
            bballsTLast[i] = millis();
            bballsPos[i] = 0;
            bballsVImpact[i] = bballsVImpact0;
            bballsCOR[i] = 0.90f - float(i) / pow(bballsNUM, 2);
            bballsShift[i] = false;
        }
    }

    void apply(light::AddressableLight &it, const Color &current_color) override 
    {
        const uint32_t now = millis();
        if (now - this->last_run_ < this->update_interval_) {
            return;
        }

        this->last_run_ = now;

        float bballsHi = 0;
        float bballsTCycle = 0;

        this->dimAll(it, 255 - this->update_interval_);

        for (int i = 0 ; i < bballsNUM ; i++) {
            bballsTCycle =  millis() - bballsTLast[i];

            bballsHi = -0.5f * bballsGRAVITY * pow(bballsTCycle / 1000.0f , 2.0f) + bballsVImpact[i] * bballsTCycle / 1000.0f;

            if ( bballsHi < 0 ) {
                bballsTLast[i] = millis();
                bballsHi = 0;
                bballsVImpact[i] = bballsCOR[i] * bballsVImpact[i];

                if (bballsVImpact[i] < 0.01f) {
                    bballsCOR[i] = 0.90f - float(random(0, 9)) / pow(random(4, 9), 2);
                    bballsShift[i] = bballsCOR[i] >= 0.89f;
                    bballsVImpact[i] = bballsVImpact0;
                }
            }
            bballsPos[i] = round(bballsHi * (this->manager_->height() - 1) / bballsH0);
            if (bballsShift[i] && (bballsPos[i] == this->manager_->height() - 1)) {
                bballsShift[i] = false;
                if (bballsCOLOR[i] % 2 == 0) {
                    if (bballsX[i] == 0) bballsX[i] = this->manager_->width() - 1;
                    else --bballsX[i];
                } 
                else {
                    if (bballsX[i] == this->manager_->width() - 1) {
                        bballsX[i] = 0;
                    } 
                    else {
                        ++bballsX[i];
                    }
                }
            }
            it[getPixelNumber(bballsX[i], bballsPos[i])] = light::ESPHSVColor(bballsCOLOR[i], (this->colored_) ? 255 : 0, 255);
        }

        it.schedule_show();
    }

    void set_colored(bool colored) { this->colored_ = colored; }

protected:
    bool colored_{false};

    const float bballsGRAVITY{9.81f};
    const uint8_t bballsH0{1};
    uint8_t bballsMaxNUM{0};
    uint8_t bballsNUM{0};

    float bballsVImpact0{0.0f};

    std::vector<uint8_t> bballsCOLOR;
    std::vector<uint8_t> bballsX;
    std::vector<bool> bballsShift;

    std::vector<float> bballsVImpact;
    std::vector<int> bballsPos;
    std::vector<long> bballsTLast;
    std::vector<float> bballsCOR;
};

}  // namespace effects
}  // namespace esphome