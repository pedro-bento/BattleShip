#include "map.h"

#include <stdio.h>
#include <stdlib.h>

#include "../math/math.h"

// Probably time can be improved
Ship* map_get_random_ship(Map* map, int length);

void map_init(Map* map)
{
  for(int i = 0; i < NUM_OF_SHIPS; i++)
    map->ships[i] = NULL;
}

void map_init_random(Map* map)
{
  // Acording to BattleShip rules
  // Carrier
  map->ships[0] = map_get_random_ship(map, 5);
  // Battleship
  map->ships[1] = map_get_random_ship(map, 4);
  // Destroyer
  map->ships[2] = map_get_random_ship(map, 3);
  // Submarine
  map->ships[3] = map_get_random_ship(map, 3);
  // Patrol Boat
  map->ships[4] = map_get_random_ship(map, 2);
}

void map_free(Map* map)
{
  for(int i = 0; i < NUM_OF_SHIPS; i++)
    if(map->ships[i] != NULL)
      ship_free(map->ships[i]);
}

char map_get_cell(Map* map, Vec2 p)
{
  char ch;
  for(size_t i = 0; i < NUM_OF_SHIPS; ++i)
    if(map->ships[i] != NULL)
        if((ch = ship_contains(map->ships[i], p)) != '\0')
          return ch;
  return ' ';
}

int map_is_valid_ship(Map* map, Ship* ship)
{
  Vec2 p1 = ship->front;
  Vec2 p2 = ship->back;

  if(p1.x < 0 || p1.x >= MAP_LENGTH || p1.y < 0 || p1.y >= MAP_LENGTH ||
     p2.x < 0 || p2.x >= MAP_LENGTH || p2.y < 0 || p2.y >= MAP_LENGTH)
     return 0;

   for(size_t i = 0; i < NUM_OF_SHIPS; ++i)
     if(map->ships[i] != NULL)
         if(ship_intersect(ship, map->ships[i]))
           return 0;

  return 1;
}

int map_reg_shoot(Map* map, Vec2 shoot)
{
  for(size_t i = 0; i < NUM_OF_SHIPS; ++i)
    if(map->ships[i] != NULL)
        if(ship_reg(map->ships[i], shoot))
          return 1;
  return 0;
}

int map_is_over(Map* map)
{
  for(size_t i = 0; i < NUM_OF_SHIPS; ++i)
    if(map->ships[i] != NULL)
        if(ship_is_over(map->ships[i]) == 0)
          return 0;
  return 1;
}

char* map_alloc_string()
{
  // good aproximation for the number of chars that will be needed
  // 16 + 6x + 2x^2
  const size_t count_aprox = 16 + 6 * MAP_LENGTH + 2 * MAP_LENGTH * MAP_LENGTH;
  char* str = malloc(count_aprox * sizeof(char));
  return str;
}

void map_to_string(Map* map, char* str)
{
  size_t index = 0;
  str[index++] = ' ';
  for(int i = 0; i < MAP_LENGTH; ++i)
  {
    str[index++] = i + '0';
    if(i != MAP_LENGTH - 1) str[index++] = ' ';
  }
  str[index++] = '\n';

  for(int x = 0; x < MAP_LENGTH; ++x)
  {
    str[index++] = x + '0';
    for(int y = 0; y < MAP_LENGTH; ++y)
    {
      str[index++] = map_get_cell(map, vec2(x, y));
      if(y != MAP_LENGTH - 1) str[index++] = ' ';
    }

    str[index++] = '#';
    str[index++] = '\n';
  }

  str[index++] = ' ';
  for(int i = 0; i <= MAP_LENGTH*2-1; ++i)
    str[index++] = '#';
  str[index++] = '\n';
  str[index] = '\0';
}

void map_to_string_just_hit(Map* map, char* str)
{
  size_t index = 0;
  str[index++] = ' ';
  for(int i = 0; i < MAP_LENGTH; ++i)
  {
    str[index++] = i + '0';
    if(i != MAP_LENGTH - 1) str[index++] = ' ';
  }
  str[index++] = '\n';

  for(int x = 0; x < MAP_LENGTH; ++x)
  {
    str[index++] = x + '0';
    for(int y = 0; y < MAP_LENGTH; ++y)
    {
      str[index++] = map_get_cell(map, vec2(x, y)) == STATE_HIT ? STATE_HIT : ' ';
      if(y != MAP_LENGTH - 1) str[index++] = ' ';
    }

    str[index++] = '#';
    str[index++] = '\n';
  }

  str[index++] = ' ';
  for(int i = 0; i <= MAP_LENGTH*2-1; ++i)
    str[index++] = '#';
  str[index++] = '\n';
  str[index] = '\0';
}

Ship* map_get_random_ship(Map* map, int length)
{
  Ship* ship = ship_alloc(length);
  do{
    ship_move(ship, vec2(rdn_range(0, MAP_LENGTH-1), rdn_range(0, MAP_LENGTH-1)));
    size_t num_rots = rdn_range(0, 4);
    for(size_t i = 0; i < num_rots; ++i)
      ship_rotate_counterclockwise(ship);
  }while(!map_is_valid_ship(map, ship));
  return ship;
}
