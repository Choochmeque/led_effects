#pragma once

#include "esphome/core/component.h"
#include "esphome/components/light/esp_hsv_color.h"
#include "esphome/components/light/addressable_light_effect.h"

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

class AddressableMatrixEffect : public light::AddressableLightEffect 
{
public:
    AddressableMatrixEffect(const std::string &name) : AddressableLightEffect(name) {}

    void apply(light::AddressableLight &it, const Color &current_color) override 
    {
        const uint32_t now = millis();
        if (now - this->last_run_ < this->update_interval_) {
            return;
        }

        this->last_run_ = now;

        for (byte x = 0; x < WIDTH; x++) {
            const int led_num = getPixelNumber(x, HEIGHT - 1);
            
            // заполняем случайно верхнюю строку
            const Color thisColor = it[led_num].get();
            if (isEqualColors(thisColor, Color::BLACK))
                it[led_num] = (random(0, 25) == 0) ? RgbToHsv(0, 255, 0) : light::ESPHSVColor(0, 0, 0);
            else if (compareColors(thisColor, Color(0x002000)) < 0)
                it[led_num] = Color::BLACK;
            else
                it[led_num] = thisColor - Color(0x002000);
        }  

        // сдвигаем всё вниз
        for (byte x = 0; x < WIDTH; x++) {
            for (byte y = 0; y < HEIGHT - 1; y++) {
                it[getPixelNumber(x, y)] = it[getPixelNumber(x, y + 1)].get();
            }
        }
        it.schedule_show();
    }

    void set_update_interval(uint32_t update_interval) { this->update_interval_ = update_interval; }

protected:
    uint32_t last_run_{0};
    uint32_t update_interval_;
};

}  // namespace effects
}  // namespace esphome