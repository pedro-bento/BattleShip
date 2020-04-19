#include "game.h"
#include "../system/log.h"

Game* new_game(Settings* settings)
{
  Game* game = malloc(sizeof(Game));
  LOG_FAIL(game);
  game->settings = settings;
  game->player1 = new_player(settings->MAP_SIZE);
  game->player2 = new_player(settings->MAP_SIZE);
  return game;
}

Player* game_get_player_by_id(Game* game, PlayerID id)
{
  if(id == 1)
    return game->player1;
  return game->player2;
}

bool game_is_valid_ship(Game* game, Ship* ship, PlayerID id, bool ignore_ships)
{
  Player* player = game_get_player_by_id(game, id);
  for(int x = 0; x < MAX_SHIP_WIDTH; ++x)
  {
    for(int y = 0; y < MAX_SHIP_WIDTH; ++y)
    {
      // ship is invalid when a cell exists outside of the map or when overlaps other ships
      ShipState ship_state = ship->bitmap.states[x][y];
      int real_x = x + ship->top_left.x;
      int real_y = y + ship->top_left.y;
      if(ship_state == SHIP_STATE_GOOD || ship_state == SHIP_STATE_HIT)
      {
        if(real_x < 0 || real_y < 0 || real_x >= game->settings->MAP_SIZE || real_y >= game->settings->MAP_SIZE)
          return false;
        if(!ignore_ships)
        {
          ShipState player_ship_state = player_get_ship_state(player, vec2i(real_x, real_y));
          if(player_ship_state == SHIP_STATE_GOOD || player_ship_state == SHIP_STATE_HIT)
            return false;
        }
      }
    }
  }
  return true;
}

bool game_player_place_ship(Game* game, Ship* ship, PlayerID id)
{
  if(!game_is_valid_ship(game, ship, id, false))
    return false;

  Player* player = game_get_player_by_id(game, id);
  for(int x = ship->top_left.x; x < ship->bottom_right.x; ++x)
  {
    for(int y = ship->top_left.y; y < ship->bottom_right.y; ++y)
    {
      // this can overwrite bitmaps, but that's okay because it will never have
      // overlapping ship cells due to the 'game_is_valid_ship' check
      if(x >= 0 && y >= 0 && x < game->settings->MAP_SIZE && y < game->settings->MAP_SIZE)
        player->map[x][y].ship = ship;
    }
  }

  return true;
}

void game_player_shoot(Game* game, Vec2i shot, PlayerID id)
{
  Player* opponent = game_get_player_by_id(game, flip_player_id(id));
  ShotState shot_state = player_register_shot(opponent, shot);

  Player* player = game_get_player_by_id(game, id);
  player->map[shot.x][shot.y].shot_state = shot_state;
}
