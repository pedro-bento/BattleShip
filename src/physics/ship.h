#ifndef SHIP_H
#define SHIP_H

#include <stdint.h>
#include <stdbool.h>

#include "../config.h"
#include "../math/vec.h"

// ShipState
// combination of typedef and enum
// to prevent the unnecessary use of 'int' when we only need 4 values
typedef uint8_t ShipState;
typedef enum
{
  SHIP_STATE_EMPTY = 0,
  SHIP_STATE_GOOD  = 1,
  SHIP_STATE_HIT   = 2,
  SHIP_STATE_MISS  = 3,
} SHIP_STATE;

// Bitmap
// stores a matrix of ShipStates
typedef struct
{
  ShipState states[MAX_SHIP_WIDTH][MAX_SHIP_WIDTH];
} Bitmap;

// Ship
// represents a ship
// it stores position, footprint and shape
typedef struct
{
  Vec2i top_left;
  Vec2i bottom_right;
  uint8_t area;
  Bitmap bitmap;
} Ship;

// ShipType
// each type represents a different ship shape/form
typedef enum
{
  F,
  I,
  Z,
  H,
  P,
} ShipType;

// new_ship
// returns a heap allocated ship
// default position is ((0,0),(4,4)) and type is passed as parameter
Ship* new_ship(ShipType type);

// delete_ship
// frees the ship
void delete_ship(Ship* ship);

// ship_move
// adds dxy to current ship position
void ship_move(Ship* ship, Vec2i dxy);

// ship_rotate
// rotates the ship by 90 degrees by rotating its bitmap
// direction of rotation is specified in is_clockwise
void ship_rotate(Ship* ship, bool is_clockwise);

#endif // SHIP_H
