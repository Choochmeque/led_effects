#pragma once

#include "AddressableAbstractEffect.h"


namespace esphome {
namespace effects {

const TProgmemRGBPalette16 WaterfallColors_p PROGMEM = {
  0x000000, 0x060707, 0x101110, 0x151717,
  0x1C1D22, 0x242A28, 0x363B3A, 0x313634,
  0x505552, 0x6B6C70, 0x98A4A1, 0xC1C2C1,
  0xCACECF, 0xCDDEDD, 0xDEDFE0, 0xB2BAB9
};

class AddressableWaterfallEffect : public AddressableAbstractEffect 
{
public:
    AddressableWaterfallEffect(const std::string &name) : AddressableAbstractEffect(name) {}

    void start() override
    {
        this->noise3d_.resize(this->manager_->width());
        for (uint8_t i = 0; i < this->manager_->width(); ++i) {
            this->noise3d_[i].resize(this->manager_->height());
        }
    }

    void apply(light::AddressableLight &it, const Color &current_color) override 
    {
        const uint32_t now = millis();
        if (now - this->last_run_ < this->update_interval_) {
            return;
        }

        this->last_run_ = now;

        for (uint8_t x = 0; x < this->manager_->width(); x++) {
            // Step 1.  Cool down every cell a little
            for (uint8_t i = 0; i < this->manager_->height(); i++) {
                this->noise3d_[x][i] = qsub8(this->noise3d_[x][i],
                                    random8(0, ((this->cooling_ * 10) / this->manager_->height()) + 2));
            }

            // Step 2.  Heat from each cell drifts 'up' and diffuses a little
            for (uint8_t k = this->manager_->height() - 1; k >= 2; k--) {
                this->noise3d_[x][k] = (this->noise3d_[x][k - 1] + this->noise3d_[x][k - 2] + this->noise3d_[x][k - 2]) / 3;
            }

            // Step 3.  Randomly ignite new 'sparks' of heat near the bottom
            if (random8() < this->sparkling_) {
                uint8_t y = random8(2);
                this->noise3d_[x][y] = qadd8(this->noise3d_[x][y], random8(160, 255));
            }

            // Step 4.  Map from heat cells to LED colors
            for (uint8_t j = 0; j < this->manager_->height(); j++) {
                // Scale the heat value from 0-255 down to 0-240
                // for best results with color palettes.
                uint8_t colorindex = scale8(this->noise3d_[x][j], 240);
                if (this->scale_ == 100)
                    it[getPixelNumber(x, this->manager_->height() - 1 - j)] = ColorFromPalette(WaterfallColors_p, colorindex);
                else
                    it[getPixelNumber(x, this->manager_->height() - 1 - j)] = 
                                        ColorFromPalette(CRGBPalette16(Color::BLACK,
                                                                        light::ESPHSVColor(this->scale_ * 2.57, 255, 255),
                                                                        light::ESPHSVColor(this->scale_ * 2.57, 128, 255),
                                                                        Color::WHITE),
                                                        colorindex);// 2.57 вместо 2.55, потому что 100 для белого цвета
            }
        }

        it.schedule_show();
    }

protected:
    int8_t cooling_{32};
    int8_t sparkling_{80};

    std::vector<std::vector<uint8_t> > noise3d_;
};

}  // namespace effects
}  // namespace esphome