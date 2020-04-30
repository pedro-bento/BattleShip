#ifndef GAME_H
#define GAME_H

#include <stdint.h>
#include <stdbool.h>

#include "../config.h"
#include "player.h"
#include "ship.h"
#include "../math/vec.h"

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
void delete_game(Game* game);
Player* game_get_player_by_id(Game* game, PlayerID id);
bool game_is_valid_ship(Game* game, Ship* ship, PlayerID id, bool ignore_ships);
// returns false if ship was not placed, true otherwise
bool game_player_place_ship(Game* game, Ship* ship, PlayerID id);
void game_player_shoot(Game* game, Vec2i shot, PlayerID id);
bool game_is_over(Game* game);

static inline PlayerID flip_player_id(PlayerID id)
{
  return id == PLAYER1 ? PLAYER2 : PLAYER1;
}

#endif // GAME_H
