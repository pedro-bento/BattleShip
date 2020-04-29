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
  ShipState states[MAX_SHIP_WIDTH][MAX_SHIP_WIDTH];
} Bitmap;

typedef struct
{
  Vec2i top_left;
  Vec2i bottom_right;
  uint8_t area;
  Bitmap bitmap;
} Ship;

typedef enum
{
  F,
  I,
  Z,
  H,
  P,
} ShipType;

Ship* new_ship(ShipType type);
void  delete_ship(Ship* ship);

void ship_move(Ship* ship, Vec2i dxy);
void ship_rotate(Ship* ship, bool is_clockwise);

#endif // SHIP_H
