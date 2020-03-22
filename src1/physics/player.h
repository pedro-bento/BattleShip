#ifndef PLAYER_H
#define PLAYER_H

#include <stdint.h>

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
  uint8_t ships_count;
  Ship ships[MAX_NUMBER_OF_SHIPS];
  Cell map[MAX_MAP_SIZE][MAX_MAP_SIZE];
} Player;

Ship* player_get_next_ship(Player* player);

#endif // PLAYER_H
