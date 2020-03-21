#ifndef COLOR_H
#define COLOR_H

#include <stdint.h>

#define COLOR_BLACK             color(0, 0, 0, 255)
#define COLOR_RADIOACTIVE_GREEN color(93, 202, 49, 255)
#define COLOR_CRIMSON_RED       color(153, 0, 0, 255)

typedef struct
{
  uint8_t r;
  uint8_t g;
  uint8_t b;
  uint8_t a;
} Color;

Color color(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

#endif // COLOR_H
