#ifndef MAP_H
#define MAP_H

#include "../math/vec2.h"
#include "ship.h"

#define MAP_LENGTH 10
#define NUM_OF_SHIPS 5

typedef struct
{
  Ship* ships[NUM_OF_SHIPS];
} Map;

// initializes all ships to NULL
void map_init(Map* map);
// initializes all ships to a valid ship
void map_init_random(Map* map);
void map_free(Map* map);
// returns ship_state if there is a ship on p, otherwise ' '
char map_get_cell(Map* map, Vec2 p);
// checks if ship exists on top of any artifact or outside of map
int map_is_valid_ship(Map* map, Ship* ship);
// returns 1 if hit, otherwise 0 and register hit
int map_reg_shoot(Map* map, Vec2 shoot);
// returns 1 if all ships are sunk, otherwise 0
int map_is_over(Map* map);
// this way we only need one syscall to print the map
// remember to free map_string with free!
char* map_alloc_string();
void map_to_string(Map* map, char* str);
void map_to_string_just_hit(Map* map, char* str);

#endif // MAP_H
