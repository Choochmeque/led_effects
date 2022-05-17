#ifndef __INC_NOISE_H
#define __INC_NOISE_H

///@defgroup Noise Noise functions
///Perlin noise function definitions
///@{
/// @name scaled 16 bit noise functions
///@{
/// 16 bit, fixed point implementation of Perlin's noise.  Coordinates are
/// 16.16 fixed point values, 32 bit integers with integral coordinates in the high 16
/// bits and fractional in the low 16 bits, and the function takes 1d, 2d, and 3d coordinate
/// values.  These functions are scaled to return 0-65535

extern uint16_t inoise16(uint32_t x, uint32_t y, uint32_t z);
extern uint16_t inoise16(uint32_t x, uint32_t y);
extern uint16_t inoise16(uint32_t x);
///@}

/// @name 8 bit scaled noise functions
///@{
/// 8 bit, fixed point implementation of Perlin's noise.  Coordinates are
/// 8.8 fixed point values, 16 bit integers with integral coordinates in the high 8
/// bits and fractional in the low 8 bits, and the function takes 1d, 2d, and 3d coordinate
/// values.  These functions are scaled to return 0-255
extern uint8_t inoise8(uint16_t x, uint16_t y, uint16_t z);
extern uint8_t inoise8(uint16_t x, uint16_t y);
extern uint8_t inoise8(uint16_t x);
///@}

#endif
