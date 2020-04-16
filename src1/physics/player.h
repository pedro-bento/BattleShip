#ifndef PLAYER_H
#define PLAYER_H

#include <stdint.h>
#include <stdlib.h>

#include "ship.h"

typedef uint8_t Shot;
typedef enum
{
  SHOT_STATE_NONE = 0,
  SHOT_STATE_MISS = 1,
  SHOT_STATE_HIT  = 2,
} SHOT_STATE;

typedef struct
{
  Ship* ship;
  Shot shot;
} Cell;

typedef struct
{
  Cell** map;
} Player;

Player* new_player(size_t map_size);
// returns the ship state at pos of its own map
ShipState player_get_ship_state(Player* player, Vec2i pos);

#endif // PLAYER_H
