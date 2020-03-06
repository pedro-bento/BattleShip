#ifndef SHIP_LINE_H
#define SHIP_LINE_H

#include <stdlib.h>

#include "../math/vec2.h"
#include "../math/math.h"

typedef enum
{
  GOOD,
  HIT,
  EMPTY,
} ShipState;

// a ship with the shape of a line
typedef struct
{
  Vec2 front;
  Vec2 back;
  ShipState* states;
} ShipLine;

// default values:
//  front:  (0,0)
//  back:   (length - 1, 0)
//  states: GOOD
ShipLine* ship_line_create(size_t length);
void ship_line_destroy(ShipLine* ship);

// returns 1 if all states are HIT, otherwise 0
int ship_line_is_over(ShipLine* ship);
// returns a (char) GOOD or HIT if contains the point, otherwise NULL
ShipState ship_line_contains(ShipLine* ship, Vec2 point);
// register and returns 1 if hit, otherwise 0
int ship_line_register_hit(ShipLine* ship, Vec2 point);
// returns 1 if ships intersect, otherwise 0
int ship_line_intersect(ShipLine* ship1, ShipLine* ship2);
// moves front and back of the ship
void ship_line_move(ShipLine* ship, Vec2 dxy);
// rotates ship's back point counterclockwise
void ship_line_rotate_counterclockwise(ShipLine* ship);
// rotates ship's back point clockwise
void ship_line_rotate_clockwise(ShipLine* ship);
// rotates ship based on pivot counterclockwise
void ship_line_rotate_counterclockwise_pivot(ShipLine* ship, Vec2 pivot);
// rotates ship based on pivot clockwise
void ship_line_rotate_clockwise_pivot(ShipLine* ship, Vec2 pivot);


#endif // SHIP_LINE_H