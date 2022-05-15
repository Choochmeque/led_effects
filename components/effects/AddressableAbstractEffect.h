#pragma once

#include "esphome/core/component.h"
#include "esphome/components/light/esp_hsv_color.h"
#include "esphome/components/light/addressable_light_effect.h"

#include "EffectsManager.h"

#include "colorutils.h"

namespace esphome {
namespace effects {

const TProgmemRGBPalette16 *colorPallettes[] = {
    &PartyColors_p,
    &OceanColors_p,
    &LavaColors_p,
    &HeatColors_p,
    &WaterfallColors_p,
    &CloudColors_p,
    &ForestColors_p,
    &RainbowColors_p,
    &RainbowStripeColors_p
};
class AddressableAbstractEffect : public light::AddressableLightEffect 
{
public:
    AddressableAbstractEffect(const std::string &name) : AddressableLightEffect(name) {}

    void set_update_interval(uint32_t update_interval) { this->update_interval_ = update_interval; }

    void set_scale(uint8_t scale) { this->scale_ = scale; }

    void set_manager(EffectsManager *manager) { this->manager_ = manager; }

protected:
    uint32_t last_run_{0};
    uint32_t update_interval_;
    uint8_t scale_;
    EffectsManager *manager_{nullptr};

protected:
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
        const byte _WIDTH = this->manager_->width();
        
        if ((THIS_Y % 2 == 0) || MATRIX_TYPE) {               // если чётная строка
            return (THIS_Y * _WIDTH + THIS_X);
        } 
        else {                                                // если нечётная строка
            return (THIS_Y * _WIDTH + _WIDTH - THIS_X - 1);
        } 
    }

    uint32_t colorcode(const Color &color)
    {
        return uint32_t{color.red} << 16 |
            uint32_t{color.green} << 8 |
            uint32_t{color.blue};
    }

    void dimAll(light::AddressableLight &it, uint8_t value)
    {
        for (uint16_t i = 0; i < this->manager_->num_leds(); i++) {
            it[i] = nscale8(it[i].get(), value);
        }
    }

    /// scale down a RGB to N 256ths of it's current brightness, using
    /// 'plain math' dimming rules, which means that if the low light levels
    /// may dim all the way to 100% black.
    inline Color nscale8 (const Color &color, uint8_t scaledown )
    {
        uint8_t r = color.r;
        uint8_t g = color.g;
        uint8_t b = color.b;
        nscale8x3(r, g, b, scaledown);
        return Color(r, g, b);
    }

    const TProgmemRGBPalette16 *GetColorPalette(uint8_t pct)
    {
        return colorPallettes[(uint8_t)(pct / 100.0f * ((sizeof(colorPallettes) / sizeof(TProgmemRGBPalette16 *)) - 0.01f))];
    }

    uint8_t MATRIX_TYPE{0};
};

}  // namespace effects
}  // namespace esphome