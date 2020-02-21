#include <stdio.h>
#include <unistd.h>

#include "world/world.h"

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
  int isRandom = 1;
  int opt;
  while((opt = getopt(argc, argv, ":m:r")) != -1)
  {
    switch(opt)
    {
      case 'm': isRandom = 0; break;
      case 'r': isRandom = 1; break;
    }
  }

  World world;
  world_init(&world);

  if(isRandom)
    world_player_place_ships_random(&world, PLAYER1);
  else
    world_player_place_ships(&world, PLAYER1);
  world_player_place_ships_random(&world, PLAYER2);

  while(world.game_state == PLAYING)
  {
    world_player_shoot(&world, PLAYER1);
    world_player_shoot(&world, PLAYER2);
  }

  world_print(&world);

  if(world.game_state == PLAYER1_WIN)
    printf("\nPLAYER 1 WON!\n");
  else
    printf("\nPLAYER 2 WON!\n");

  world_free(&world);

  return 0;
}
