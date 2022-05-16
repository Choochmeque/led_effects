#pragma once

#include "esphome/core/component.h"
#include "esphome/components/light/esp_hsv_color.h"
#include "esphome/components/light/addressable_light_effect.h"

#include "EffectsManager.h"

#include "colorutils.h"

namespace esphome {
namespace effects {

    /// Predefined RGB colors
    typedef enum {
        AliceBlue=0xF0F8FF,
        Amethyst=0x9966CC,
        AntiqueWhite=0xFAEBD7,
        Aqua=0x00FFFF,
        Aquamarine=0x7FFFD4,
        Azure=0xF0FFFF,
        Beige=0xF5F5DC,
        Bisque=0xFFE4C4,
        Black=0x000000,
        BlanchedAlmond=0xFFEBCD,
        Blue=0x0000FF,
        BlueViolet=0x8A2BE2,
        Brown=0xA52A2A,
        BurlyWood=0xDEB887,
        CadetBlue=0x5F9EA0,
        Chartreuse=0x7FFF00,
        Chocolate=0xD2691E,
        Coral=0xFF7F50,
        CornflowerBlue=0x6495ED,
        Cornsilk=0xFFF8DC,
        Crimson=0xDC143C,
        Cyan=0x00FFFF,
        DarkBlue=0x00008B,
        DarkCyan=0x008B8B,
        DarkGoldenrod=0xB8860B,
        DarkGray=0xA9A9A9,
        DarkGrey=0xA9A9A9,
        DarkGreen=0x006400,
        DarkKhaki=0xBDB76B,
        DarkMagenta=0x8B008B,
        DarkOliveGreen=0x556B2F,
        DarkOrange=0xFF8C00,
        DarkOrchid=0x9932CC,
        DarkRed=0x8B0000,
        DarkSalmon=0xE9967A,
        DarkSeaGreen=0x8FBC8F,
        DarkSlateBlue=0x483D8B,
        DarkSlateGray=0x2F4F4F,
        DarkSlateGrey=0x2F4F4F,
        DarkTurquoise=0x00CED1,
        DarkViolet=0x9400D3,
        DeepPink=0xFF1493,
        DeepSkyBlue=0x00BFFF,
        DimGray=0x696969,
        DimGrey=0x696969,
        DodgerBlue=0x1E90FF,
        FireBrick=0xB22222,
        FloralWhite=0xFFFAF0,
        ForestGreen=0x228B22,
        Fuchsia=0xFF00FF,
        Gainsboro=0xDCDCDC,
        GhostWhite=0xF8F8FF,
        Gold=0xFFD700,
        Goldenrod=0xDAA520,
        Gray=0x808080,
        Grey=0x808080,
        Green=0x008000,
        GreenYellow=0xADFF2F,
        Honeydew=0xF0FFF0,
        HotPink=0xFF69B4,
        IndianRed=0xCD5C5C,
        Indigo=0x4B0082,
        Ivory=0xFFFFF0,
        Khaki=0xF0E68C,
        Lavender=0xE6E6FA,
        LavenderBlush=0xFFF0F5,
        LawnGreen=0x7CFC00,
        LemonChiffon=0xFFFACD,
        LightBlue=0xADD8E6,
        LightCoral=0xF08080,
        LightCyan=0xE0FFFF,
        LightGoldenrodYellow=0xFAFAD2,
        LightGreen=0x90EE90,
        LightGrey=0xD3D3D3,
        LightPink=0xFFB6C1,
        LightSalmon=0xFFA07A,
        LightSeaGreen=0x20B2AA,
        LightSkyBlue=0x87CEFA,
        LightSlateGray=0x778899,
        LightSlateGrey=0x778899,
        LightSteelBlue=0xB0C4DE,
        LightYellow=0xFFFFE0,
        Lime=0x00FF00,
        LimeGreen=0x32CD32,
        Linen=0xFAF0E6,
        Magenta=0xFF00FF,
        Maroon=0x800000,
        MediumAquamarine=0x66CDAA,
        MediumBlue=0x0000CD,
        MediumOrchid=0xBA55D3,
        MediumPurple=0x9370DB,
        MediumSeaGreen=0x3CB371,
        MediumSlateBlue=0x7B68EE,
        MediumSpringGreen=0x00FA9A,
        MediumTurquoise=0x48D1CC,
        MediumVioletRed=0xC71585,
        MidnightBlue=0x191970,
        MintCream=0xF5FFFA,
        MistyRose=0xFFE4E1,
        Moccasin=0xFFE4B5,
        NavajoWhite=0xFFDEAD,
        Navy=0x000080,
        OldLace=0xFDF5E6,
        Olive=0x808000,
        OliveDrab=0x6B8E23,
        Orange=0xFFA500,
        OrangeRed=0xFF4500,
        Orchid=0xDA70D6,
        PaleGoldenrod=0xEEE8AA,
        PaleGreen=0x98FB98,
        PaleTurquoise=0xAFEEEE,
        PaleVioletRed=0xDB7093,
        PapayaWhip=0xFFEFD5,
        PeachPuff=0xFFDAB9,
        Peru=0xCD853F,
        Pink=0xFFC0CB,
        Plaid=0xCC5533,
        Plum=0xDDA0DD,
        PowderBlue=0xB0E0E6,
        Purple=0x800080,
        Red=0xFF0000,
        RosyBrown=0xBC8F8F,
        RoyalBlue=0x4169E1,
        SaddleBrown=0x8B4513,
        Salmon=0xFA8072,
        SandyBrown=0xF4A460,
        SeaGreen=0x2E8B57,
        Seashell=0xFFF5EE,
        Sienna=0xA0522D,
        Silver=0xC0C0C0,
        SkyBlue=0x87CEEB,
        SlateBlue=0x6A5ACD,
        SlateGray=0x708090,
        SlateGrey=0x708090,
        Snow=0xFFFAFA,
        SpringGreen=0x00FF7F,
        SteelBlue=0x4682B4,
        Tan=0xD2B48C,
        Teal=0x008080,
        Thistle=0xD8BFD8,
        Tomato=0xFF6347,
        Turquoise=0x40E0D0,
        Violet=0xEE82EE,
        Wheat=0xF5DEB3,
        White=0xFFFFFF,
        WhiteSmoke=0xF5F5F5,
        Yellow=0xFFFF00,
        YellowGreen=0x9ACD32,

        // LED RGB color that roughly approximates
        // the color of incandescent fairy lights,
        // assuming that you're using FastLED
        // color correction on your LEDs (recommended).
        FairyLight=0xFFE42D,
        // If you are using no color correction, use this
        FairyLightNCC=0xFF9D2A

    } HTMLColorCode;

// Preset color schemes, such as they are.

// These schemes are all declared as "PROGMEM", meaning
// that they won't take up SRAM on AVR chips until used.
// Furthermore, the compiler won't even include these
// in your PROGMEM (flash) storage unless you specifically
// use each one, so you only 'pay for' those you actually use.


const TProgmemRGBPalette16 CloudColors_p PROGMEM =
{
    HTMLColorCode::Blue,
    HTMLColorCode::DarkBlue,
    HTMLColorCode::DarkBlue,
    HTMLColorCode::DarkBlue,

    HTMLColorCode::DarkBlue,
    HTMLColorCode::DarkBlue,
    HTMLColorCode::DarkBlue,
    HTMLColorCode::DarkBlue,

    HTMLColorCode::Blue,
    HTMLColorCode::DarkBlue,
    HTMLColorCode::SkyBlue,
    HTMLColorCode::SkyBlue,

    HTMLColorCode::LightBlue,
    HTMLColorCode::White,
    HTMLColorCode::LightBlue,
    HTMLColorCode::SkyBlue
};

const TProgmemRGBPalette16 LavaColors_p PROGMEM =
{
    HTMLColorCode::Black,
    HTMLColorCode::Maroon,
    HTMLColorCode::Black,
    HTMLColorCode::Maroon,

    HTMLColorCode::DarkRed,
    HTMLColorCode::Maroon,
    HTMLColorCode::DarkRed,

    HTMLColorCode::DarkRed,
    HTMLColorCode::DarkRed,
    HTMLColorCode::Red,
    HTMLColorCode::Orange,

    HTMLColorCode::White,
    HTMLColorCode::Orange,
    HTMLColorCode::Red,
    HTMLColorCode::DarkRed
};

const TProgmemRGBPalette16 OceanColors_p PROGMEM =
{
    HTMLColorCode::MidnightBlue,
    HTMLColorCode::DarkBlue,
    HTMLColorCode::MidnightBlue,
    HTMLColorCode::Navy,

    HTMLColorCode::DarkBlue,
    HTMLColorCode::MediumBlue,
    HTMLColorCode::SeaGreen,
    HTMLColorCode::Teal,

    HTMLColorCode::CadetBlue,
    HTMLColorCode::Blue,
    HTMLColorCode::DarkCyan,
    HTMLColorCode::CornflowerBlue,

    HTMLColorCode::Aquamarine,
    HTMLColorCode::SeaGreen,
    HTMLColorCode::Aqua,
    HTMLColorCode::LightSkyBlue
};

const TProgmemRGBPalette16 ForestColors_p PROGMEM =
{
    HTMLColorCode::DarkGreen,
    HTMLColorCode::DarkGreen,
    HTMLColorCode::DarkOliveGreen,
    HTMLColorCode::DarkGreen,

    HTMLColorCode::Green,
    HTMLColorCode::ForestGreen,
    HTMLColorCode::OliveDrab,
    HTMLColorCode::Green,

    HTMLColorCode::SeaGreen,
    HTMLColorCode::MediumAquamarine,
    HTMLColorCode::LimeGreen,
    HTMLColorCode::YellowGreen,

    HTMLColorCode::LightGreen,
    HTMLColorCode::LawnGreen,
    HTMLColorCode::MediumAquamarine,
    HTMLColorCode::ForestGreen
};

/// Approximate "black body radiation" palette, akin to
/// the FastLED 'HeatColor' function.
/// Recommend that you use values 0-240 rather than
/// the usual 0-255, as the last 15 colors will be
/// 'wrapping around' from the hot end to the cold end,
/// which looks wrong.
const TProgmemRGBPalette16 HeatColors_p PROGMEM =
{
    0x000000,
    0x330000, 0x660000, 0x990000, 0xCC0000, 0xFF0000,
    0xFF3300, 0xFF6600, 0xFF9900, 0xFFCC00, 0xFFFF00,
    0xFFFF33, 0xFFFF66, 0xFFFF99, 0xFFFFCC, 0xFFFFFF
};

/// HSV Rainbow
const TProgmemRGBPalette16 RainbowColors_p PROGMEM =
{
    0xFF0000, 0xD52A00, 0xAB5500, 0xAB7F00,
    0xABAB00, 0x56D500, 0x00FF00, 0x00D52A,
    0x00AB55, 0x0056AA, 0x0000FF, 0x2A00D5,
    0x5500AB, 0x7F0081, 0xAB0055, 0xD5002B
};

/// HSV Rainbow colors with alternatating stripes of black
#define RainbowStripesColors_p RainbowStripeColors_p
const TProgmemRGBPalette16 RainbowStripeColors_p PROGMEM =
{
    0xFF0000, 0x000000, 0xAB5500, 0x000000,
    0xABAB00, 0x000000, 0x00FF00, 0x000000,
    0x00AB55, 0x000000, 0x0000FF, 0x000000,
    0x5500AB, 0x000000, 0xAB0055, 0x000000
};

/// HSV color ramp: blue purple ping red orange yellow (and back)
/// Basically, everything but the greens, which tend to make
/// people's skin look unhealthy.  This palette is good for
/// lighting at a club or party, where it'll be shining on people.
const TProgmemRGBPalette16 PartyColors_p PROGMEM =
{
    0x5500AB, 0x84007C, 0xB5004B, 0xE5001B,
    0xE81700, 0xB84700, 0xAB7700, 0xABAB00,
    0xAB5500, 0xDD2200, 0xF2000E, 0xC2003E,
    0x8F0071, 0x5F00A1, 0x2F00D0, 0x0007F9
};

const TProgmemRGBPalette16 WaterfallColors_p PROGMEM = 
{
  0x000000, 0x060707, 0x101110, 0x151717,
  0x1C1D22, 0x242A28, 0x363B3A, 0x313634,
  0x505552, 0x6B6C70, 0x98A4A1, 0xC1C2C1,
  0xCACECF, 0xCDDEDD, 0xDEDFE0, 0xB2BAB9
};

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

