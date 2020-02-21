#ifndef BOAT_H
#define BOAT_H

#include <stdlib.h>

#include "../math/vec2.h"
#include "../math/math.h"

#define STATE_GOOD  'O'
#define STATE_HIT   '@'

typedef struct
{
  Vec2 front;
  Vec2 back;
  char* states;
} Ship;

// default values:
//  front:  (0,0)
//  back:   (length - 1, 0)
//  states: STATE_GOOD
Ship* ship_alloc(size_t length);
void ship_free(Ship* ship);

// returns 1 if all states are STATE_HIT, otherwise 0
int ship_is_over(Ship* ship);
// returns a (char) STATE if contains the point, otherwise '\0'
char ship_contains(Ship* ship, Vec2 point);
// register and returns 1 if hit, otherwise 0
int ship_reg(Ship* ship, Vec2 point);
// returns 1 if ships intersect, otherwise 0
int ship_intersect(Ship* ship1, Ship* ship2);
// moves front and back of the ship
void ship_move(Ship* ship, Vec2 pos);
// rotates ship's back point counterclockwise
void ship_rotate_counterclockwise(Ship* ship);
// rotates ship's back point clockwise
void ship_rotate_clockwise(Ship* ship);

#endif // BOAT_H
