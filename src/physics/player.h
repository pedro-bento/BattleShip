#ifndef PLAYER_H
#define PLAYER_H

#include <stdint.h>
#include <stdlib.h>

#include "ship.h"
#include "../system/quadtree.h"

// ShotState
// combination of typedef and enum
// to prevent the unnecessary use of 'int' when we only need 3 values
typedef uint8_t ShotState;
typedef enum
{
  SHOT_STATE_NONE = 0,
  SHOT_STATE_MISS = 1,
  SHOT_STATE_HIT  = 2,
} SHOT_STATE;

// Cell
// represents a map cell
// stores a pointer to a ship if exists or NULL and the Cell ShotState
typedef struct
{
  Ship* ship;
  ShotState shot_state;
} Cell;

Cell* new_cell();
void delete_cell(Cell* cell);

// Player
// represents a player
// stores the player hp and a map (matrix of cells)
typedef struct
{
  int hp;
  QT* map;
} Player;

// new_player
// returns a heap allocated player
// default hp is 0 and all cells from map are set to (NULL, SHOT_STATE_NONE)
Player* new_player(size_t map_size);

// delete_player
// deletes all ships from map, frees the map and player
void delete_player(Player* player, size_t map_size);

// player_get_ship_state
// returns the ship state at pos of its map
// or SHIP_STATE_EMPTY when there is no ship at pos
ShipState player_get_ship_state(Player* player, Vec2i pos);

// player_register_shot
// registers opponent shot in its own map and returns shot state
ShotState player_register_shot(Player* player, Vec2i pos);

#endif // PLAYER_H
