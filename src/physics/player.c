#include "player.h"
#include "../system/log.h"

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

bool not_deleted(Ship* ship, Ship* deleted[], int deleted_count)
{
  for(int i = 0; i < deleted_count; ++i)
    if(deleted[i] == ship)
      return false;
  return true;
}

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

ShipState player_get_ship_state(Player* player, Vec2i pos)
{
  QT_Node* node = qt_find(player->map, pos);
  if(node == NULL) return SHIP_STATE_EMPTY;
  Cell* cell = (Cell*)node->data;
  if(cell->ship == NULL) return SHIP_STATE_EMPTY;
  Ship* ship = cell->ship;
  return ship->bitmap.states[pos.x - ship->top_left.x][pos.y - ship->top_left.y];
}

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
