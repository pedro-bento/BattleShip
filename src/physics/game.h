#ifndef GAME_H
#define GAME_H

#include <stdint.h>
#include <stdbool.h>

#include "../config.h"
#include "../math/vec.h"
#include "player.h"
#include "ship.h"

// PlayerID
// used to distinguish player one and two
typedef enum
{
  PLAYER1 = 1,
  PLAYER2 = 2,
} PlayerID;

// Game
// stores game settings and two players
typedef struct
{
  Settings* settings;
  Player* player1;
  Player* player2;
} Game;

// new_game
// returns a heap allocated game object
// default players are equal to the default 'new_player' and settings is passed as parameter
Game* new_game(Settings* settings);

// delete_game
// deletes both players and frees the game object
void delete_game(Game* game);

// game_get_player_by_id
// returns a pointer to a player given an id
Player* game_get_player_by_id(Game* game, PlayerID id);

// game_is_valid_ship
// if 'ignore_ships' is false,
// it checks if a ship is inside a player map and does not overlap other ships
// else, it just checks if a ship is inside a player map
bool game_is_valid_ship(Game* game, Ship* ship, PlayerID id, bool ignore_ships);

// game_player_place_ship
// returns true if ship was successfully placed in a player map
// and false if ship is invalid
bool game_player_place_ship(Game* game, Ship* ship, PlayerID id);

// game_player_shoot
// it performs the 'action' of shooting
// it registers the shot 'shot' in the opponent of 'id'
// and stores the result 'shot_state' in 'id' map
void game_player_shoot(Game* game, Vec2i shot, PlayerID id);

// game_is_over
// checks if game is over
// returns true if it's over or false otherwise
bool game_is_over(Game* game);

// flip_player_id
// flips a PlayerID
// PLAYER1 -> PLAYER2
// PLAYER2 -> PLAYER1
static inline PlayerID flip_player_id(PlayerID id)
{
  return id == PLAYER1 ? PLAYER2 : PLAYER1;
}

#endif // GAME_H
