#ifndef PLAYER_H
#define PLAYER_H

#include "ship.h"
#include "../quadtree.h"
#include "../config.h"
#include "../math/vec2.h"
#include "../math/math.h"

typedef struct
{
  Ship* ships[NUM_OF_SHIPS];
  QT* map;
} Player;

// initializes all ships to NULL and creates a empty map
void player_init_empty(Player* player);
// adds NUM_OF_SHIPS created with player_create_random_ship to player
void player_init_random(Player* player); // it only generates ships according to BattleShip rules
// frees all ships and map
void player_free(Player* player);

// checks if ship exists on top of any artifact or outside of the map
// retuns 1 if valid, otherwise 0
int player_is_valid_ship(Player* player, Ship* ship);
// returns a random and valid ship
Ship* player_create_random_ship(Player* player, int ship_length); // it probably can be improved
// adds a ship to the map and ships array;
// returns 1 if successful, 0 if ship is invalid or ships array is full
int player_add_ship(Player* player, Ship* ship);
// if a ship exists at position "pos" returns it's state, otherwise STATE_NULL
ShipState player_get_map_state(Player* player, Vec2 pos);

// registers hit if there is a ship a position "pos" with STATE_GOOD
// return 1 if hit, otherwise 0
int player_register_hit(Player* player, Vec2 pos);

// returns 1 if player is dead, otherwise 0
int player_is_over(Player* player);

#endif
