#pragma once

#include "AddressableAbstractEffect.h"


namespace esphome {
namespace effects {

const TProgmemRGBPalette16 WaterfallColors4in1_p PROGMEM = 
{
  HTMLColorCode::Black,
  HTMLColorCode::DarkSlateGray,
  HTMLColorCode::DimGray,
  HTMLColorCode::LightSlateGray,

  HTMLColorCode::DimGray,
  HTMLColorCode::DarkSlateGray,
  HTMLColorCode::Silver,
  HTMLColorCode::DarkCyan,

  HTMLColorCode::Lavender,
  HTMLColorCode::Silver,
  HTMLColorCode::Azure,
  HTMLColorCode::LightGrey,

  HTMLColorCode::GhostWhite,
  HTMLColorCode::Silver,
  HTMLColorCode::White,
  HTMLColorCode::RoyalBlue
};

class AddressableWaterfallPaletteEffect : public AddressableAbstractEffect 
{
public:
    AddressableWaterfallPaletteEffect(const std::string &name) : AddressableAbstractEffect(name) {}

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

        uint8_t rCOOLINGNEW = constrain((uint16_t)(this->scale_ % 16) * 32 / this->manager_->height() + 16, 1, 255) ;

        for (uint8_t x = 0; x < this->manager_->width(); x++) {
            // Step 1.  Cool down every cell a little
            for (unsigned int i = 0; i < this->manager_->height(); i++) {
                this->noise3d_[x][i] = qsub8(this->noise3d_[x][i], random8(0, rCOOLINGNEW));
            }

            // Step 2.  Heat from each cell drifts 'up' and diffuses a little
            for (int k = this->manager_->height() - 1; k >= 2; k--) {
                this->noise3d_[x][k] = (this->noise3d_[x][k - 1] + this->noise3d_[x][k - 2] + this->noise3d_[x][k - 2]) / 3;
            }

            // Step 3.  Randomly ignite new 'sparks' of heat near the bottom
            if (random8() < this->sparkling_) {
                int y = random8(2);
                this->noise3d_[x][y] = qadd8(this->noise3d_[x][y], random8(160, 255));
            }

            // Step 4.  Map from heat cells to LED colors
            for (unsigned int j = 0; j < this->manager_->height(); j++) {
                // Scale the heat value from 0-255 down to 0-240
                // for best results with color palettes.
                uint8_t colorindex = scale8(this->noise3d_[x][j], 240);
                if  (this->scale_ < 16) {            // Lavafall
                    it[getPixelNumber(x, this->manager_->height() - 1 - j)] = ColorFromPalette(LavaColors_p, colorindex);
                } 
                else if (this->scale_ < 32) {      // Firefall
                    it[getPixelNumber(x, this->manager_->height() - 1 - j)] = ColorFromPalette(HeatColors_p, colorindex);
                } 
                else if (this->scale_ < 48) {      // Waterfall
                    it[getPixelNumber(x, this->manager_->height() - 1 - j)] = ColorFromPalette(WaterfallColors4in1_p, colorindex);
                } 
                else if (this->scale_ < 64) {      // Skyfall
                    it[getPixelNumber(x, this->manager_->height() - 1 - j)] = ColorFromPalette(CloudColors_p, colorindex);
                } 
                else if (this->scale_ < 80) {      // Forestfall
                    it[getPixelNumber(x, this->manager_->height() - 1 - j)] = ColorFromPalette(ForestColors_p, colorindex);
                } 
                else if (this->scale_ < 96) {      // Rainbowfall
                    it[getPixelNumber(x, this->manager_->height() - 1 - j)] = ColorFromPalette(RainbowColors_p, colorindex);
                } 
                else {                      // Aurora
                    it[getPixelNumber(x, this->manager_->height() - 1 - j)] = ColorFromPalette(RainbowStripeColors_p, colorindex);
                }
            }
        }

        it.schedule_show();
    }

    void set_sparkling(uint8_t sparkling) { this->sparkling_ = sparkling; }

protected:
    uint8_t sparkling_{80};
    std::vector<std::vector<uint8_t> > noise3d_;
};

}  // namespace effects
}  // namespace esphome