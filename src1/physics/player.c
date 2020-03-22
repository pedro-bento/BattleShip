#include "player.h"

Ship* player_get_next_ship(Player* player)
{
  player->ships[player->ships_count] = (Ship)
  {
    .top_left     = vec2i(0,0),
    .bottom_right = vec2i(4,4),
    .shot_count   = 0,
    .states       =
    {
      {0, 1, 1, 1, 0},
      {0, 1, 1, 1, 0},
      {0, 1, 1, 1, 0},
      {0, 1, 1, 1, 0},
      {0, 1, 1, 1, 0},
    },
  };

  return &player->ships[player->ships_count++];
}
