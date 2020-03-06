#ifndef SHIP_H
#define SHIP_H

#include "ship_line.h"
#include "../math/vec2.h"

// Shapes based on tetris
// For classic BattleShip mode we just use 'I' with variable length
typedef enum
{
 // ####
 I,

 // #
 // ###
 J,

 //   #
 // ###
 L,

 // ##
 // ##
 O,

 //  ##
 // ##
 S,

 //  #
 // ###
 T,

 // ##
 //  ##
 Z,
} ShipType;

// Ship of any complex shape that can be formed by 2 lines
typedef struct
{
 ShipLine* line1;
 ShipLine* line2;
} Ship;

// default values:
// When type is 'I' and size is declared
//  front:  (0,0)
//  back:   (length - 1, 0)
//  states: GOOD
// Otherwise
//  position: upper left conner
//  states: GOOD
Ship* ship_create(ShipType type, size_t length);
void ship_destroy(Ship* ship);

// returns 1 if all states are HIT, otherwise 0
int ship_is_over(Ship* ship);
// returns a (char) GOOD or HIT if contains the point, otherwise NULL
ShipState ship_contains(Ship* ship, Vec2 point);
// register and returns 1 if hit, otherwise 0
int ship_register_hit(Ship* ship, Vec2 point);
// returns 1 if ships intersect, otherwise 0
int ship_intersect(Ship* ship1, Ship* ship2);
// moves the ship
void ship_move(Ship* ship, Vec2 dxy);
// rotates ship where front is the pivot counterclockwise
void ship_rotate_counterclockwise(Ship* ship);
// rotates ship where front is the pivot clockwise
void ship_rotate_clockwise(Ship* ship);

#endif // SHIP_H
