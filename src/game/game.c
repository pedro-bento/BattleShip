#include "game.h"

#include <stdio.h>

#include "../math/vec2.h"

void game_init(Game* game)
{
  for(size_t i = 0; i < NUM_OF_SHIPS; i++)
    game->player1[i] = NULL;
  for(size_t i = 0; i < NUM_OF_SHIPS; i++)
    game->player2[i] = NULL;
  game->state = PLAYING;
  game->current_player = PLAYER1;
}

void game_free(Game* game)
{
  for(int i = 0; i < NUM_OF_SHIPS; i++)
    if(game->player1[i] != NULL)
      ship_free(game->player1[i]);
  for(int i = 0; i < NUM_OF_SHIPS; i++)
    if(game->player1[i] != NULL)
      ship_free(game->player1[i]);
}

void game_swap_current_player(Game* game)
{
  game->current_player = game->current_player == PLAYER1 ? PLAYER2 : PLAYER1;
}

Ship** game_get_player_ships(Game* game, Player player)
{
  return player == PLAYER1 ? game->player1 : game->player2;
}

int game_is_valid_ship(Game* game, Ship* ship)
{
  Vec2 p1 = ship->front;
  Vec2 p2 = ship->back;

  if(p1.x < 0 || p1.x >= MAP_LENGTH || p1.y < 0 || p1.y >= MAP_LENGTH ||
     p2.x < 0 || p2.x >= MAP_LENGTH || p2.y < 0 || p2.y >= MAP_LENGTH)
     return 0;

  Ship** pships = game_get_player_ships(game, game->current_player);
  for(size_t i = 0; i < NUM_OF_SHIPS; ++i)
    if(pships[i] != NULL)
      if(ship_intersect(ship, pships[i]))
        return 0;

  return 1;
}

void game_place_ship(Game* game, int length, int id)
{
  Vec2 front, orientation;
  char buffer[8];
  short isSuccess = 0;
  Ship* ship = ship_alloc(length);
  Ship** pships = game_get_player_ships(game, game->current_player);

  while(!isSuccess)
  {
    printf("> ");
    scanf("%hhd %hhd %s", &front.x, &front.y, buffer);

    switch(buffer[0])
    {
      case 'u': orientation.x = -1; orientation.y =  0; break;
      case 'l': orientation.x =  0; orientation.y = -1; break;
      case 'r': orientation.x =  0; orientation.y =  1; break;
      case 'd': orientation.x =  1; orientation.y =  0; break;
      default: printf("Invalid orientation, try again!\n"); continue;
    }

    ship->front = front;
    ship->back = add(ship->front, scalar(orientation, length));

    if(game_is_valid_ship(game, ship))
    {
      pships[id] = ship;
      isSuccess = 1;
    }else{
      printf("Invalid location, try again!\n");
    }
  }
}

void game_player_init_manual_console(Game* game)
{
  const int ship_length[5] = {5, 4, 3, 3, 2};
  const char* ship_name[5] = {"Carrier: 00000", "BattleShip: 0000",
    "Destroyer: 000", "Submarine: 000", "Patrol Boat: 00"};

  printf("To place a ship type: x y orientation\n\
x and y range from 0 to 9 (x is vertical)\n\
orientation can be up, left, right and down\n\
example: 2 3 right\n");

  for(size_t i = 0; i < NUM_OF_SHIPS; i++)
  {
      game_player_print(game, game->current_player);
      printf("Place %s\n", ship_name[i % 5]);
      game_place_ship(game, ship_length[i % 5], i);
  }

  game_player_print(game, game->current_player);
}

int game_player_add_ship(Game* game, Ship* ship, size_t id)
{
  Ship** pships = game_get_player_ships(game, game->current_player);
  if(game_is_valid_ship(game, ship))
  {
    pships[id] = ship;
    return 1;
  }
  return 0;
}

// Probably time can be improved
Ship* game_create_random_ship(Game* game, int length)
{
  Ship* ship = ship_alloc(length);
  do{
    ship_move(ship, vec2(rdn_range(0, MAP_LENGTH-1), rdn_range(0, MAP_LENGTH-1)));
    size_t num_rots = rdn_range(0, 4);
    for(size_t i = 0; i < num_rots; ++i)
      ship_rotate_counterclockwise(ship);
  }while(!game_is_valid_ship(game, ship));
  return ship;
}

void game_player_init_random(Game* game)
{
  const int ship_length[5] = {5, 4, 3, 3, 2};
  Ship** pships = game_get_player_ships(game, game->current_player);
  for(size_t i = 0; i < NUM_OF_SHIPS; i++)
    pships[i] = game_create_random_ship(game, ship_length[i % 5]);
}

