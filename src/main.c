#include <stdio.h>
#include <unistd.h>

#include "game.h"

/*
  Functions, conventions:

    To allocate object in heap (by default initializes)
      Type* type_alloc(...)

    To free object from heap or objects inside it
      void type_free(Type* obj)

    To initialize object
      void type_init(Type* obj)
*/

int main(int argc, char* const argv[])
{
  Game game;
  game_init(&game);

  game_player_init_manual(&game, PLAYER1);
  game_player_init_random(&game, PLAYER2);

  while(game.state == PLAYING)
  {
    game_player_shoot(&game, PLAYER1);
    game_player_shoot(&game, PLAYER2);
  }

  game_print(&game);

  if(game.state == PLAYER1_WIN)
    printf("\nPLAYER 1 WON!\n");
  else
    printf("\nPLAYER 2 WON!\n");

  game_free(&game);

  return 0;
}
