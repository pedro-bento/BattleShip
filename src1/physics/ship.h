#ifndef SHIP_H
#define SHIP_H

#include <stdint.h>
#include <stdbool.h>

#include "../config.h"
#include "../math/vec.h"

// to prevent the unnecessary storage of 'int' when we only need 4 values
typedef uint8_t ShipState;
typedef enum
{
  SHIP_STATE_EMPTY = 0,
  SHIP_STATE_GOOD  = 1,
  SHIP_STATE_HIT   = 2,
  SHIP_STATE_MISS  = 3,
} SHIP_STATE;

typedef struct
{
  Vec2i top_left;
  Vec2i bottom_right;
  uint8_t shot_count;
  ShipState states[MAX_SHIP_WIDTH][MAX_SHIP_WIDTH];
} Ship;

void ship_rotate_90(Ship* ship, bool is_clockwise);

#endif // SHIP_H
