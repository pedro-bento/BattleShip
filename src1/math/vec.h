#ifndef VEC_H
#define VEC_H

#include <stdint.h>
#include <stdbool.h>

typedef struct
{
  int16_t x;
  int16_t y;
} Vec2i;

static inline Vec2i vec2i(int16_t x, int16_t y)
{
  return (Vec2i)
  {
    .x = x,
    .y = y,
  };
}

Vec2i vec2i_rotate_90(Vec2i vec, bool is_clockwise);

#endif
