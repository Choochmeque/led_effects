#pragma once

#include "AddressableAbstractEffect.h"


namespace esphome {
namespace effects {

class AddressableRainNeoEffect : public AddressableAbstractEffect 
{
public:
    AddressableRainNeoEffect(const std::string &name) : AddressableAbstractEffect(name) {}

    void start() override
    {
        this->rainClouds_p = CRGBPalette16(Color::BLACK, Color(15, 24, 24), Color(9, 15, 15), Color::BLACK);

        this->temp_matrix_.resize(this->manager_->width());
        for (uint8_t i = 0; i < this->manager_->width(); ++i) {
            this->temp_matrix_[i].resize(this->manager_->height());
        }
        this->splash_array_.resize(this->manager_->width());
        this->cloud_height_ = this->manager_->height() * 0.4 + 1;
    }

    void apply(light::AddressableLight &it, const Color &current_color) override 
    {
        const uint32_t now = millis();
        if (now - this->last_run_ < this->update_interval_) {
            return;
        }

        this->last_run_ = now;

        rain(it);

        it.schedule_show();
    }

    void rain(light::AddressableLight &it)
    {
        CRGBPalette16 rain_p(Color::BLACK, Color(rainColor));

        fadeToBlackBy(it, 255 - tailLength);

        if (!lightning && this->storm_) {
            lightning = new uint8_t[this->manager_->num_leds()];
        } else if (lightning && !this->storm_) {
            delete[] lightning;
            lightning = nullptr;
        }

        if (!noise && this->clouds_) {
            noise = new uint8_t[this->manager_->width() * this->cloud_height_];
        } else if (noise && !this->clouds_) {
            delete[] noise;
            noise = nullptr;
        }

        // Loop for each column individually
        for (int x = 0; x < this->manager_->width(); x++) {
            // Step 1.  Move each dot down one cell
            for (int i = 0; i < this->manager_->height(); i++) {
                if (this->temp_matrix_[x][i] >= backgroundDepth) {  // Don't move empty cells
                    if (i > 0) {
                        this->temp_matrix_[x][wrapY(i - 1)] = this->temp_matrix_[x][i];
                    }
                    this->temp_matrix_[x][i] = 0;
                }
            }

            // Step 2.  Randomly spawn new dots at top
            if (random8() < spawnFreq) {
                this->temp_matrix_[x][this->manager_->height() - 1] = random(backgroundDepth, maxBrightness);
            }

            // Step 3. Map from tempMatrix cells to LED colors
            for (int y = 0; y < this->manager_->height(); y++) {
                if (this->temp_matrix_[x][y] >= backgroundDepth) {  // Don't write out empty cells
                    it[getPixelNumber(x, y)] = ColorFromPalette(rain_p, this->temp_matrix_[x][y]);
                }
            }

            // Step 4. Add splash if called for
            if (this->splashes_) {
                // FIXME, this is broken
                uint8_t j = this->splash_array_[x];
                uint8_t v = this->temp_matrix_[x][0];

                if (j >= backgroundDepth) {
                    it[getPixelNumber(wrapX(x - 2), 0)] = ColorFromPalette(rain_p, j/3);
                    it[getPixelNumber(wrapX(x + 2), 0)] = ColorFromPalette(rain_p, j/3);
                    this->splash_array_[x] = 0;   // Reset splash
                }

                if (v >= backgroundDepth) {
                    it[getPixelNumber(wrapX(x - 1), 1)] = ColorFromPalette(rain_p, v/2);
                    it[getPixelNumber(wrapX(x + 1), 1)] = ColorFromPalette(rain_p, v/2);
                    this->splash_array_[x] = v; // Prep splash for next frame
                }
            }

            // Step 5. Add lightning if called for
            if (this->storm_) {
                if (!lightning) {
                    Serial.println("lightning malloc failed");
                    return;
                } else {
                    memset(lightning, 0, this->manager_->num_leds() * sizeof(*lightning));
                }

                if (random16() < 72) {    // Odds of a lightning bolt
                    lightning[scale8(random8(), this->manager_->width() - 1) + (this->manager_->height() - 1) * this->manager_->width()] = 255;  // Random starting location
                    for(int ly = this->manager_->height() - 1; ly > 1; ly--) {
                        for (int lx = 1; lx < this->manager_->width() - 1; lx++) {
                            if (lightning[lx + ly * this->manager_->width()] == 255) {
                                lightning[lx + ly * this->manager_->width()] = 0;
                                uint8_t dir = random8(4);
                                switch (dir) {
                                case 0:
                                    it[getPixelNumber(lx + 1, ly - 1)] = Color(lightningColor);
                                    lightning[wrapX(lx + 1) + (ly - 1) * this->manager_->width()] = 255; // move down and right
                                    break;
                                case 1:
                                    it[getPixelNumber(lx, ly - 1)] = Color(128, 128, 128);
                                    lightning[lx + (ly - 1) * this->manager_->width()] = 255;    // move down
                                    break;
                                case 2:
                                    it[getPixelNumber(lx - 1, ly - 1)] = Color(128, 128, 128);
                                    lightning[wrapX(lx - 1) + (ly - 1) * this->manager_->width()] = 255; // move down and left
                                    break;
                                case 3:
                                    it[getPixelNumber(lx - 1, ly - 1)] = Color(128, 128, 128);
                                    lightning[wrapX(lx - 1) + (ly - 1) * this->manager_->width()] = 255; // fork down and left
                                    it[getPixelNumber(lx - 1, ly - 1)] = Color(128, 128, 128);
                                    lightning[wrapX(lx + 1) + (ly - 1) * this->manager_->width()] = 255; // fork down and right
                                    break;
                                }
                            }
                        }
                    }
                }
            }

            // Step 6. Add clouds if called for
            if (clouds) {
                if (!noise) {
                    Serial.println("noise malloc failed");
                    return;
                } else {
                    memset(noise, 0, this->manager_->width() * this->cloud_height_ * sizeof(*noise));
                }
                int xoffset = noiseScale * x + this->hue_;

                for(uint8_t z = 0; z < this->cloud_height_; z++) {
                    int yoffset = noiseScale * z - this->hue_;
                    uint8_t dataSmoothing = 192;
                    uint8_t noiseData = qsub8(inoise8(noiseX + xoffset, noiseY + yoffset, noiseZ), 16);
                    noiseData = qadd8(noiseData, scale8(noiseData,39));
                    noise[x * this->cloud_height_ + z] = scale8(noise[x * this->cloud_height_ + z], dataSmoothing) + scale8(noiseData, 256 - dataSmoothing);
                    blendPixelXY(it, x, this->manager_->height() - z - 1, ColorFromPalette(rainClouds_p, noise[x * this->cloud_height_ + z]), (this->cloud_height_ - z) * (250 / this->cloud_height_));
                }
                noiseZ ++;
            }
        }
    }

    void set_splashes(bool splashes) { this->splashes_ = splashes; }

    void set_clouds(bool clouds) { this->clouds_ = clouds; }

    void set_storm(bool storm) { this->storm_ = storm; }

protected:
    std::vector<std::vector<uint8_t> > temp_matrix_;
    std::vector<uint8_t> splash_array_;

    uint16_t noiseX = random16();
    uint16_t noiseY = random16();
    uint16_t noiseZ = random16();
    CRGBPalette16 rainClouds_p;

    uint8_t hue_{0};

    uint8_t* lightning = nullptr;
    uint8_t* noise = nullptr;

    uint16_t noiseScale = 250;  // A value of 1 will be so zoomed in, you'll mostly see solid colors. A value of 4011 will be very zoomed out and shimmery
    uint8_t cloud_height_{2};

    // settigns
    uint32_t rainColor = 0x3c505a;
    uint32_t lightningColor = 0x484850;

    uint8_t backgroundDepth = 60;
    uint8_t maxBrightness = 200;
    uint8_t spawnFreq = 50;
    uint8_t tailLength = 30;
    bool splashes_{false};
    bool clouds_{false};
    bool storm_{false};
};

}  // namespace effects
}  // namespace esphome