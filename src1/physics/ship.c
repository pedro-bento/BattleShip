#include "ship.h"

#include <stdlib.h>

void ship_rotate_90(Ship* ship, bool is_clockwise)
{
  ShipState new_states[MAX_SHIP_WIDTH][MAX_SHIP_WIDTH];
  Vec2i new_pos;
  int16_t m = MAX_SHIP_WIDTH / 2;

  for(size_t x = 0; x < MAX_SHIP_WIDTH; ++x)
  {
    for(size_t y = 0; y < MAX_SHIP_WIDTH; ++y)
    {
      new_pos = vec2i_rotate_90(vec2i(x-m, y-m), is_clockwise);
      new_states[new_pos.x + m][new_pos.y + m] = ship->states[x][y];
    }
  }

  for(size_t x = 0; x < MAX_SHIP_WIDTH; ++x)
  {
    for(size_t y = 0; y < MAX_SHIP_WIDTH; ++y)
    {
      ship->states[x][y] = new_states[x][y];
    }
  }
}
