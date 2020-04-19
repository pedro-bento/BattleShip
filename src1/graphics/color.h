#ifndef COLOR_H
#define COLOR_H

#include <stdint.h>

// _A stands for alpha
#define COLOR_BLACK                 color(0, 0, 0, 255)
#define COLOR_RADIOACTIVE_GREEN     color(93, 202, 49, 255)
#define COLOR_FLUORESCENT_YELLOW    color(204, 255, 0, 255)
#define COLOR_SAINT_PATRICK_BLUE_A  color(32, 32, 144, 130)
#define COLOR_RADIOACTIVE_GREEN_A   color(93, 202, 49, 32)
#define COLOR_CRIMSON_RED_A         color(153, 0, 0, 130)
#define COLOR_FLUORESCENT_YELLOW_A  color(204, 255, 0, 155)

typedef struct
{
  uint8_t r;
  uint8_t g;
  uint8_t b;
  uint8_t a;
} Color;

Color color(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

#endif // COLOR_H
