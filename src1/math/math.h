#ifndef MATH_H
#define MATH_H

#include <stdlib.h>

#define MAX(a,b) ((a) > (b) ? (a) : (b))
#define MIN(a,b) ((a) < (b) ? (a) : (b))

static inline int rand_range(int min, int max)
{
  return rand() % (max + 1 - min) + min;
}

#endif
