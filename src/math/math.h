#ifndef MATH_H
#define MATH_H

#include <stdint.h>

#define MAX(a,b) ((a) >= (b) ? (a) : (b))
#define MIN(a,b) ((a) <= (b) ? (a) : (b))

// RANDOM NUMBERS GENERATION
static uint32_t rdn_seed = 13;

// Park-Miller RNG
static inline uint32_t rdn()
{
  return rdn_seed = (uint64_t)rdn_seed * 48271 % 0x7fffffff;
}

static inline int rdn_range(int min, int max)
{
  return min + rdn() % (max + 1 - min);
}

#endif // MATH_H
