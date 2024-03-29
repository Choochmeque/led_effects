#ifndef __INC_COLORUTILS_H
#define __INC_COLORUTILS_H

#include "esphome/components/light/esp_hsv_color.h"
#include "esphome/components/light/addressable_light_effect.h"

#include "lib8tion.h"

#define saccum87 int16_t

// fill_gradient_RGB - fill a range of LEDs with a smooth RGB gradient
//                     between two specified RGB colors.
//                     Unlike HSV, there is no 'color wheel' in RGB space,
//                     and therefore there's only one 'direction' for the
//                     gradient to go, and no 'direction code' is needed.
void fill_gradient_RGB(esphome::Color *leds,
                       uint16_t startpos, esphome::Color startcolor,
                       uint16_t endpos,   esphome::Color endcolor);
void fill_gradient_RGB(esphome::Color *leds, uint16_t numLeds, const esphome::Color &c1, const esphome::Color &c2);
void fill_gradient_RGB(esphome::Color *leds, uint16_t numLeds, const esphome::Color &c1, const esphome::Color &c2, const esphome::Color &c3);
void fill_gradient_RGB(esphome::Color *leds, uint16_t numLeds, const esphome::Color &c1, const esphome::Color &c2, const esphome::Color &c3, const esphome::Color &c4);

// nblend - destructively modifies one color, blending
//          in a given fraction of an overlay color
esphome::Color& nblend( esphome::Color& existing, const esphome::Color& overlay, fract8 amountOfOverlay );

// Palettes
//
// RGB Palettes map an 8-bit value (0..255) to an RGB color.
//
// You can create any color palette you wish; a couple of starters
// are provided: Forest, Clouds, Lava, Ocean, Rainbow, and Rainbow Stripes.
//
// Palettes come in the traditional 256-entry variety, which take
// up 768 bytes of RAM, and lightweight 16-entry varieties.  The 16-entry
// variety automatically interpolates between its entries to produce
// a full 256-element color map, but at a cost of only 48 bytes or RAM.
//
// Basic operation is like this: (example shows the 16-entry variety)
// 1. Declare your palette storage:
//    CRGBPalette16 myPalette;
//
// 2. Fill myPalette with your own 16 colors, or with a preset color scheme.
//    You can specify your 16 colors a variety of ways:
//      CRGBPalette16 myPalette(
//          CRGB::Black,
//          CRGB::Black,
//          CRGB::Red,
//          CRGB::Yellow,
//          CRGB::Green,
//          CRGB::Blue,
//          CRGB::Purple,
//          CRGB::Black,
//
//          0x100000,
//          0x200000,
//          0x400000,
//          0x800000,
//
//          CHSV( 30,255,255),
//          CHSV( 50,255,255),
//          CHSV( 70,255,255),
//          CHSV( 90,255,255)
//      );
//
//    Or you can initiaize your palette with a preset color scheme:
//      myPalette = RainbowStripesColors_p;
//
// 3. Any time you want to set a pixel to a color from your palette, use
//    "ColorFromPalette(...)" as shown:
//
//      uint8_t index = /* any value 0..255 */;
//      leds[i] = ColorFromPalette( myPalette, index);
//
//    Even though your palette has only 16 explicily defined entries, you
//    can use an 'index' from 0..255.  The 16 explicit palette entries will
//    be spread evenly across the 0..255 range, and the intermedate values
//    will be RGB-interpolated between adjacent explicit entries.
//
//    It's easier to use than it sounds.
//

class CRGBPalette16;
class CRGBPalette32;
class CRGBPalette256;
class CHSVPalette16;
class CHSVPalette32;
class CHSVPalette256;
typedef uint32_t TProgmemRGBPalette16[16];
typedef uint32_t TProgmemHSVPalette16[16];
#define TProgmemPalette16 TProgmemRGBPalette16
typedef uint32_t TProgmemRGBPalette32[32];
typedef uint32_t TProgmemHSVPalette32[32];
#define TProgmemPalette32 TProgmemRGBPalette32

class CRGBPalette16 {
public:
    esphome::Color entries[16];
    CRGBPalette16() {};

    CRGBPalette16(const CRGBPalette16& rhs)
    {
        memmove8((void *) &(entries[0]), &(rhs.entries[0]), sizeof(entries));
    }
    CRGBPalette16(const esphome::Color rhs[16])
    {
        memmove8( (void *) &(entries[0]), &(rhs[0]), sizeof(entries));
    }
    CRGBPalette16& operator=(const CRGBPalette16& rhs)
    {
        memmove8((void *) &(entries[0]), &(rhs.entries[0]), sizeof(entries));
        return *this;
    }
    CRGBPalette16& operator=(const esphome::Color rhs[16])
    {
        memmove8( (void *) &(entries[0]), &(rhs[0]), sizeof(entries));
        return *this;
    }

    CRGBPalette16( const TProgmemRGBPalette16& rhs)
    {
        for( uint8_t i = 0; i < 16; ++i) {
            entries[i] = esphome::Color(pgm_read_dword_near(rhs + i));
        }
    }
    CRGBPalette16& operator=( const TProgmemRGBPalette16& rhs)
    {
        for( uint8_t i = 0; i < 16; ++i) {
            entries[i] = esphome::Color(pgm_read_dword_near(rhs + i));
        }
        return *this;
    }

    bool operator==( const CRGBPalette16 rhs)
    {
        const uint8_t* p = (const uint8_t*)(&(this->entries[0]));
        const uint8_t* q = (const uint8_t*)(&(rhs.entries[0]));
        if( p == q) return true;
        for( uint8_t i = 0; i < (sizeof( entries)); ++i) {
            if( *p != *q) return false;
            ++p;
            ++q;
        }
        return true;
    }
    bool operator!=( const CRGBPalette16 rhs)
    {
        return !( *this == rhs);
    }
    
    inline esphome::Color& operator[] (uint8_t x) __attribute__((always_inline))
    {
        return entries[x];
    }
    inline const esphome::Color& operator[] (uint8_t x) const __attribute__((always_inline))
    {
        return entries[x];
    }

    inline esphome::Color& operator[] (int x) __attribute__((always_inline))
    {
        return entries[(uint8_t)x];
    }
    inline const esphome::Color& operator[] (int x) const __attribute__((always_inline))
    {
        return entries[(uint8_t)x];
    }

    operator esphome::Color*()
    {
        return &(entries[0]);
    }

    CRGBPalette16(const esphome::Color &c1, const esphome::Color &c2)
    {
        fill_gradient_RGB(&(entries[0]), 16, c1, c2);
    }
    CRGBPalette16(const esphome::Color &c1, const esphome::Color &c2, const esphome::Color &c3)
    {
        fill_gradient_RGB(&(entries[0]), 16, c1, c2, c3);
    }
    CRGBPalette16(const esphome::Color &c1, const esphome::Color &c2, const esphome::Color &c3, const esphome::Color &c4)
    {
        fill_gradient_RGB(&(entries[0]), 16, c1, c2, c3, c4);
    }
};

typedef enum { NOBLEND=0, LINEARBLEND=1 } TBlendType;

esphome::Color ColorFromPalette(const CRGBPalette16& pal,
                      uint8_t index,
                      uint8_t brightness=255,
                      TBlendType blendType=LINEARBLEND);

esphome::Color ColorFromPalette(const TProgmemRGBPalette16& pal,
                       uint8_t index,
                       uint8_t brightness=255,
                       TBlendType blendType=LINEARBLEND);

#endif // __INC_COLORUTILS_H