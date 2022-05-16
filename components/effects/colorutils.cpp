
#include "colorutils.h"

void fill_gradient_RGB(esphome::Color *leds,
                   uint16_t startpos, esphome::Color startcolor,
                   uint16_t endpos,   esphome::Color endcolor )
{
    // if the points are in the wrong order, straighten them
    if(endpos < startpos) {
        uint16_t t = endpos;
        esphome::Color tc = endcolor;
        endcolor = startcolor;
        endpos = startpos;
        startpos = t;
        startcolor = tc;
    }

    saccum87 rdistance87;
    saccum87 gdistance87;
    saccum87 bdistance87;

    rdistance87 = (endcolor.r - startcolor.r) << 7;
    gdistance87 = (endcolor.g - startcolor.g) << 7;
    bdistance87 = (endcolor.b - startcolor.b) << 7;

    uint16_t pixeldistance = endpos - startpos;
    int16_t divisor = pixeldistance ? pixeldistance : 1;

    saccum87 rdelta87 = rdistance87 / divisor;
    saccum87 gdelta87 = gdistance87 / divisor;
    saccum87 bdelta87 = bdistance87 / divisor;

    rdelta87 *= 2;
    gdelta87 *= 2;
    bdelta87 *= 2;

    accum88 r88 = startcolor.r << 8;
    accum88 g88 = startcolor.g << 8;
    accum88 b88 = startcolor.b << 8;
    for( uint16_t i = startpos; i <= endpos; ++i) {
        leds[i] = esphome::Color(r88 >> 8, g88 >> 8, b88 >> 8);
        r88 += rdelta87;
        g88 += gdelta87;
        b88 += bdelta87;
    }
}

void fill_gradient_RGB(esphome::Color *leds, uint16_t numLeds, const esphome::Color &c1, const esphome::Color &c2)
{
    uint16_t last = numLeds - 1;
    fill_gradient_RGB(leds, 0, c1, last, c2);
}

void fill_gradient_RGB(esphome::Color *leds, uint16_t numLeds, const esphome::Color &c1, const esphome::Color &c2, const esphome::Color &c3)
{
    uint16_t half = (numLeds / 2);
    uint16_t last = numLeds - 1;
    fill_gradient_RGB(leds,    0, c1, half, c2);
    fill_gradient_RGB(leds, half, c2, last, c3);
}

void fill_gradient_RGB(esphome::Color *leds, uint16_t numLeds, const esphome::Color &c1, const esphome::Color &c2, const esphome::Color &c3, const esphome::Color &c4)
{
    uint16_t onethird = (numLeds / 3);
    uint16_t twothirds = ((numLeds * 2) / 3);
    uint16_t last = numLeds - 1;
    fill_gradient_RGB(leds,         0, c1,  onethird, c2);
    fill_gradient_RGB(leds,  onethird, c2, twothirds, c3);
    fill_gradient_RGB(leds, twothirds, c3,      last, c4);
}

// lsrX4: helper function to divide a number by 16, aka four LSR's.
// On avr-gcc, "u8 >> 4" generates a loop, which is big, and slow.
// merely forcing it to be four /=2's causes avr-gcc to emit
// a SWAP instruction followed by an AND 0x0F, which is faster, and smaller.
inline uint8_t lsrX4( uint8_t dividend) __attribute__((always_inline));
inline uint8_t lsrX4( uint8_t dividend)
{
#if defined(__AVR__)
    dividend /= 2;
    dividend /= 2;
    dividend /= 2;
    dividend /= 2;
#else
    dividend >>= 4;
#endif
    return dividend;
}

esphome::Color ColorFromPalette( const TProgmemRGBPalette16& pal, uint8_t index, uint8_t brightness, TBlendType blendType)
{
    //      hi4 = index >> 4;
    uint8_t hi4 = lsrX4(index);
    uint8_t lo4 = index & 0x0F;

    esphome::Color entry   =  esphome::Color(pgm_read_dword_near( &(pal[0]) + hi4 ));

    uint8_t red1   = entry.red;
    uint8_t green1 = entry.green;
    uint8_t blue1  = entry.blue;

    uint8_t blend = lo4 && (blendType != NOBLEND);

    if( blend ) {

        if( hi4 == 15 ) {
            entry =   esphome::Color(pgm_read_dword_near( &(pal[0]) ));
        } else {
            entry =   esphome::Color(pgm_read_dword_near( &(pal[1]) + hi4 ));
        }

        uint8_t f2 = lo4 << 4;
        uint8_t f1 = 255 - f2;

        uint8_t red2   = entry.red;
        red1   = scale8_LEAVING_R1_DIRTY( red1,   f1);
        red2   = scale8_LEAVING_R1_DIRTY( red2,   f2);
        red1   += red2;

        uint8_t green2 = entry.green;
        green1 = scale8_LEAVING_R1_DIRTY( green1, f1);
        green2 = scale8_LEAVING_R1_DIRTY( green2, f2);
        green1 += green2;

        uint8_t blue2  = entry.blue;
        blue1  = scale8_LEAVING_R1_DIRTY( blue1,  f1);
        blue2  = scale8_LEAVING_R1_DIRTY( blue2,  f2);
        blue1  += blue2;

        cleanup_R1();
    }

    if( brightness != 255) {
        if( brightness ) {
            ++brightness; // adjust for rounding
            // Now, since brightness is nonzero, we don't need the full scale8_video logic;
            // we can just to scale8 and then add one (unless scale8 fixed) to all nonzero inputs.
            if( red1 )   {
                red1 = scale8_LEAVING_R1_DIRTY( red1, brightness);
#if !(FASTLED_SCALE8_FIXED==1)
                ++red1;
#endif
            }
            if( green1 ) {
                green1 = scale8_LEAVING_R1_DIRTY( green1, brightness);
#if !(FASTLED_SCALE8_FIXED==1)
                ++green1;
#endif
            }
            if( blue1 )  {
                blue1 = scale8_LEAVING_R1_DIRTY( blue1, brightness);
#if !(FASTLED_SCALE8_FIXED==1)
                ++blue1;
#endif
            }
            cleanup_R1();
        } else {
            red1 = 0;
            green1 = 0;
            blue1 = 0;
        }
    }

    return esphome::Color( red1, green1, blue1);
}
