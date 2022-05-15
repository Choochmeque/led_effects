#pragma once

#include "AddressableAbstractEffect.h"


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