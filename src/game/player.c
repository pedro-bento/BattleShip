#include "player.h"

// returns the first ships index that is NULL, -1 if none
// maybe store curr_index in variable to have O(1) complexity?
int player_get_ships_index(Player* player);

void player_init_empty(Player* player)
{
  for(size_t i = 0; i < NUM_OF_SHIPS; i++)
    player->ships[i] = NULL;
  player->map = qt_create(vec2(0,0), vec2(MAP_LENGTH, MAP_LENGTH));
}

void player_init_random(Player* player)
{
  const int ship_length[5] = {5, 4, 3, 3, 2};
  for(size_t i = 0; i < NUM_OF_SHIPS; i++)
    player_add_ship(player, player_create_random_ship(player, ship_length[i % 5]));
}

void player_free(Player* player)
{
  for(size_t i = 0; i < NUM_OF_SHIPS; i++)
    if(player->ships[i] != NULL)
      ship_destroy(player->ships[i]);
  qt_destroy(player->map);
}

int player_is_valid_ship(Player* player, Ship* ship)
{
  Vec2 p1 = ship->line1->front;
  Vec2 p2 = ship->line1->back;

  // checks if it is inside the map boundary
  if(p1.x < 0 || p1.x >= MAP_LENGTH || p1.y < 0 || p1.y >= MAP_LENGTH ||
     p2.x < 0 || p2.x >= MAP_LENGTH || p2.y < 0 || p2.y >= MAP_LENGTH)
       return 0;

  p1 = ship->line2->front;
  p2 = ship->line2->back;

  // checks if it is inside the map boundary
  if(p1.x < 0 || p1.x >= MAP_LENGTH || p1.y < 0 || p1.y >= MAP_LENGTH ||
     p2.x < 0 || p2.x >= MAP_LENGTH || p2.y < 0 || p2.y >= MAP_LENGTH)
     return 0;

  // checks if intersects other ships
  for(size_t i = 0; i < NUM_OF_SHIPS; ++i)
    if(player->ships[i] != NULL)
      if(ship_intersect(ship, player->ships[i]))
        return 0;

  return 1;
}

Ship* player_create_random_ship(Player* player, int ship_length)
{
  Vec2 dxy;
  Ship* ship = ship_create(Z, ship_length);
  do{
    dxy = sub(vec2(rdn_range(0, MAP_LENGTH-1), rdn_range(0, MAP_LENGTH-1)),
              ship->line1->front);
    ship_move(ship, dxy);
    size_t num_rots = rdn_range(0, 4);
    for(size_t i = 0; i < num_rots; ++i)
      ship_rotate_counterclockwise(ship);
  }while(!player_is_valid_ship(player, ship));
  return ship;
}

int player_add_ship(Player* player, Ship* ship)
{
  if(!player_is_valid_ship(player, ship))
    return 0;

  int id;
  if((id = player_get_ships_index(player)) == -1)
    return 0;

  // add to ships array
  player->ships[id] = ship;

  // add to map
  int lower_x = MIN(ship->line1->front.x, ship->line1->back.x);
  int upper_x = MAX(ship->line1->front.x, ship->line1->back.x);
  int lower_y = MIN(ship->line1->front.y, ship->line1->back.y);
  int upper_y = MAX(ship->line1->front.y, ship->line1->back.y);
  for(int x = lower_x; x <= upper_x; ++x)
    for(int y = lower_y; y <= upper_y; ++y)
      qt_insert(player->map, qt_node_create(vec2(x,y), (void*)ship));

  lower_x = MIN(ship->line2->front.x, ship->line2->back.x);
  upper_x = MAX(ship->line2->front.x, ship->line2->back.x);
  lower_y = MIN(ship->line2->front.y, ship->line2->back.y);
  upper_y = MAX(ship->line2->front.y, ship->line2->back.y);
  for(int x = lower_x; x <= upper_x; ++x)
    for(int y = lower_y; y <= upper_y; ++y)
      qt_insert(player->map, qt_node_create(vec2(x,y), (void*)ship));

  return 1;
}

ShipState player_get_map_state(Player* player, Vec2 pos)
{
  QT_Node* node = qt_find(player->map, pos);
  if(node == NULL) return EMPTY;
  return ship_contains((Ship*)(node->data), pos);
}

int player_register_hit(Player* player, Vec2 pos)
{
  QT_Node* node = qt_find(player->map, pos);
  if(node == NULL) return 0;
  return ship_register_hit((Ship*)node->data, pos);
}

int player_is_over(Player* player)
{
  for(size_t i = 0; i < NUM_OF_SHIPS; ++i)
    if(player->ships[i] != NULL)
        if(!ship_is_over(player->ships[i]))
          return 0;
  return 1;
}

int player_get_ships_index(Player* player)
{
  for(int i = 0; i < NUM_OF_SHIPS; i++)
    if(player->ships[i] == NULL)
      return i;
  return -1;
}
