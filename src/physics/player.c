#include "player.h"
#include "../system/log.h"

#ifdef A

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

#else

Cell* new_cell()
{
  Cell* cell = (Cell*)calloc(1, sizeof(Cell));
  LOG_FAIL(cell);

  cell->ship = NULL;
  cell->shot_state = SHOT_STATE_NONE;

  return cell;
}

void delete_cell(Cell* cell)
{
  free(cell);
}

Player* new_player(size_t map_size)
{
  Player* player = (Player*)calloc(1, sizeof(Player));
  LOG_FAIL(player);

  player->hp = 0;
  player->map = qt_create(vec2i(0, 0), vec2i(map_size, map_size));

  return player;
}

#endif

bool not_deleted(Ship* ship, Ship* deleted[], int deleted_count)
{
  for(int i = 0; i < deleted_count; ++i)
    if(deleted[i] == ship)
      return false;
  return true;
}

#ifdef A

void delete_player(Player* player, size_t map_size)
{
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

  for(size_t i = 0; i < map_size; i++)
    free(player->map[i]);

  free(player->map);

  free(player);
}

#else

void delete_ships_and_cells(QT* map, Ship* deleted[], int deleted_count)
{
  if(map->node == NULL) return;

  Cell* cell = (Cell*)map->node->data;
  if(cell->ship != NULL && not_deleted(cell->ship, deleted, deleted_count))
  {
    deleted[deleted_count] = cell->ship;
    deleted_count++;
    delete_ship(cell->ship);
  }

  delete_ships_and_cells(map->t_left, deleted, deleted_count);
  delete_ships_and_cells(map->t_right, deleted, deleted_count);
  delete_ships_and_cells(map->b_left, deleted, deleted_count);
  delete_ships_and_cells(map->b_right, deleted, deleted_count);
}

void delete_player(Player* player, size_t map_size)
{
  // free ships
  Ship* deleted[(map_size * map_size) / (MAX_SHIP_WIDTH * MAX_SHIP_WIDTH)];
  int deleted_count = 0;

  delete_ships_and_cells(player->map, deleted, deleted_count);

  qt_destroy(player->map);
  free(player);
}

#endif

#ifdef A

ShipState player_get_ship_state(Player* player, Vec2i pos)
{
  Ship* ship = player->map[pos.x][pos.y].ship;
  if(ship == NULL) return SHIP_STATE_EMPTY;
  return ship->bitmap.states[pos.x - ship->top_left.x][pos.y - ship->top_left.y];
}

#else

ShipState player_get_ship_state(Player* player, Vec2i pos)
{
  QT_Node* node = qt_find(player->map, pos);
  if(node == NULL) return SHIP_STATE_EMPTY;
  Cell* cell = (Cell*)node->data;
  if(cell->ship == NULL) return SHIP_STATE_EMPTY;
  Ship* ship = cell->ship;
  return ship->bitmap.states[pos.x - ship->top_left.x][pos.y - ship->top_left.y];
}

#endif

#ifdef A

ShotState player_register_shot(Player* player, Vec2i pos)
{
  Ship* ship = player->map[pos.x][pos.y].ship;
  if(ship == NULL) return SHOT_STATE_MISS;

  ShipState state = ship->bitmap.states[pos.x - ship->top_left.x][pos.y - ship->top_left.y];
  if(state == SHIP_STATE_EMPTY || state == SHIP_STATE_MISS)
  {
    ship->bitmap.states[pos.x - ship->top_left.x][pos.y - ship->top_left.y] = SHIP_STATE_MISS;
    return SHOT_STATE_MISS;
  }

  if(state == SHIP_STATE_GOOD) player->hp--;
  ship->bitmap.states[pos.x - ship->top_left.x][pos.y - ship->top_left.y] = SHIP_STATE_HIT;
  return SHOT_STATE_HIT;
}

#else

ShotState player_register_shot(Player* player, Vec2i pos)
{
  QT_Node* node = qt_find(player->map, pos);
  if(node == NULL) return SHOT_STATE_MISS;
  Cell* cell = (Cell*)node->data;
  if(cell->ship == NULL) return SHOT_STATE_MISS;
  Ship* ship = cell->ship;

  ShipState state = ship->bitmap.states[pos.x - ship->top_left.x][pos.y - ship->top_left.y];
  if(state == SHIP_STATE_EMPTY || state == SHIP_STATE_MISS)
  {
    ship->bitmap.states[pos.x - ship->top_left.x][pos.y - ship->top_left.y] = SHIP_STATE_MISS;
    return SHOT_STATE_MISS;
  }

  if(state == SHIP_STATE_GOOD) player->hp--;
  ship->bitmap.states[pos.x - ship->top_left.x][pos.y - ship->top_left.y] = SHIP_STATE_HIT;
  return SHOT_STATE_HIT;
}

#endif
