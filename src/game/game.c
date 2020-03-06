#include "game.h"

#include <stdio.h>

#include "../math/vec2.h"

void game_init_empty(Game* game)
{
  player_init_empty(&game->player1);
  player_init_empty(&game->player2);
  game->state = PLAYING;
}

void game_free(Game* game)
{
  player_free(&game->player1);
  player_free(&game->player2);
}

Ship* game_create_random_ship(Game* game, GamePlayer player, ShipType type, int ship_length)
{
  if(player == PLAYER1)
    return player_create_random_ship(&game->player1, type, ship_length);
  return player_create_random_ship(&game->player2, type, ship_length);
}

int game_player_place_ship(Game* game, GamePlayer player, Ship* ship)
{
  if(player == PLAYER1)
    return player_add_ship(&game->player1, ship);
  return player_add_ship(&game->player2, ship);
}

void game_player_shoot(Game* game, GamePlayer player, Vec2 pos)
{
  if(player == PLAYER1)
  {
    if(player_register_hit(&game->player2, pos))
      if(player_is_over(&game->player2))
        game->state = PLAYER1_WIN;
  }

  else
  {
    if(player_register_hit(&game->player1, pos))
      if(player_is_over(&game->player1))
        game->state = PLAYER2_WIN;
  }
}

char game_player_get_map_state(Game* game, GamePlayer player, Vec2 pos)
{
  if(player == PLAYER1)
    return player_get_map_state(&(game->player1), pos);
  return player_get_map_state(&(game->player2), pos);
}
