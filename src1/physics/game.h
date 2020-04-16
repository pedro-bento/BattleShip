#ifndef GAME_H
#define GAME_H

#include <stdint.h>
#include <stdbool.h>

#include "../config.h"
#include "player.h"
#include "ship.h"

typedef enum
{
  PLAYER1 = 1,
  PLAYER2 = 2,
} PlayerID;

typedef struct
{
  Settings* settings;
  Player* player1;
  Player* player2;
} Game;

Game* new_game(Settings* settings);
Player* game_get_player_by_id(Game* game, PlayerID id);
bool game_is_valid_ship(Game* game, Ship* ship, PlayerID id, bool ignore_ships);
// returns false if ship was not placed, true otherwise
bool game_player_place_ship(Game* game, Ship* ship, PlayerID id);

#endif // GAME_H
