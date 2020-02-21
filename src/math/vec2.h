#ifndef VEC2_H
#define VEC2_H

#include <stdint.h>

// Currently there is no need for more than uint_8
typedef struct
{
  int8_t x;
  int8_t y;
} Vec2;

// can be passed by value because it's size is less tha a pointers size
static inline Vec2 vec2(int8_t x, int8_t y)
{
  Vec2 v = {x, y};
  return v;
}

static inline Vec2 scalar(Vec2 u, int8_t s)
{
  Vec2 v = {u.x * s, u.y * s};
  return v;
}

static inline Vec2 add(Vec2 u, Vec2 v)
{
  Vec2 e = {u.x + v.x, u.y + v.y};
  return e;
}

static inline int equal(Vec2 u, Vec2 v)
{
  return u.x == v.x && u.y == v.y;
}

#endif // VEC2_H
