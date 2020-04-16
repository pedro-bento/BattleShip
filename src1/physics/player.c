#include "player.h"
#include "../system/log.h"

Player* new_player(size_t map_size)
{
  Player* player = (Player*)calloc(1, sizeof(Player));
  LOG_FAIL(player);

  player->map = calloc(map_size, sizeof(Cell*));
  LOG_FAIL(player->map);

  for(size_t i = 0; i < map_size; i++)
  {
    player->map[i] = calloc(map_size, sizeof(Cell));
    LOG_FAIL(player->map[i]);
  }

  for(size_t x = 0; x < map_size; x++)
    for(size_t y = 0; y < map_size; y++)
      player->map[x][y].ship = NULL;

  return player;
}

ShipState player_get_ship_state(Player* player, Vec2i pos)
{
  Ship* ship = player->map[pos.x][pos.y].ship;
  if(ship == NULL) return SHIP_STATE_EMPTY;
  return ship->bitmap.states[pos.x - ship->top_left.x][pos.y - ship->top_left.y];
}
