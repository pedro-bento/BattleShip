#ifndef WORLD_H
#define WORLD_H

#include "ship.h"
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
} Player;

typedef struct
{
  Ship* player1[NUM_OF_SHIPS];
  Ship* player2[NUM_OF_SHIPS];
  Game_State state;
  Player current_player;
} Game;

// initializes players ships to NULL, game_state to PLAYING and current_player to PLAYER1
void game_init(Game* game);
// frees all ships
void game_free(Game* game);

// swaps current_player player
void game_swap_current_player(Game* game);
// returns player ship array
Ship** game_get_player_ships(Game* game, Player player);
// checks if ship exists on top of any artifact or outside of map
int game_is_valid_ship(Game* game, Ship* ship);
// initializes players ships in random positions
void game_player_init_random(Game* game);
// returns a random valid ship;
Ship* game_create_random_ship(Game* game, int length);
// adds ship to current_player at position id
int game_player_add_ship(Game* game, Ship* ship, size_t id);
void game_player_shoot_gui(Game* game, Vec2 shot);
// return state of cell with position pos from defined player
char game_player_get_cell(Game* game, Player player, Vec2 pos);

// No Longer used, maybe delete in the future

// gets player shoot from console and updates game state
void game_player_shoot_console(Game* game);

// initializes players ships through console
void game_player_init_manual_console(Game* game);

// this way we only need one syscall to print the player
void game_player_to_string(Game* game, Player player, char* str);
void game_player_print(Game* game, Player player);
void game_player_print_hits(Game* game, Player player);
void game_print(Game* game);

#endif