    void applyBlur2d(light::AddressableLight &it, uint8_t amount)
    {
        blur2d(it, this->manager_->width(), this->manager_->height(), amount);
    }

    void blur2d(light::AddressableLight &it, uint8_t width, uint8_t height, fract8 blur_amount)
    {
        blurRows(it, width, height, blur_amount);
        blurColumns(it, width, height, blur_amount);
    }

    void blurRows(light::AddressableLight &it, uint8_t width, uint8_t height, fract8 blur_amount)
    {
        // blur rows same as columns, for irregular matrix
        uint8_t keep = 255 - blur_amount;
        uint8_t seep = blur_amount >> 1;
        for( uint8_t row = 0; row < height; row++) {
            Color carryover = Color::BLACK;
            for( uint8_t i = 0; i < width; i++) {
                Color cur = it[getPixelNumber(i, row)].get();
                Color part = cur;
                part = nscale8(part, seep);
                cur = nscale8(cur, keep);
                cur += carryover;
                if(i) {
                    Color c = it[getPixelNumber(i-1, row)].get();
                    c += part;
                    it[getPixelNumber(i-1, row)] = c;
                }
                it[getPixelNumber(i, row)] = cur;
                carryover = part;
            }
        }
    }

    // blurColumns: perform a blur1d on each column of a rectangular matrix
    void blurColumns(light::AddressableLight &it, uint8_t width, uint8_t height, fract8 blur_amount)
    {
        // blur columns
        uint8_t keep = 255 - blur_amount;
        uint8_t seep = blur_amount >> 1;
        for( uint8_t col = 0; col < width; ++col) {
            Color carryover = Color::BLACK;
            for( uint8_t i = 0; i < height; ++i) {
                Color cur = it[getPixelNumber(col, i)].get();
                Color part = cur;
                nscale8(part, seep);
                nscale8(cur, keep);
                cur += carryover;
                if(i) {
                    Color c = it[getPixelNumber(col, i-1)].get();
                    c += part;
                    it[getPixelNumber(col, i-1)] = c;
                }
                it[getPixelNumber(col,i)] = cur;
                carryover = part;
            }
        }
    }

    void blendPixelXY(light::AddressableLight &it, uint8_t x, uint8_t y, const Color &color, uint8_t amount)
    {
        Color c = it[getPixelNumber(x, y)].get();
        nblend(c, color, amount);
        it[getPixelNumber(x, y)] = c;
    }

    uint8_t wrapX(int8_t x)
    {
        return mod8(x + this->manager_->width(), this->manager_->width());
    }

    uint8_t wrapY(int8_t y)
    {
        return mod8(y + this->manager_->height(), this->manager_->height());
    }

    void fadeToBlackBy(light::AddressableLight &it, uint8_t step)
    {
        for (uint16_t i = 0; i < this->manager_->num_leds(); i++) {
            it[i].fadeToBlackBy(step);
        }
    }

    uint8_t MATRIX_TYPE{0};
};

}  // namespace effects
}  // namespace esphome