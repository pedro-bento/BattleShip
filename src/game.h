#ifndef WORLD_H
#define WORLD_H

#include "ship.h"

// acording to BattleShip rules
#define MAP_LENGTH 10
#define NUM_OF_SHIPS 5

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
} Player;

typedef struct
{
  Ship* player1[NUM_OF_SHIPS];
  Ship* player2[NUM_OF_SHIPS];
  Game_State state;
} Game;

// initializes players ships to NULL and game_state to PLAYING
void game_init(Game* game);
// frees all ships
void game_free(Game* game);

// returns player ship array
Ship** game_get_player_ships(Game* game, Player player);
// checks if ship exists on top of any artifact or outside of map
int game_is_valid_ship(Game* game, Ship* ship, Player player);

// initializes players ships through console
void game_player_init_manual(Game* game, Player player);
// initializes players ships in random positions
void game_player_init_random(Game* game, Player player);

// gets player shoot from console and updates game state
void game_player_shoot(Game* game, Player player);

// this way we only need one syscall to print the player
void game_player_to_string(Game* game, Player player, char* str);
void game_player_print(Game* game, Player player);
void game_player_print_hits(Game* game, Player player);
void game_print(Game* game);

#endif
