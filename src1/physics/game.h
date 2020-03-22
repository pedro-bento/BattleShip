#ifndef GAME_H
#define GAME_H

#include <stdint.h>

#include "player.h"

typedef struct
{
  uint8_t map_size;
  uint8_t num_of_ships;
  Player player1;
  Player player2;
} Game;

Ship* game_player_get_next_ship(Game* game, int player_id);
Player* game_get_player_by_id(Game* game, int player_id);

#endif // GAME_H
