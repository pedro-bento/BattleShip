#include "color.h"

Color color(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
  return (Color)
  {
    .r = r,
    .g = g,
    .b = b,
    .a = a,
  };
}
