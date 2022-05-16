#pragma once

#include "AddressableAbstractEffect.h"


namespace esphome {
namespace effects {

class AddressableFire12Effect : public AddressableAbstractEffect 
{
public:
    AddressableFire12Effect(const std::string &name) : AddressableAbstractEffect(name) {}

    void start() override
    {
        random16_add_entropy(random(256));
        this->fire_base_ = this->manager_->height() / 6 + 1;

        this->noise3d_.resize(this->manager_->width());
        for (uint8_t i = 0; i < this->manager_->width(); ++i) {
            noise3d[i].resize(this->manager_->height());
        }
    }

    void apply(light::AddressableLight &it, const Color &current_color) override 
    {
        const uint32_t now = millis();
        if (now - this->last_run_ < this->update_interval_) {
            return;
        }

        this->last_run_ = now;

        // Loop for each column individually
        for (int x = 0; x < this->manager_->width(); x++) {
            // Step 1.  Cool down every cell a little
            for (int i = 0; i < this->manager_->height(); i++) {
                this->noise3d_[x][i] = qsub8(this->noise3d_[x][i],
                                    random(0, ((cooling * 10) / this->manager_->height()) + 2));
            }
            // Step 2.  Heat from each cell drifts 'up' and diffuses a little
            for (int k = this->manager_->height(); k > 1; k--) {
                this->noise3d_[x][myMatrix->wrapY(k)] = (this->noise3d_[x][k - 1] + this->noise3d_[x][wrapY(k - 2)] + this->noise3d_[x][wrapY(k - 2)]) / 3;
            }
            // Step 3.  Randomly ignite new 'sparks' of heat near the bottom
            if (random8() < this->sparking_) {
                int j = random(this->fire_base_);
                this->noise3d_[x][j] = qadd8(this->noise3d_[x][j], random(160, 255));
            }
            // Step 4.  Map from heat cells to LED colors
            if (this->scale_ > 50) {
                for (int y = 0; y < this->manager_->height(); y++) {
                    // Blend new data with previous frame. Average data between neighbouring pixels
                    blendPixelXY(it, x, y, ColorFromPalette(*GetFirePalette((this->scale_ - 50) * 2), ((this->noise3d_[x][y] * 0.7f) + (this->noise3d_[wrapX(x + 1)][y] * 0.3f))), this->fire_smoothing_);
                }
            } else {
                for (int y = 0; y < this->manager_->height(); y++) {
                    // Blend new data with previous frame. Average data between neighbouring pixels
                    blendPixelXY(it, x, y, ColorFromPalette(*GetColorPalette(this->scale_ * 2), ((this->noise3d_[x][y] * 0.7f) + (this->noise3d_[wrapX(x + 1)][y] * 0.3f))), this->fire_smoothing_);
                }
            }
        }

        it.schedule_show();
    }

protected:
    uint8_t cooling_{70};
    uint8_t sparking_{130};
    uint8_t fire_smoothing_{80};

    uint8_t fire_base_{3};
    std::vector<std::vector<uint8_t> > noise3d_;
};

}  // namespace effects
}  // namespace esphome