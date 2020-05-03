#ifndef VEC_H
#define VEC_H

#include <stdint.h>
#include <stdbool.h>

// Vec2i
// 2D vector in discrete space
typedef struct
{
  int16_t x;
  int16_t y;
} Vec2i;

// vec2i
// creates 2D vector
// no need to malloc since Vec2i only has 32 bits (same as int)
// this means this object will always be passed by value
static inline Vec2i vec2i(int16_t x, int16_t y)
{
  return (Vec2i)
  {
    .x = x,
    .y = y,
  };
}

// vec2i_add
// sums two Vec2i and returns the result
static inline Vec2i vec2i_add(Vec2i u, Vec2i v)
{
  return vec2i(u.x + v.x, u.y + v.y);
}

#endif
