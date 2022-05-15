#pragma once

#include "AddressableAbstractEffect.h"


namespace esphome {
namespace effects {

class AddressableWaveEffect : public AddressableAbstractEffect 
{
public:
    AddressableWaveEffect(const std::string &name) : AddressableAbstractEffect(name) {}

    void start() override
    {
        this->wave_scale_ = 256 / this->manager_->width();

        this->wave_rotation_ = (this->scale_ - 1) / 25;
        this->wave_count_ = this->update_interval_ % 2;
    }

    void apply(light::AddressableLight &it, const Color &current_color) override 
    {
        const uint32_t now = millis();
        if (now - this->last_run_ < this->update_interval_) {
            return;
        }

        this->last_run_ = now;

        this->dimAll(it, 254);

        int n = 0;

        switch (this->wave_rotation_) {
        case 0:
            for (int x = 0; x < this->manager_->width(); x++) {
                n = quadwave8(x * 2 + waveTheta) / this->wave_scale_;
                it[getPixelNumber(x, n)] = ColorFromPalette(*GetColorPalette(this->scale_), this->hue_ + x);
                if (this->wave_count_ != 1) {
                    it[getPixelNumber(x, this->manager_->height() - 1 - n)] = ColorFromPalette(*GetColorPalette(this->scale_), this->hue_ + x);
                }
            }
            break;

        case 1:
            for (int y = 0; y < this->manager_->height(); y++) {
                n = quadwave8(y * 2 + waveTheta) / this->wave_scale_;
                it[getPixelNumber(n, y)] = ColorFromPalette(*GetColorPalette(this->scale_), this->hue_ + y);
                if (this->wave_count_ != 1) {
                    it[getPixelNumber(this->manager_->width() - 1 - n, y)] = ColorFromPalette(*GetColorPalette(this->scale_), this->hue_ + y);
                }
            }
            break;

        case 2:
            for (int x = 0; x < this->manager_->width(); x++) {
                n = quadwave8(x * 2 - waveTheta) / this->wave_scale_;
                it[getPixelNumber(x, n)] = ColorFromPalette(*GetColorPalette(this->scale_), this->hue_ + x);
                if (this->wave_count_ != 1) {
                    it[getPixelNumber(x, this->manager_->height() - 1 - n)] = ColorFromPalette(*GetColorPalette(this->scale_), this->hue_ + x);
                }
            }
            break;

        case 3:
            for (int y = 0; y < this->manager_->height(); y++) {
                n = quadwave8(y * 2 - waveTheta) / this->wave_scale_;
                it[getPixelNumber(n, y)] = ColorFromPalette(*GetColorPalette(this->scale_), this->hue_ + y);
                if (this->wave_count_ != 1) {
                    it[getPixelNumber(this->manager_->width() - 1 - n, y)] = ColorFromPalette(*GetColorPalette(this->scale_), this->hue_ + y);
                }
            }
            break;
        }

        if (waveThetaUpdate >= waveThetaUpdateFrequency) {
            waveThetaUpdate = 0;
            waveTheta++;
        }
        else {
            waveThetaUpdate++;
        }

        if (hueUpdate >= hueUpdateFrequency) {
            hueUpdate = 0;
            this->hue_++;
        }
        else {
            hueUpdate++;
        }

        this->applyBlur2d(it, 20);

        it.schedule_show();
    }

protected:
    uint8_t waveThetaUpdate{0};
    uint8_t waveThetaUpdateFrequency{0};
    uint8_t waveTheta{0};

    uint8_t hueUpdate{0};
    uint8_t hueUpdateFrequency{0};
    uint8_t hue_{0};

    uint8_t wave_rotation_{0};
    uint8_t wave_scale_{16};
    uint8_t wave_count_{1};
};

}  // namespace effects
}  // namespace esphome