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

void delete_game(Game* game)
{
  delete_player(game->player1, game->settings->MAP_SIZE);
  delete_player(game->player2, game->settings->MAP_SIZE);
  free(game);
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
  for(int x = ship->top_left.x; x <= ship->bottom_right.x; ++x)
  {
    for(int y = ship->top_left.y; y <= ship->bottom_right.y; ++y)
    {
      if(x >= 0 && y >= 0 && x < game->settings->MAP_SIZE && y < game->settings->MAP_SIZE)
      {
        ShipState player_ship_state = player_get_ship_state(player, vec2i(x, y));
        if(!(player_ship_state == SHIP_STATE_GOOD || player_ship_state == SHIP_STATE_HIT))
        {
          QT_Node* node = qt_find(player->map, vec2i(x,y));
          if(node == NULL){
            Cell* cell = new_cell();
            cell->ship = ship;
            qt_insert(player->map, qt_node_create(vec2i(x,y), (void*)cell));
          }else if((Cell*)node->data == NULL){
            Cell* cell = new_cell();
            cell->ship = ship;
            node->data = (void*)cell;
          }else{
            Cell* cell = (Cell*)node->data;
            cell->ship = ship;
            node->data = (void*)cell;
          }
        }
      }
    }
  }

  player->hp += ship->area;

  return true;
}

void game_player_shoot(Game* game, Vec2i shot, PlayerID id)
{
  Player* opponent = game_get_player_by_id(game, flip_player_id(id));
  ShotState shot_state = player_register_shot(opponent, shot);

  Player* player = game_get_player_by_id(game, id);

  QT_Node* node = qt_find(player->map, shot);
  if(node == NULL){
    Cell* cell = new_cell();
    cell->shot_state = shot_state;
    qt_insert(player->map, qt_node_create(shot, (void*)cell));
  }else if((Cell*)node->data == NULL){
    Cell* cell = new_cell();
    cell->shot_state = shot_state;
    node->data = (void*)cell;
  }else{
    Cell* cell = (Cell*)node->data;
    cell->shot_state = shot_state;
    node->data = (void*)cell;
  }
}

bool game_is_over(Game* game)
{
  return game->player1->hp == 0 || game->player2->hp == 0;
}
