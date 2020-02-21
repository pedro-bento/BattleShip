#ifndef WORLD_H
#define WORLD_H

#include "map.h"

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
  Map p1_map;
  Map p2_map;
  char* map_str;
  Game_State game_state;
} World;

// initializes empty maps, allocates map_str and game_state = PLAYING
void world_init(World* w);
void world_free(World* w);

void world_player_place_ships(World* w, Player player);
void world_player_place_ships_random(World* w, Player player);

void world_player_shoot(World* w, Player player);

void world_player_print(World* w, Player player);
void world_print(World* w);

#endif
