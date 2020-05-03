#ifndef MATH_H
#define MATH_H

#include <stdlib.h>

// MAX and MIN
// macros that replicate max and min generic functions using ternary operator
#define MAX(a,b) ((a) > (b) ? (a) : (b))
#define MIN(a,b) ((a) < (b) ? (a) : (b))

// rand_range
// returns a random int between min and max
static inline int rand_range(int min, int max)
{
  return rand() % (max + 1 - min) + min;
}

#endif
