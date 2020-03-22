#include <math.h>

#include "vec.h"

Vec2i vec2i_rotate_90(Vec2i vec, bool is_clockwise)
{
  const int16_t dir = is_clockwise ? 1 : -1;
  return vec2i(vec.y * dir, vec.x * -dir);
}
