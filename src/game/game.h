#ifndef WORLD_H
#define WORLD_H

#include "ship.h"
#include "player.h"
#include "../config.h"

typedef enum
{
  PLAYING,
  PLAYER1_WIN,
  PLAYER2_WIN,
} Game_State;

typedef enum
{
  PLAYER1,
  PLAYER2,
} GamePlayer;

typedef struct
{
  Player player1;
  Player player2;
  Game_State state;
} Game;

// allocates Game object
// default values: same as game_init_empty
Game* game_create();
// deallocates game and players
void game_destroy(Game* game);

// frees players
void game_free(Game* game);
// initializes empty players
void game_init_empty(Game* game);

// returns a random and valid ship for player
Ship* game_create_random_ship(Game* game, GamePlayer player, ShipType type, int ship_length);
// adds ship to player
// returns 1 if successful, otherwise 0
int game_player_place_ship(Game* game, GamePlayer player, Ship* ship);
// registers player shot at position "pos"
// if hit checks if opponet is_over
// if opponet is_over updates state
void game_player_shoot(Game* game, GamePlayer player, Vec2 pos);
// if a ship exists at position "pos" on defined player's map returns it's state,
// otherwise STATE_NULL
char game_player_get_map_state(Game* game, GamePlayer player, Vec2 pos);

#endif
