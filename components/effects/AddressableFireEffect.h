#pragma once

#include "AddressableAbstractEffect.h"

namespace esphome {
namespace effects {

static byte MATRIX_TYPE = 0;
static byte WIDTH = 16;
static byte HEIGHT = 16;

light::ESPHSVColor RgbToHsv(byte r, byte g, byte b)
{
    light::ESPHSVColor hsv;

    const byte rgbMin = std::min(std::min(r, g), b);
    const byte rgbMax = std::max(std::max(r, g), b);

    hsv.value = rgbMax;
    if (hsv.value == 0) {
        hsv.hue = 0;
        hsv.saturation = 0;
        return hsv;
    }

    hsv.saturation = 255 * uint32(rgbMax - rgbMin) / hsv.value;
    if (hsv.saturation == 0) {
        hsv.hue = 0;
        return hsv;
    }

    if (rgbMax == r) {
        hsv.hue = 0 + 43 * (g - b) / (rgbMax - rgbMin);
    }
    else if (rgbMax == g) {
        hsv.hue = 85 + 43 * (b - r) / (rgbMax - rgbMin);
    }
    else {
        hsv.hue = 171 + 43 * (r - g) / (rgbMax - rgbMin);
    }

    return hsv;
}

light::ESPHSVColor RgbToHsv(const Color &color)
{
    return RgbToHsv(color.red, color.green, color.blue);
}

signed char compareColors(const Color &lh, const Color &rh)
{
    const uint32_t lhc = ((lh.red & 0xFF) << 16) + ((lh.green & 0xFF) << 8) + (lh.blue & 0xFF);
    const uint32_t rhc = ((rh.red & 0xFF) << 16) + ((rh.green & 0xFF) << 8) + (rh.blue & 0xFF);

    if (lhc == rhc) {
        return 0;
    }

    if (lhc < rhc) {
        return -1;
    }

    return 1;
}

bool isEqualColors(const Color &lh, const Color &rh)
{
    return lh.red == rh.red &&
            lh.green == rh.green &&
            lh.blue == rh.blue;
}

uint32 getPixelNumber(byte x, byte y)
{
    const byte THIS_X = x;
    const byte THIS_Y = y;
    const byte _WIDTH = WIDTH;
    
    if ((THIS_Y % 2 == 0) || MATRIX_TYPE) {               // если чётная строка
        return (THIS_Y * _WIDTH + THIS_X);
    } 
    else {                                                // если нечётная строка
        return (THIS_Y * _WIDTH + _WIDTH - THIS_X - 1);
    } 
};

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

uint8_t matrixValue[8][16] = {};
uint8_t line[WIDTH] = {};
uint8_t pcnt = 0;

class AddressableFireEffect : public AddressableAbstractEffect 
{
public:
    AddressableFireEffect(const std::string &name) : AddressableAbstractEffect(name) {}

    void apply(light::AddressableLight &it, const Color &current_color) override 
    {
        const uint32_t now = millis();
        if (now - this->last_run_ < this->update_interval_) {
            return;
        }

        this->last_run_ = now;

        if (this->first_run_) {
            this->first_run_ = false;
            generateLine();
        }

        if (pcnt >= 100) {
            shiftUp();
            generateLine();
            pcnt = 0;
        }

        drawFrame(pcnt, it);
        pcnt += 30;

        it.schedule_show();
    }

    void generateLine()
    {
        for (uint8_t x = 0; x < WIDTH; x++) {
            line[x] = static_cast<uint8_t>(random(64, 255));
        }
    }

    void shiftUp()
    {
        for (uint8_t y = HEIGHT - 1; y > 0; y--) {
            for (uint8_t x = 0; x < WIDTH; x++) {
                if (y > 7) {
                    continue;
                }
                matrixValue[y][x] = matrixValue[y - 1][x];
            }
        }

        for (uint8_t x = 0; x < WIDTH; x++) {
            matrixValue[0][x] = line[x];
        }
    }

    void drawFrame(uint8_t pcnt, light::AddressableLight &it)
    {
        int nextv;

        //each row interpolates with the one before it
        for (uint8_t y = HEIGHT - 1; y > 0; y--) {
            for (uint8_t x = 0; x < WIDTH; x++) {
                if (y < 8) {
                    nextv =
                            (((100.0 - pcnt) * matrixValue[y][x]
                            + pcnt * matrixValue[y - 1][x]) / 100.0)
                            - pgm_read_byte(&(valueMask[y][x]));

                    uint8_t hue = this->scale_ * 2.55;

                    light::ESPHSVColor color = light::ESPHSVColor(
                            hue + pgm_read_byte(&(hueMask[y][x])), // H
                            255, // S
                            (uint8_t)max(0, nextv) // V
                            );
                    it[getPixelNumber(x, y)] = color;
                } 
                else if (y == 8 && this->sparkles_) {
                    const Color c = it[getPixelNumber(x, y - 1)].get();
                    if (random(0, 20) == 0 && compareColors(c, Color::BLACK) > 0)) {
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
        for (uint8_t x = 0; x < WIDTH; x++) {
            uint8_t hue = this->scale_ * 2.55;

            light::ESPHSVColor color = light::ESPHSVColor(
                    hue + pgm_read_byte(&(hueMask[0][x])), // H
                    255,           // S
                    (uint8_t)(((100.0 - pcnt) * matrixValue[0][x] + pcnt * line[x]) / 100.0) // V
                    );
            it[getPixelNumber(x, y)] = color;
        }
    }

protected:
    bool first_run_{true};
    bool sparkles_{true};
};

}  // namespace effects
}  // namespace esphome