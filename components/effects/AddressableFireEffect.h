#pragma once

#include "AddressableAbstractEffect.h"

namespace esphome {
namespace effects {

//these values are substracetd from the generated values to give a shape to the animation
const unsigned char valueMask[8][16] PROGMEM = {
    {32 , 0  , 0  , 0  , 0  , 0  , 0  , 32 , 32 , 0  , 0  , 0  , 0  , 0  , 0  , 32 },
    {64 , 0  , 0  , 0  , 0  , 0  , 0  , 64 , 64 , 0  , 0  , 0  , 0  , 0  , 0  , 64 },
    {96 , 32 , 0  , 0  , 0  , 0  , 32 , 96 , 96 , 32 , 0  , 0  , 0  , 0  , 32 , 96 },
    {128, 64 , 32 , 0  , 0  , 32 , 64 , 128, 128, 64 , 32 , 0  , 0  , 32 , 64 , 128},
    {160, 96 , 64 , 32 , 32 , 64 , 96 , 160, 160, 96 , 64 , 32 , 32 , 64 , 96 , 160},
    {192, 128, 96 , 64 , 64 , 96 , 128, 192, 192, 128, 96 , 64 , 64 , 96 , 128, 192},
    {255, 160, 128, 96 , 96 , 128, 160, 255, 255, 160, 128, 96 , 96 , 128, 160, 255},
    {255, 192, 160, 128, 128, 160, 192, 255, 255, 192, 160, 128, 128, 160, 192, 255}
};

//these are the hues for the fire,
//should be between 0 (red) to about 25 (yellow)
const unsigned char hueMask[8][16] PROGMEM = {
    {1 , 11, 19, 25, 25, 22, 11, 1 , 1 , 11, 19, 25, 25, 22, 11, 1 },
    {1 , 8 , 13, 19, 25, 19, 8 , 1 , 1 , 8 , 13, 19, 25, 19, 8 , 1 },
    {1 , 8 , 13, 16, 19, 16, 8 , 1 , 1 , 8 , 13, 16, 19, 16, 8 , 1 },
    {1 , 5 , 11, 13, 13, 13, 5 , 1 , 1 , 5 , 11, 13, 13, 13, 5 , 1 },
    {1 , 5 , 11, 11, 11, 11, 5 , 1 , 1 , 5 , 11, 11, 11, 11, 5 , 1 },
    {0 , 1 , 5 , 8 , 8 , 5 , 1 , 0 , 0 , 1 , 5 , 8 , 8 , 5 , 1 , 0 },
    {0 , 0 , 1 , 5 , 5 , 1 , 0 , 0 , 0 , 0 , 1 , 5 , 5 , 1 , 0 , 0 },
    {0 , 0 , 0 , 1 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 1 , 0 , 0 , 0 }
};

class AddressableFireEffect : public AddressableAbstractEffect 
{
public:
    AddressableFireEffect(const std::string &name) : AddressableAbstractEffect(name) {}

    void start() override
    {
        this->line_.resize(this->manager_->width());
        generateLine();
    }

    void apply(light::AddressableLight &it, const Color &current_color) override 
    {
        const uint32_t now = millis();
        if (now - this->last_run_ < this->update_interval_) {
            return;
        }

        this->last_run_ = now;

        if (this->pcnt_ >= 100) {
            shiftUp();
            generateLine();
            this->pcnt_ = 0;
        }

        drawFrame(it);
        this->pcnt_ += 30;

        it.schedule_show();
    }

    void generateLine()
    {
        for (uint8_t x = 0; x < this->manager_->width(); x++) {
            this->line_[x] = static_cast<uint8_t>(random(64, 255));
        }
    }

    void shiftUp()
    {
        for (uint8_t y = this->manager_->height() - 1; y > 0; y--) {
            for (uint8_t x = 0; x < this->manager_->width(); x++) {
                if (y > 7) {
                    continue;
                }
                matrixValue[y][x] = matrixValue[y - 1][x];
            }
        }

        for (uint8_t x = 0; x < this->manager_->width(); x++) {
            matrixValue[0][x] = this->line_[x];
        }
    }

    void drawFrame(light::AddressableLight &it)
    {
        int nextv{0};

        //each row interpolates with the one before it
        for (uint8_t y = this->manager_->height() - 1; y > 0; y--) {
            for (uint8_t x = 0; x < this->manager_->width(); x++) {
                if (y < 8) {
                    nextv =
                            (((100.0 - this->pcnt_) * matrixValue[y][x]
                            + this->pcnt_ * matrixValue[y - 1][x]) / 100.0)
                            - pgm_read_byte(&(valueMask[y][x]));

                    const uint8_t hue = this->scale_ * 2.55;

                    const light::ESPHSVColor color = light::ESPHSVColor(
                            hue + pgm_read_byte(&(hueMask[y][x])), // H
                            255, // S
                            (uint8_t)max(0, nextv) // V
                            );
                    it[getPixelNumber(x, y)] = color;
                } 
                else if (y == 8 && this->sparkles_) {
                    const Color c = it[getPixelNumber(x, y - 1)].get();
                    if (random(0, 20) == 0 && compareColors(c, Color::BLACK) > 0) {
                        it[getPixelNumber(x, y)] = c;
                    } 
                    else {
                        it[getPixelNumber(x, y)] = Color::BLACK;
                    }
                } 
                else if (random(0, 2) == 0 && this->sparkles_) {
                    // старая версия для яркости
                    const Color c = it[getPixelNumber(x, y - 1)].get();
                    if (compareColors(c, Color::BLACK) > 0) {
                        it[getPixelNumber(x, y)] = c;
                    } 
                    else {
                        it[getPixelNumber(x, y)] = Color::BLACK;
                    }
                }
            }
        }

        //first row interpolates with the "next" line
        for (uint8_t x = 0; x < this->manager_->width(); x++) {
            const uint8_t hue = this->scale_ * 2.55;

            const light::ESPHSVColor color = light::ESPHSVColor(
                    hue + pgm_read_byte(&(hueMask[0][x])), // H
                    255,           // S
                    (uint8_t)(((100.0 - this->pcnt_) * matrixValue[0][x] + this->pcnt_ * this->line_[x]) / 100.0) // V
                    );
            it[getPixelNumber(x, 0)] = color;
        }
    }

    void set_sparkles(bool sparkles) { this->sparkles_ = sparkles; }

protected:
    bool sparkles_{true};

    uint8_t matrixValue[8][16] = {};
    std::vector<uint8_t> line_;
    uint8_t pcnt_{0};
};

}  // namespace effects
}  // namespace esphome