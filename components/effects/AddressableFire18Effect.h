#pragma once

#include "AddressableAbstractEffect.h"


namespace esphome {
namespace effects {

class AddressableFire18Effect : public AddressableAbstractEffect 
{
public:
    AddressableFire18Effect(const std::string &name) : AddressableAbstractEffect(name) {}

    void start() override
    {
        this->effect_x_.resize(this->num_layers_);
        this->effect_y_.resize(this->num_layers_);
        this->effect_z_.resize(this->num_layers_);
        this->effect_scale_x_.resize(this->num_layers_);
        this->effect_scale_y_.resize(this->num_layers_);

        this->noise3d.resize(this->num_layers_);
        for (uint8_t i = 0; i < this->num_layers_; ++i) {
            this->noise3d[i].resize(this->manager_->width());
            for (uint8_t j = 0; j < this->manager_->width(); ++j) {
                this->noise3d[i][j].resize(this->manager_->height());
            }
        }

        this->fire18heat.resize(this->manager_->height());
        for (uint8_t j = 0; j < this->manager_->height(); ++j) {
            this->fire18heat[j].resize(this->manager_->width());
        }
    }

    void apply(light::AddressableLight &it, const Color &current_color) override 
    {
        const uint32_t now = millis();
        if (now - this->last_run_ < this->update_interval_) {
            return;
        }

        this->last_run_ = now;

        uint16_t ctrl1 = inoise16(11 * millis(), 0, 0);
        uint16_t ctrl2 = inoise16(13 * millis(), 100000, 100000);
        uint16_t  ctrl = ((ctrl1 + ctrl2) / 2);

        for (int z = 0; z < this->num_layers_; z++) {
            const uint16_t speed = this->speed_array_[z];
            this->effect_x_[z] = 3 * ctrl * speed;
            this->effect_y_[z] = 20 * millis() * speed;
            this->effect_z_[z] = 5 * millis() * speed ;
            this->effect_scale_x_[z] = ctrl1 / 2;
            this->effect_scale_y_[z] = ctrl2 / 2;

            for (uint8_t i = 0; i < this->manager_->width(); i++) {
                uint32_t ioffset = this->effect_scale_x_[z] * (i - getCenterX());
                for (uint8_t j = 0; j < this->manager_->height(); j++) {
                    uint32_t joffset = this->effect_scale_y_[z] * (j - getCenterY());
                    uint16_t data = ((inoise16(this->effect_x_[z] + ioffset, this->effect_y_[z] + joffset, this->effect_z_[z])) + 1);
                    this->noise3d[z][i][j] = data >> 8;
                }
            }
        }

        // draw lowest line - seed the fire
        for (uint8_t x = 0; x < this->manager_->width(); x++) {
            fire18heat[this->manager_->height() - 1][x] =
                    this->noise3d[0][this->manager_->width() - 1 - x][getCenterY() - 1];
        }


        //copy everything one line up
        for (uint8_t y = 0; y < this->manager_->height() - 1; y++) {
            memcpy(this->fire18heat[y], this->fire18heat[y + 1], sizeof(uint8_t) * this->manager_->width());
        }

        //dim
        for (uint8_t y = 0; y < this->manager_->height() - 1; y++) {
            for (uint8_t x = 0; x < this->manager_->width(); x++) {
                uint8_t dim = this->noise3d[0][x][y];
                // high value = high flames
                dim = dim / 1.7;
                dim = 255 - dim;
                this->fire18heat[y][x] = scale8(this->fire18heat[y][x], dim);
            }
        }

        for (uint8_t y = 0; y < this->manager_->height(); y++) {
            for (uint8_t x = 0; x < this->manager_->width(); x++) {
                // map the colors based on heatmap
                it[getPixelNumber(x, this->manager_->height() - 1 - y)] =
                                    Color(this->fire18heat[y][x],
                                        (float)this->fire18heat[y][x] * this->scale_ * 0.01f,
                                        0));

                // dim the result based on 2nd noise layer
                dimPixelXY(it, x,
                                    this->manager_->height() - 1 - y,
                                    this->noise3d[1][x][y]);
            }
        }

        it.schedule_show();
    }

protected:
    std::vector<uint32_t> effect_x_;
    std::vector<uint32_t> effect_y_;
    std::vector<uint32_t> effect_z_;
    std::vector<uint32_t> effect_scale_x_;
    std::vector<uint32_t> effect_scale_y_;
    std::vector<std::vector<std::vector<uint8_t> > > noise3d;

    std::vector<std::vector<uint8_t> > fire18heat;

    const uint8_t num_layers_{2};
    const uint16_t speed_array_[2] = {25, 20};
};

}  // namespace effects
}  // namespace esphome