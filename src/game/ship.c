#include "ship.h"
#include "../system/stacktrace.h"

#include <stdlib.h>

Ship* ship_create(ShipType type, size_t length)
{
  Ship* ship = malloc(sizeof(Ship));
  trace_assert(ship);

  switch(type)
  {
   case I : {
     size_t len = length > 0 ? length : 4;
     ship->line1 = ship_line_create(len);
     ship->line2 = ship_line_create(len);
   } break;

   default : return NULL;
  }

  return ship;
}

void ship_destroy(Ship* ship)
{
  ship_line_destroy(ship->line1);
  ship_line_destroy(ship->line2);
  free(ship);
}

int ship_is_over(Ship* ship)
{
  return ship_line_is_over(ship->line1) && ship_line_is_over(ship->line2);
}

ShipState ship_contains(Ship* ship, Vec2 point)
{
  ShipState state = ship_line_contains(ship->line1, point);
  if(state != EMPTY) return state;
  state = ship_line_contains(ship->line2, point);
  return state;
}

int ship_register_hit(Ship* ship, Vec2 point)
{
  int hit1 = ship_line_register_hit(ship->line1, point);
  int hit2 = ship_line_register_hit(ship->line2, point);
  return hit1 || hit2;
}

int ship_intersect(Ship* ship1, Ship* ship2)
{
    return ship_line_intersect(ship1->line1, ship2->line1) ||
           ship_line_intersect(ship1->line1, ship2->line2) ||
           ship_line_intersect(ship1->line2, ship2->line1) ||
           ship_line_intersect(ship1->line2, ship2->line2);
}

void ship_move(Ship* ship, Vec2 dxy)
{
  ship_line_move(ship->line1, dxy);
  ship_line_move(ship->line2, dxy);
}

void ship_rotate_counterclockwise(Ship* ship)
{
  Vec2 pivot = ship->line1->front;
  ship_line_rotate_counterclockwise_pivot(ship->line1, pivot);
  ship_line_rotate_counterclockwise_pivot(ship->line2, pivot);
}

void ship_rotate_clockwise(Ship* ship)
{
  Vec2 pivot = ship->line1->front;
  ship_line_rotate_clockwise_pivot(ship->line1, pivot);
  ship_line_rotate_clockwise_pivot(ship->line2, pivot);
}
