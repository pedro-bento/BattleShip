#include "game.h"

Ship* game_player_get_next_ship(Game* game, int player_id)
{
  switch(player_id)
  {
    case 1  : return player_get_next_ship(&game->player1);
    case 2  : return player_get_next_ship(&game->player2);
    default : return (void*)0;
  }
}

Player* game_get_player_by_id(Game* game, int player_id)
{
  switch(player_id)
  {
    case 1  : return &game->player1;
    case 2  : return &game->player2;
    default : return (void*)0;
  }
}
