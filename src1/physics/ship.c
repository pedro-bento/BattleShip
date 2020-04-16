#include "ship.h"

#include <stdlib.h>
#include "../system/log.h"

Ship* new_ship(ShipType type)
{
  Ship* ship = (Ship*)malloc(sizeof(Ship));
  LOG_FAIL(ship);

  switch(type)
  {
    case F :{
      ship->top_left     = vec2i(0,0),
      ship->bottom_right = vec2i(4,4),
      ship->hp           = 5,
      ship->bitmap       = (Bitmap){
        .states = {
          {0, 0, 0, 0, 0},
          {0, 0, 1, 1, 0},
          {0, 1, 1, 0, 0},
          {0, 0, 1, 0, 0},
          {0, 0, 0, 0, 0},
        }
      };
    } break;

    case I :{
      ship->top_left     = vec2i(0,0),
      ship->bottom_right = vec2i(4,4),
      ship->hp           = 5,
      ship->bitmap       = (Bitmap){
        .states = {
          {0, 0, 1, 0, 0},
          {0, 0, 1, 0, 0},
          {0, 0, 1, 0, 0},
          {0, 0, 1, 0, 0},
          {0, 0, 1, 0, 0},
        }
      };
    } break;

    case L :{
      ship->top_left     = vec2i(0,0),
      ship->bottom_right = vec2i(4,4),
      ship->hp           = 5,
      ship->bitmap       = (Bitmap){
        .states = {
          {0, 0, 1, 0, 0},
          {0, 0, 1, 0, 0},
          {0, 0, 1, 0, 0},
          {0, 0, 1, 1, 0},
          {0, 0, 0, 0, 0},
        }
      };
    } break;

    case N :{
      ship->top_left     = vec2i(0,0),
      ship->bottom_right = vec2i(4,4),
      ship->hp           = 5,
      ship->bitmap       = (Bitmap){
        .states = {
          {0, 0, 0, 0, 1},
          {0, 1, 0, 1, 0},
          {1, 0, 1, 0, 0},
          {0, 0, 0, 0, 0},
          {0, 0, 0, 0, 0},
        }
      };
    } break;

    case P :{
      ship->top_left     = vec2i(0,0),
      ship->bottom_right = vec2i(4,4),
      ship->hp           = 5,
      ship->bitmap       = (Bitmap){
        .states = {
          {0, 0, 0, 0, 0},
          {0, 0, 1, 1, 0},
          {0, 0, 1, 1, 0},
          {0, 0, 1, 0, 0},
          {0, 0, 0, 0, 0},
        }
      };
    } break;

    case T :{
      ship->top_left     = vec2i(0,0),
      ship->bottom_right = vec2i(4,4),
      ship->hp           = 5,
      ship->bitmap       = (Bitmap){
        .states = {
          {0, 0, 0, 0, 0},
          {0, 1, 1, 1, 0},
          {0, 0, 1, 0, 0},
          {0, 0, 1, 0, 0},
          {0, 0, 0, 0, 0},
        }
      };
    } break;

    case U :{
      ship->top_left     = vec2i(0,0),
      ship->bottom_right = vec2i(4,4),
      ship->hp           = 5,
      ship->bitmap       = (Bitmap){
        .states = {
          {0, 0, 0, 0, 0},
          {0, 1, 0, 1, 0},
          {0, 1, 1, 1, 0},
          {0, 0, 0, 0, 0},
          {0, 0, 0, 0, 0},
        }
      };
    } break;

    case V :{
      ship->top_left     = vec2i(0,0),
      ship->bottom_right = vec2i(4,4),
      ship->hp           = 5,
      ship->bitmap       = (Bitmap){
        .states = {
          {1, 0, 0, 0, 1},
          {0, 1, 0, 1, 0},
          {0, 0, 1, 0, 0},
          {0, 0, 0, 0, 0},
          {0, 0, 0, 0, 0},
        }
      };
    } break;

    case W :{
      ship->top_left     = vec2i(0,0),
      ship->bottom_right = vec2i(4,4),
      ship->hp           = 5,
      ship->bitmap       = (Bitmap){
        .states = {
          {0, 0, 0, 0, 0},
          {0, 0, 0, 0, 0},
          {1, 0, 1, 0, 1},
          {0, 1, 0, 1, 0},
          {0, 0, 0, 0, 0},
        }
      };
    } break;

    case X :{
      ship->top_left     = vec2i(0,0),
      ship->bottom_right = vec2i(4,4),
      ship->hp           = 5,
      ship->bitmap       = (Bitmap){
        .states = {
          {0, 0, 0, 0, 0},
          {0, 1, 0, 1, 0},
          {0, 0, 1, 0, 0},
          {0, 1, 0, 1, 0},
          {0, 0, 0, 0, 0},
        }
      };
    } break;

    case Y :{
      ship->top_left     = vec2i(0,0),
      ship->bottom_right = vec2i(4,4),
      ship->hp           = 5,
      ship->bitmap       = (Bitmap){
        .states = {
          {0, 0, 0, 0, 0},
          {0, 1, 0, 1, 0},
          {0, 0, 1, 0, 0},
          {0, 1, 0, 0, 0},
          {1, 0, 0, 0, 0},
        }
      };
    } break;

    case Z :{
      ship->top_left     = vec2i(0,0),
      ship->bottom_right = vec2i(4,4),
      ship->hp           = 5,
      ship->bitmap       = (Bitmap){
        .states = {
          {0, 0, 0, 0, 0},
          {0, 1, 1, 0, 0},
          {0, 0, 1, 0, 0},
          {0, 0, 1, 1, 0},
          {0, 0, 0, 0, 0},
        }
      };
    } break;
  }

  return ship;
}

void  delete_ship(Ship* ship)
{
  free(ship);
}

void ship_move(Ship* ship, Vec2i dxy)
{
  ship->top_left     = vec2i_add(ship->top_left, dxy);
  ship->bottom_right = vec2i_add(ship->bottom_right, dxy);
}

void ship_rotate(Ship* ship, bool is_clockwise)
{
  ShipState new_states[MAX_SHIP_WIDTH][MAX_SHIP_WIDTH];
  Vec2i new_pos;

  const int16_t m = MAX_SHIP_WIDTH / 2;
  const int16_t dir = is_clockwise ? 1 : -1;

  for(size_t x = 0; x < MAX_SHIP_WIDTH; ++x)
  {
    for(size_t y = 0; y < MAX_SHIP_WIDTH; ++y)
    {
      new_pos = vec2i((y-m) * dir, (x-m) * -dir); // rotate 90º
      new_states[new_pos.x + m][new_pos.y + m] = ship->bitmap.states[x][y];
    }
  }

  for(size_t x = 0; x < MAX_SHIP_WIDTH; ++x)
  {
    for(size_t y = 0; y < MAX_SHIP_WIDTH; ++y)
    {
      ship->bitmap.states[x][y] = new_states[x][y];
    }
  }
}
