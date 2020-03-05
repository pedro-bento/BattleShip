#include <stdio.h>
#include "ship.h"
#include "../system/stacktrace.h"

ShipLine* ship_create(size_t length)
{
  ShipLine* ship = malloc(sizeof(ShipLine));
  ship->front = vec2(0, 0);
  ship->back = vec2(length - 1, 0);
  ship->states = malloc(length * sizeof(char));
  trace_assert(ship->states);
  for(size_t i = 0; i < length; ++i)
    ship->states[i] = GOOD;
  return ship;
}

void ship_destroy(ShipLine* ship)
{
  free(ship->states);
  free(ship);
}

int ship_is_over(ShipLine* ship)
{
  int lower_x = MIN(ship->front.x, ship->back.x);
  int upper_x = MAX(ship->front.x, ship->back.x);
  int lower_y = MIN(ship->front.y, ship->back.y);
  int upper_y = MAX(ship->front.y, ship->back.y);

  size_t length = upper_x - lower_x + upper_y - lower_y + 1;
  for(size_t i = 0; i < length; ++i)
    if(ship->states[i] == GOOD)
      return 0;
  return 1;
}

ShipState ship_contains(ShipLine* ship, Vec2 point)
{
  int lower_x = MIN(ship->front.x, ship->back.x);
  int upper_x = MAX(ship->front.x, ship->back.x);
  int lower_y = MIN(ship->front.y, ship->back.y);
  int upper_y = MAX(ship->front.y, ship->back.y);

  if(point.x >= lower_x && point.x <= upper_x && point.y >= lower_y && point.y <= upper_y)
  {
    if(lower_x == upper_x) return ship->states[point.y - lower_y];
    else return ship->states[point.x - lower_x];
  }

  return EMPTY;
}

int ship_register_hit(ShipLine* ship, Vec2 point)
{
  int lower_x = MIN(ship->front.x, ship->back.x);
  int upper_x = MAX(ship->front.x, ship->back.x);
  int lower_y = MIN(ship->front.y, ship->back.y);
  int upper_y = MAX(ship->front.y, ship->back.y);

  if(point.x >= lower_x && point.x <= upper_x && point.y >= lower_y && point.y <= upper_y){
    if(lower_x == upper_x){
      if(ship->states[point.y - lower_y] == GOOD){
        ship->states[point.y - lower_y] = HIT;
        return 1;
      }
    }else{
      if(ship->states[point.x - lower_x] == GOOD){
        ship->states[point.x - lower_x] = HIT;
        return 1;
      }
    }
  }

  return 0;
}

int ship_intersect(ShipLine* ship1, ShipLine* ship2)
{
  Vec2 p1 = vec2(MIN(ship1->front.x, ship1->back.x), MIN(ship1->front.y, ship1->back.y));
  Vec2 p2 = vec2(MAX(ship1->front.x, ship1->back.x), MAX(ship1->front.y, ship1->back.y));

  Vec2 q1 = vec2(MIN(ship2->front.x, ship2->back.x), MIN(ship2->front.y, ship2->back.y));
  Vec2 q2 = vec2(MAX(ship2->front.x, ship2->back.x), MAX(ship2->front.y, ship2->back.y));

  return (p1.y >= q1.y && p1.y <= q2.y && p1.x <= q1.x && p2.x >= q1.x) ||
         (p1.y <= q1.y && p2.y >= q1.y && p1.x >= q1.x && p1.x <= q2.x);
}

void ship_move(ShipLine* ship, Vec2 pos)
{
  ship->back.x += pos.x - ship->front.x;
  ship->back.y += pos.y - ship->front.y;
  ship->front = pos;
}

// sg can be 1 for a 90º counterclockwise rotation, otherwise -1
void ship_rotate90(ShipLine* ship, float sg)
{
  ship->back.x -= ship->front.x;
  ship->back.y -= ship->front.y;

  int nx = ship->back.y * sg;
  int ny = ship->back.x * -sg;

  ship->back.x = nx + ship->front.x;
  ship->back.y = ny + ship->front.y;
}

void ship_rotate_counterclockwise(ShipLine* ship)
{
  ship_rotate90(ship, -1);
}

void ship_rotate_clockwise(ShipLine* ship)
{
  ship_rotate90(ship, 1);
}
