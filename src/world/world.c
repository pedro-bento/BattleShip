#include "world.h"

#include <stdio.h>

#include "../math/vec2.h"

void world_init(World* w)
{
  map_init(&w->p1_map);
  map_init(&w->p2_map);
  w->map_str = map_alloc_string();
  w->game_state = PLAYING;
}

void world_free(World* w)
{
  map_free(&w->p1_map);
  map_free(&w->p2_map);
  free(w->map_str);
}

void world_place_ship(World* w, Player player, int length, int id)
{
  Vec2 front, orientation;
  char buffer[8];
  Ship* ship = ship_alloc(length);
  Map* map = player == PLAYER1 ? &w->p1_map : &w->p2_map;

try_again:
    printf("> ");
    scanf("%hhd %hhd %s", &front.x, &front.y, buffer);

    switch((char)buffer[0])
    {
      case 'u': orientation.x = -1; orientation.y =  0; break;
      case 'l': orientation.x =  0; orientation.y = -1; break;
      case 'r': orientation.x =  0; orientation.y =  1; break;
      case 'd': orientation.x =  1; orientation.y =  0; break;
      default: printf("Invalid orientation, try again!\n"); goto try_again;
    }

    ship->front = front;
    ship->back = add(ship->front, scalar(orientation, length));

    printf("PPP: %c\n", ship_contains(ship, vec2(9, 9)));

    if(map_is_valid_ship(map, ship))
    {
      map->ships[id] = ship;
    }
    else
    {
      printf("Invalid location, try again!\n");
      goto try_again;
    }
}

void world_player_place_ships(World* w, Player player)
{
  world_player_print(w, player);
  printf("Place carrier: #####\ntype: x y orientation\nx and y range from 0 to 9\norientation can be up, left, right and down\nexample: 2 3 right\n");
  world_place_ship(w, player, 5, 0);

  world_player_print(w, player);
  printf("Place Battleship: ####\n");
  world_place_ship(w, player, 4, 1);

  world_player_print(w, player);
  printf("Place Destroyer: ###\n");
  world_place_ship(w, player, 3, 2);

  world_player_print(w, player);
  printf("Place Submarine: ###\n");
  world_place_ship(w, player, 3, 3);

  world_player_print(w, player);
  printf("Place Patrol Boat: ##\n");
  world_place_ship(w, player, 2, 4);

  world_player_print(w, player);
}

void world_player_place_ships_random(World* w, Player player)
{
  if(player == PLAYER1)
    map_init_random(&w->p1_map);
  else
    map_init_random(&w->p2_map);
}

void world_player_shoot(World* w, Player player)
{
  Map* map;
  Vec2 shoot;

  if(player == PLAYER1)
  {
    map = &w->p2_map;
    map_to_string_just_hit(map, w->map_str);
    printf("\n\n%s", w->map_str);
    printf("PLAYER 1 shoot :> ");
  }
  else
  {
    map = &w->p1_map;
    map_to_string_just_hit(map, w->map_str);
    printf("\n\n%s", w->map_str);
    printf("PLAYER 2 shoot :> ");
  }

  scanf("%hhd %hhd", &shoot.x, &shoot.y);
  if(map_reg_shoot(map, shoot) == 1)
  {
    printf("HIT!\n");
    if(map_is_over(map))
    {
      if(player == PLAYER1)
        w->game_state = PLAYER1_WIN;
      else
        w->game_state = PLAYER2_WIN;
    }
  }
  else
    printf("MISS!\n");

}

void world_player_print(World* w, Player player)
{
  if(player == PLAYER1)
  {
    printf("\nPLAYER 1\n");
    map_to_string(&w->p1_map, w->map_str);
    printf("%s", w->map_str);
  }
  else
  {
    printf("\nPLAYER 2\n");
    map_to_string(&w->p2_map, w->map_str);
    printf("%s", w->map_str);
  }
}

void world_print(World* w)
{
  printf("\nWORLD:\n");
  world_player_print(w, PLAYER1);
  world_player_print(w, PLAYER2);
}