int game_reg_shot(Game* game, Player player, Vec2 shot)
{
  Ship** pships = game_get_player_ships(game, player);
  for(size_t i = 0; i < NUM_OF_SHIPS; ++i)
    if(pships[i] != NULL)
        if(ship_reg(pships[i], shot))
          return 1;
  return 0;
}

int game_player_is_over(Game* game, Player player)
{
  Ship** pships = game_get_player_ships(game, player);
  for(size_t i = 0; i < NUM_OF_SHIPS; ++i)
    if(pships[i] != NULL)
        if(ship_is_over(pships[i]) == 0)
          return 0;
  return 1;
}

void game_player_shoot_console(Game* game)
{
  Vec2 shot;
  Player opp;

  if(game->current_player == PLAYER1){
    opp = PLAYER2;
    game_player_print_hits(game, opp);
    printf("\nPLAYER 1 shoot :> ");
  }else{
    opp = PLAYER1;
    game_player_print_hits(game, opp);
    printf("\nPLAYER 2 shoot :> ");
  }

  scanf("%hhd %hhd", &shot.x, &shot.y);
  if(game_reg_shot(game, opp, shot) == 1){
    printf("HIT!\n");
    if(game_player_is_over(game, opp)){
      if(game->current_player == PLAYER1) game->state = PLAYER1_WIN;
      else game->state = PLAYER2_WIN;
    }
  }else{
    printf("MISS!\n");
  }
}

void game_player_shoot_gui(Game* game, Vec2 shot)
{
  Player opp = game->current_player == PLAYER1 ? PLAYER2 : PLAYER1;
  if(game_reg_shot(game, opp, shot) == 1){
    if(game_player_is_over(game, opp)){
      if(game->current_player == PLAYER1) game->state = PLAYER1_WIN;
      else game->state = PLAYER2_WIN;
    }
  }
}

char game_player_get_cell(Game* game, Player player, Vec2 p)
{
  Ship** pships = game_get_player_ships(game, player);
  char ch;
  for(size_t i = 0; i < NUM_OF_SHIPS; ++i)
    if(pships[i] != NULL)
        if((ch = ship_contains(pships[i], p)) != '\0')
          return ch;
  return ' ';
}

void game_player_to_string(Game* game, Player player, char* str)
{
  size_t index = 0;
  str[index++] = ' ';
  for(int i = 0; i < MAP_LENGTH; ++i)
  {
    str[index++] = i + '0';
    if(i != MAP_LENGTH - 1) str[index++] = ' ';
  }
  str[index++] = '\n';

  for(int x = 0; x < MAP_LENGTH; ++x)
  {
    str[index++] = x + '0';
    for(int y = 0; y < MAP_LENGTH; ++y)
    {
      str[index++] = game_player_get_cell(game, player, vec2(x, y));
      if(y != MAP_LENGTH - 1) str[index++] = ' ';
    }

    str[index++] = '#';
    str[index++] = '\n';
  }

  str[index++] = ' ';
  for(int i = 0; i <= MAP_LENGTH*2-1; ++i)
    str[index++] = '#';
  str[index++] = '\n';
  str[index] = '\0';
}

void game_player_print(Game* game, Player player)
{
  // good aproximation for the number of chars that will be needed
  // 16 + 6x + 2x^2
  const size_t count_aprox = 16 + 6 * MAP_LENGTH + 2 * MAP_LENGTH * MAP_LENGTH;
  char player_str[count_aprox];

  if(player == PLAYER1)
    printf("\nPLAYER 1\n");
  else
    printf("\nPLAYER 2\n");

  game_player_to_string(game, player, player_str);
  printf("%s", player_str);
}

void game_player_print_hits(Game* game, Player player)
{
  // good aproximation for the number of chars that will be needed
  // 16 + 6x + 2x^2
  const size_t count_aprox = 16 + 6 * MAP_LENGTH + 2 * MAP_LENGTH * MAP_LENGTH;
  char player_str[count_aprox];
  game_player_to_string(game, player, player_str);
  size_t i = 0;
  while(player_str[i] != '\0'){
    if(player_str[i] == STATE_GOOD)
      player_str[i] = ' ';
    ++i;
  }
  printf("\n%s", player_str);
}

void game_print(Game* game)
{
  printf("\nWORLD:\n");
  game_player_print(game, PLAYER1);
  game_player_print(game, PLAYER2);
}
