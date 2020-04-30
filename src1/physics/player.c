#include "player.h"
#include "../system/log.h"

Player* new_player(size_t map_size)
{
  Player* player = (Player*)calloc(1, sizeof(Player));
  LOG_FAIL(player);

  player->hp = 0;

  player->map = calloc(map_size, sizeof(Cell*));
  LOG_FAIL(player->map);

  for(size_t i = 0; i < map_size; i++)
  {
    player->map[i] = calloc(map_size, sizeof(Cell));
    LOG_FAIL(player->map[i]);
  }

  for(size_t x = 0; x < map_size; x++)
  {
    for(size_t y = 0; y < map_size; y++)
    {
      player->map[x][y].ship = NULL;
      player->map[x][y].shot_state = SHOT_STATE_NONE;
    }
  }

  return player;
}

bool not_deleted(Ship* ship, Ship* deleted[], int deleted_count)
{
  for(int i = 0; i < deleted_count; ++i)
    if(deleted[i] == ship)
      return false;
  return true;
}

void delete_player(Player* player, size_t map_size)
{
  // free ships
  Ship* deleted[(map_size * map_size) / (MAX_SHIP_WIDTH * MAX_SHIP_WIDTH)];
  int deleted_count = 0;

  for(size_t x = 0; x < map_size; x++)
  {
    for(size_t y = 0; y < map_size; y++)
    {
      if(player->map[x][y].ship != NULL)
      {
        if(not_deleted(player->map[x][y].ship, deleted, deleted_count))
        {
          deleted[deleted_count] = player->map[x][y].ship;
          deleted_count++;
          delete_ship(player->map[x][y].ship);
        }
      }
    }
  }

  // free cells
  for(size_t i = 0; i < map_size; i++)
    free(player->map[i]);

  // free map
  free(player->map);

  // free player
  free(player);
}

ShipState player_get_ship_state(Player* player, Vec2i pos)
{
  Ship* ship = player->map[pos.x][pos.y].ship;
  if(ship == NULL) return SHIP_STATE_EMPTY;
  return ship->bitmap.states[pos.x - ship->top_left.x][pos.y - ship->top_left.y];
}

ShotState player_register_shot(Player* player, Vec2i pos)
{
  Ship* ship = player->map[pos.x][pos.y].ship;
  if(ship == NULL) return SHOT_STATE_MISS;

  ShipState state = ship->bitmap.states[pos.x - ship->top_left.x][pos.y - ship->top_left.y];
  if(state == SHIP_STATE_EMPTY || state == SHIP_STATE_MISS){
    ship->bitmap.states[pos.x - ship->top_left.x][pos.y - ship->top_left.y] = SHIP_STATE_MISS;
    return SHOT_STATE_MISS;
  }

  if(state == SHIP_STATE_GOOD) player->hp--;
  ship->bitmap.states[pos.x - ship->top_left.x][pos.y - ship->top_left.y] = SHIP_STATE_HIT;
  return SHOT_STATE_HIT;
}
